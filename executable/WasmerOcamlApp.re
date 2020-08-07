open Ctypes;
open WasmerOcaml;

let (let.collect) = (v, f) => {
  Gc.full_major();
  Gc.minor();
  let value = f(v);
  Gc.full_major();
  Gc.minor();
  value;
};

let main = () => {
  let filename = "hello_wasm.wasm";
  let wasmBlob = Util.readFile(filename);
  let wasmBlobSize = String.length(wasmBlob);
  print_endline(
    Format.sprintf("Loaded wasmBlob=%s, bytes=%d", filename, wasmBlobSize),
  );
  let.collect engine = Wasm.engine_new();
  print_endline(Format.sprintf("Made an engine"));
  let.collect store = Wasm.store_new(engine);
  if (Ctypes.raw_address_of_ptr(Ctypes.to_voidp(store)) == 0n) {
    failwith("failed to create store");
  };
  print_endline(Format.sprintf("Made a store from the engine"));

  let.collect binary =
    Wasm.Byte_vec.make(Unsigned.Size_t.of_int(wasmBlobSize));
  let data_buffer = Ctypes.CArray.of_string(wasmBlob);
  Ctypes.setf(
    Ctypes.(!@binary),
    Wasm.Byte_vec.data,
    data_buffer |> Ctypes.CArray.start,
  );
  let.collect binarySize = Ctypes.getf(Ctypes.(!@binary), Wasm.Byte_vec.size);

  let.collect _ =
    binarySize
    |> Unsigned.Size_t.to_int
    |> Format.sprintf("Initialized storage, bytes=%d")
    |> print_endline;

  print_endline(Format.sprintf("Compiling module..."));

  let.collect wasm_module = Wasm.module_new(store, binary);
  if (Ctypes.raw_address_of_ptr(Ctypes.to_voidp(wasm_module)) == 0n) {
    failwith("failed to create module");
  };

  Format.sprintf("Creating s") |> print_endline;
  let.collect hello_type = Wasm.functype_new_0_0();
  Format.sprintf("Created functype") |> print_endline;

  let.collect hello_callback = (_, _) => {
    Printf.printf("HELLO MAN\n");
    Ctypes.coerce(
      Ctypes.ptr(Ctypes.void),
      Ctypes.ptr(Wasm.trap),
      Ctypes.null,
    );
  };
  let.collect hello_func = Wasm.func_new(store, hello_type, hello_callback);
  Format.sprintf("Created callback") |> print_endline;
  Format.sprintf("Instantiating module...\n") |> print_endline;
  let.collect imports = Ctypes.CArray.make(Ctypes.ptr(Wasm.extern), 1);
  Ctypes.CArray.set(imports, 0, Wasm.func_as_extern(hello_func));
  let.collect instance =
    Wasm.instance_new(
      store,
      wasm_module,
      imports |> Ctypes.CArray.start,
      Ctypes.null,
    );

  if (Ctypes.raw_address_of_ptr(Ctypes.to_voidp(instance)) == 0n) {
    failwith("failed to create instance");
  };

  let.collect exports = Wasm.Extern_vec.make(Unsigned.Size_t.of_int(0));
  let.collect () = Wasm.instance_exports(instance, exports);

  let.collect exports_size =
    Ctypes.getf(!@exports, Wasm.Extern_vec.size) |> Unsigned.Size_t.to_int;

  if (exports_size == 0) {
    failwith("no exports found");
  };
  Format.sprintf("Found %d exports\n", exports_size) |> print_endline;

  let.collect exports_data =
    CArray.from_ptr(Ctypes.getf(!@exports, Wasm.Extern_vec.data), 1);

  let.collect run_func = CArray.get(exports_data, 0) |> Wasm.extern_as_func;
  Wasm.func_call(run_func, Wasm.val_null, Wasm.val_null);
};

main();
