include Test_bindings.WasmerBindings.M(Wasmer_stubgen);

let makeByteVec = () => {
  let vec = Ctypes.allocate_n(~count=1, wasm_byte_vec);
  vec;
};
