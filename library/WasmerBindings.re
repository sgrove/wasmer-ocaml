open Ctypes;
module M = (F: FOREIGN) => {
  open F;
  let wasm_engine: typ(structure([ | `engine])) =
    structure("wasm_engine_t");
  let wasm_engine_new =
    foreign("wasm_engine_new", void @-> returning(ptr(wasm_engine)));

  let wasm_store: typ(structure([ | `store])) = structure("wasm_store_t");

  let wasm_store_new =
    foreign(
      "wasm_store_new",
      ptr(wasm_engine) @-> returning(ptr(wasm_store)),
    );

  type wasm_byte_vec;

  let wasm_byte_vec: typ(structure(wasm_byte_vec)) =
    structure("wasm_byte_vec_t");

  let wasm_byte_vec_size = field(wasm_byte_vec, "size", size_t);
  let wasm_byte_vec_data = field(wasm_byte_vec, "data", ptr(void));
  let () = seal(wasm_byte_vec);

  let wasm_byte_vec_new_uninitialized =
    foreign(
      "wasm_byte_vec_new_uninitialized",
      ptr(wasm_byte_vec) @-> size_t @-> returning(void),
    );

  let wasm_byte_vec_delete =
    foreign("wasm_byte_vec_delete", ptr(wasm_byte_vec) @-> returning(void));

  type wasm_module;
  let wasm_module: typ(structure(wasm_module)) = structure("wasm_module_t");
  let wasm_module_size = field(wasm_module, "size", size_t);
  let () = seal(wasm_module);

  //  WASM_API_EXTERN void wasm_##name##_vec_new_uninitialized
  let wasm_module_new =
    foreign(
      "wasm_module_new",
      ptr(wasm_store)
      @-> ptr(wasm_byte_vec)
      @-> returning(ptr(wasm_module)),
    );

  /* Functype */
  type wasm_functype;
  let wasm_functype: typ(structure(wasm_functype)) =
    structure("wasm_functype_t");
  let wasm_functype_size = field(wasm_functype, "size", size_t);
  let () = seal(wasm_functype);

  let wasm_functype_new_0_0 =
    foreign(
      "wasm_functype_new_0_0",
      void @-> returning(ptr(wasm_functype)),
    );

  /* Func */
  type wasm_func;
  let wasm_func: typ(structure(wasm_func)) = structure("wasm_func_t");
  let wasm_func_size = field(wasm_func, "size", size_t);
  let () = seal(wasm_func);

  let wasm_func_0_0_callback =
    Ctypes.static_funptr(Ctypes_static.(void @-> returning(void)));

  let wasm_func_new =
    foreign(
      "wasm_func_new",
      ptr(wasm_store)
      @-> ptr(wasm_functype)
      @-> wasm_func_0_0_callback
      @-> returning(ptr(wasm_func)),
    );
};
