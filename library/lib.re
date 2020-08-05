include Test_bindings.WasmerBindings.M(Wasmer_stubgen);

let finalise = (callback, value) => {
  Gc.finalise(callback, value);
  value
};

let makeByteVec = () => {
  let vec = Ctypes.allocate_n(~count=1, wasm_byte_vec);
  vec;
};

let wasm_functype_new_0_0 = () => finalise(wasm_functype_delete, wasm_functype_new_0_0());