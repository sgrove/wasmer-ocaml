open Ctypes;
open Foreign;

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

  /* Byte */
  type wasm_byte_vec;

  let wasm_byte_vec: typ(structure(wasm_byte_vec)) =
    structure("wasm_byte_vec_t");

  let wasm_byte_vec_size = field(wasm_byte_vec, "size", size_t);
  let wasm_byte_vec_data = field(wasm_byte_vec, "data", ptr(char));
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

  /*  WASM_API_EXTERN void wasm_##name##_vec_new_uninitialized */
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
  let wasm_functype_delete =
    foreign("wasm_functype_delete", ptr(wasm_functype) @-> returning(void));

  /* Val */
  type wasm_val;
  let wasm_val: typ(structure(wasm_val)) = structure("wasm_val_t");
  let wasm_val_kind = field(wasm_val, "kind", size_t);
  let () = seal(wasm_val);

  /* Trap */
  type wasm_trap;
  let wasm_trap: typ(structure(wasm_trap)) = structure("wasm_trap_t");
  let wasm_trap_size = field(wasm_trap, "size", size_t);
  let () = seal(wasm_trap);

  /* Func */
  type wasm_func;
  let wasm_func: typ(structure(wasm_func)) = structure("wasm_func_t");
  let wasm_func_size = field(wasm_func, "size", size_t);
  let () = seal(wasm_func);

  let wasm_func_0_0_callback =
    typedef(
      funptr(
        Ctypes.(
          ptr(wasm_val) @-> ptr(wasm_val) @-> returning(ptr(wasm_trap))
        ),
      ),
      "wasm_func_callback_t",
    );

  let wasm_func_new =
    foreign(
      "wasm_func_new",
      ptr(wasm_store)
      @-> ptr(wasm_functype)
      @-> wasm_func_0_0_callback
      @-> returning(ptr(wasm_func)),
    );
  let wasm_func_delete =
    foreign("wasm_func_delete", ptr(wasm_func) @-> returning(void));

  /* Extern */
  type wasm_extern;
  let wasm_extern: typ(structure(wasm_extern)) = structure("wasm_extern_t");
  let wasm_extern_size = field(wasm_extern, "size", size_t);
  let () = seal(wasm_extern);

  let wasm_func_as_extern =
    foreign(
      "wasm_func_as_extern",
      ptr(wasm_func) @-> returning(ptr(wasm_extern)),
    );
  let wasm_extern_as_func =
    foreign(
      "wasm_extern_as_func",
      ptr(wasm_extern) @-> returning(ptr(wasm_func)),
    );

  type wasm_extern_vec;

  let wasm_extern_vec: typ(structure(wasm_extern_vec)) =
    structure("wasm_extern_vec_t");

  let wasm_extern_vec_size = field(wasm_extern_vec, "size", size_t);
  let wasm_extern_vec_data =
    field(wasm_extern_vec, "data", ptr(ptr(wasm_extern)));
  let () = seal(wasm_extern_vec);

  /* Instance */
  type wasm_instance;
  let wasm_instance: typ(structure(wasm_instance)) =
    structure("wasm_instance_t");
  let wasm_instance_size = field(wasm_instance, "size", size_t);
  let () = seal(wasm_instance);

  let wasm_instance_new =
    foreign(
      "wasm_instance_new",
      ptr(wasm_store)
      @-> ptr(wasm_module)
      @-> ptr(ptr(wasm_extern))
      @-> ptr(void)
      @-> returning(ptr(wasm_instance)),
    );

  let wasm_instance_exports =
    foreign(
      "wasm_instance_exports",
      ptr(wasm_instance) @-> ptr(wasm_extern_vec) @-> returning(void),
    );

  /* Call */
  let wasm_func_call =
    foreign(
      "wasm_func_call",
      ptr(wasm_func)
      @-> ptr(wasm_val)
      @-> ptr(wasm_val)
      @-> returning(ptr(void)),
    );
};
