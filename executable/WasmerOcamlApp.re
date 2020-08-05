open Ctypes;
open WasmerOcaml;

let main = () => {
  let filename = "hello_wasm.wasm";
  let wasmBlob = Util.readFile(filename);
  let wasmBlobSize = String.length(wasmBlob);
  print_endline(
    Format.sprintf("Loaded wasmBlob=%s, bytes=%d", filename, wasmBlobSize),
  );
  let engine = Wasm.engine_new();
  print_endline(Format.sprintf("Made an engine"));
  let store = Wasm.store_new(engine);
  if (Ctypes.raw_address_of_ptr(Ctypes.to_voidp(store)) == 0n) {
    failwith("failed to create store");
  };
  print_endline(Format.sprintf("Made a store from the engine"));

  let binary = Wasm.makeByteVec();

  Wasm.Byte_vec.new_uninitialized(
    binary,
    Unsigned.Size_t.of_int(wasmBlobSize),
  );

  let data_buffer = Ctypes.CArray.of_string(wasmBlob);
  Ctypes.setf(
    Ctypes.(!@binary),
    Wasm.Byte_vec.data,
    data_buffer |> Ctypes.CArray.start,
  );

  let binarySize = Ctypes.getf(Ctypes.(!@binary), Wasm.Byte_vec.size);

  binarySize
  |> Unsigned.Size_t.to_int
  |> Format.sprintf("Initialized storage, bytes=%d")
  |> print_endline;

  print_endline(Format.sprintf("Compiling module..."));

  let wasm_module = Wasm.module_new(store, binary);

  if (Ctypes.raw_address_of_ptr(Ctypes.to_voidp(wasm_module)) == 0n) {
    failwith("failed to create module");
  };
  Format.sprintf("Creating s") |> print_endline;
  let hello_type = Wasm.functype_new_0_0();
  Format.sprintf("Created functype") |> print_endline;

  let hello_callback = (_, _) => {
    Printf.printf("HELLO MAN\n");
    Ctypes.coerce(
      Ctypes.ptr(Ctypes.void),
      Ctypes.ptr(Wasm.trap),
      Ctypes.null,
    );
  };
  let hello_func = Wasm.func_new(store, hello_type, hello_callback);
  Format.sprintf("Created callback") |> print_endline;

  Format.sprintf("Instantiating module...\n") |> print_endline;
  let imports = Ctypes.CArray.make(Ctypes.ptr(Wasm.extern), 1);
  Ctypes.CArray.set(imports, 0, Wasm.func_as_extern(hello_func));

  let instance =
    Wasm.instance_new(
      store,
      wasm_module,
      imports |> Ctypes.CArray.start,
      Ctypes.null,
    );
  if (Ctypes.raw_address_of_ptr(Ctypes.to_voidp(instance)) == 0n) {
    failwith("failed to create instance");
  };

  let exports = Wasm.makeExternVec();
  Wasm.instance_exports(instance, exports);
  let exports_size =
    Ctypes.getf(!@exports, Wasm.Extern_vec.size) |> Unsigned.Size_t.to_int;
  if (exports_size == 0) {
    failwith("no exports found");
  };
  Format.sprintf("Found %d exports\n", exports_size) |> print_endline;

  let exports_data =
    CArray.from_ptr(Ctypes.getf(!@exports, Wasm.Extern_vec.data), 1);

  let run_func = CArray.get(exports_data, 0) |> Wasm.extern_as_func;

  Wasm.func_call(run_func, Wasm.val_null, Wasm.val_null);
};

main();
