let hello_callback = () => {
  print_endline("Calling back...");
  print_endline("> Hello World!");
};

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
  print_endline(Format.sprintf("Made a store from the engine"));

  let binary = Lib.makeByteVec();

  Lib.wasm_byte_vec_new_uninitialized(
    binary,
    Unsigned.Size_t.of_int(wasmBlobSize),
  );

  let binarySize = Ctypes.getf(Ctypes.(!@binary), Lib.wasm_byte_vec_size);

  binarySize
  |> Unsigned.Size_t.to_int
  |> Format.sprintf("Initialized storage, bytes=%d")
  |> print_endline;

  print_endline(Format.sprintf("Compiling module..."));

  let wasm_module = Lib.wasm_module_new(store, binary);

  Format.sprintf("Done. Deleting binary...") |> print_endline;

  Lib.wasm_byte_vec_delete(binary);
  Format.sprintf("Deleted") |> print_endline;
  Format.sprintf("Creating callback") |> print_endline;
  let hello_type = Lib.wasm_functype_new_0_0();
  Format.sprintf("Created functype") |> print_endline;

  let hello_func = Lib.wasm_func_new(store, hello_type, hello_callback);
  Format.sprintf("Created callback") |> print_endline;
  ();
};

main();
