include Bindings.WasmerBindings.M(Wasmer_stubgen);

let finalise = (callback, value) => {
  Gc.finalise(callback, value);
  value;
};

let makeByteVec = () => {
  let vec = Ctypes.allocate_n(~count=1, wasm_byte_vec);
  vec;
  // finalise(wasm_byte_vec_delete, vec);
} /* let wasm_func_new = (store, functype, callback) => finalise(wasm_func_delete, wasm_func_new(store, functype, callback)*/;

let makeExternVec = () => {
  let vec = Ctypes.allocate_n(~count=1, wasm_extern_vec);
  vec;
};

// let wasm_functype_new_0_0 = () => finalise(wasm_functype_delete, wasm_functype_new_0_0());

let wasm_val_null =
  Ctypes.coerce(Ctypes.ptr(Ctypes.void), Ctypes.ptr(wasm_val), Ctypes.null);
