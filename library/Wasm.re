include Bindings.WasmerBindings.M(Wasmer_stubgen);
open Ctypes;

type size_t = Unsigned.Size_t.t;

module type Vector_S = {
  type data;
  type t = structure(data);
  let t: typ(t);

  let size: field(size_t, t);
  let data: field(ptr(data), t);

  let new_uninitialized: (ptr(t), size_t) => unit;
  let delete: ptr(t) => unit;
};

let finalise = (callback, value) => {
  Gc.finalise(callback, value);
  value;
};

let makeByteVec = () => {
  let vec = Ctypes.allocate_n(~count=1, Byte_vec.t);
  finalise(Byte_vec.delete, vec);
};

let makeExternVec = () => {
  let vec = Ctypes.allocate_n(~count=1, Extern_vec.t);
  finalise(Extern_vec.delete, vec);
};

let module_new = (store, binary) => {
  let store_ptr = Root.create(store);
  let binary_ptr = Root.create(binary);

  finalise(
    _module_ => {
      Root.release(store_ptr);
      Root.release(binary_ptr);
    },
    module_new(store, binary),
  );
};
let func_new = (store, functype, callback) =>
  finalise(func_delete, func_new(store, functype, callback));
let functype_new_0_0 = () => finalise(functype_delete, functype_new_0_0());

let val_null = coerce(ptr(void), ptr(val_), null);
