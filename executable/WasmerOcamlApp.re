open Ctypes;

let main = () => {
  open WasmerOcaml;
  let filename = "hello_wasm.wasm";
  let wasmBlob = Util.readFile(filename);
  let wasmBlobSize = String.length(wasmBlob);
  print_endline(
    Format.sprintf("Loaded wasmBlob=%s, bytes=%d", filename, wasmBlobSize),
  );
  let engine = Lib.wasm_engine_new();
  print_endline(Format.sprintf("Made an engine"));
  let store = Lib.wasm_store_new(engine);
  if (Ctypes.raw_address_of_ptr(Ctypes.to_voidp(store)) == 0n) {
    failwith("failed to create store");
  };
  print_endline(Format.sprintf("Made a store from the engine"));

  let binary = Lib.makeByteVec();

  Lib.wasm_byte_vec_new_uninitialized(
    binary,
    Unsigned.Size_t.of_int(wasmBlobSize),
  );

  let data_buffer = Ctypes.CArray.of_string(wasmBlob);
  Ctypes.setf(
    Ctypes.(!@binary),
    Lib.wasm_byte_vec_data,
    data_buffer |> Ctypes.CArray.start,
  );

  let binarySize = Ctypes.getf(Ctypes.(!@binary), Lib.wasm_byte_vec_size);

  binarySize
  |> Unsigned.Size_t.to_int
  |> Format.sprintf("Initialized storage, bytes=%d")
  |> print_endline;

  print_endline(Format.sprintf("Compiling module..."));

  let wasm_module = Lib.wasm_module_new(store, binary);
  if (Ctypes.raw_address_of_ptr(Ctypes.to_voidp(wasm_module)) == 0n) {
    failwith("failed to create module");
  };
  Format.sprintf("Creating callback") |> print_endline;
  let hello_type = Lib.wasm_functype_new_0_0();
  Format.sprintf("Created functype") |> print_endline;

  let hello_callback = (_, _) => {
    Printf.printf("HELLO MAN\n");
    Ctypes.coerce(
      Ctypes.ptr(Ctypes.void),
      Ctypes.ptr(Lib.wasm_trap),
      Ctypes.null,
    );
  };
  let hello_func = Lib.wasm_func_new(store, hello_type, hello_callback);
  Format.sprintf("Created callback") |> print_endline;

  Format.sprintf("Instantiating module...\n") |> print_endline;
  let imports = Ctypes.CArray.make(Ctypes.ptr(Lib.wasm_extern), 1);
  Ctypes.CArray.set(imports, 0, Lib.wasm_func_as_extern(hello_func));

  let instance =
    Lib.wasm_instance_new(
      store,
      wasm_module,
      imports |> Ctypes.CArray.start,
      Ctypes.null,
    );
  if (Ctypes.raw_address_of_ptr(Ctypes.to_voidp(instance)) == 0n) {
    failwith("failed to create instance");
  };

  let exports = Lib.makeExternVec();
  Lib.wasm_instance_exports(instance, exports);
  let exports_size =
    Ctypes.getf(!@exports, Lib.wasm_extern_vec_size) |> Unsigned.Size_t.to_int;
  if (exports_size == 0) {
    failwith("no exports found");
  };
  Format.sprintf("Found %d exports\n", exports_size) |> print_endline;

  let exports_data =
    CArray.from_ptr(Ctypes.getf(!@exports, Lib.wasm_extern_vec_data), 1);
  let run_func = CArray.get(exports_data, 0) |> Lib.wasm_extern_as_func;

  Lib.wasm_func_call(run_func, Lib.wasm_val_null, Lib.wasm_val_null);
};

main();
