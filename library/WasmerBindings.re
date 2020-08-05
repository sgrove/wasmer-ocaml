open Ctypes;
open Foreign;

module Vector =
       (F: FOREIGN, T: {
                      type t;
                      let t: Ctypes.typ(t);
                      let name: string;
                    }) => {
  open F;
  open T;
  type nonrec t = typ(structure(t));
  let name = name ++ "_vec";
  let t: typ(structure(t)) = structure(name ++ "_t");

  let size = field(t, "size", size_t);
  let data = field(t, "data", ptr(T.t));
  seal(t);

  let new_uninitialized =
    foreign(
      name ++ "_new_uninitialized",
      ptr(t) @-> size_t @-> returning(void),
    );

  let delete = foreign(name ++ "_delete", ptr(t) @-> returning(void));
};
module M = (F: FOREIGN) => {
  open F;

  let engine: typ(structure([ | `engine])) = structure("wasm_engine_t");
  let engine_new =
    foreign("wasm_engine_new", void @-> returning(ptr(engine)));

  let store: typ(structure([ | `store])) = structure("wasm_store_t");

  let store_new =
    foreign("wasm_store_new", ptr(engine) @-> returning(ptr(store)));

  /* Byte */
  type byte;

  module Byte_vec =
    Vector(
      F,
      {
        type t = char;
        let t = char;
        let name = "wasm_byte";
      },
    );

  type wasm_module;
  let module_: typ(structure(wasm_module)) = structure("wasm_module_t");
  let module_size = field(module_, "size", size_t);
  let () = seal(module_);

  /*  WASM_API_EXTERN void wasm_##name##_vec_new_uninitialized */

  let module_new =
    foreign(
      "wasm_module_new",
      ptr(store) @-> ptr(Byte_vec.t) @-> returning(ptr(module_)),
    );

  /* Functype */
  type wasm_functype;
  let functype: typ(structure(wasm_functype)) =
    structure("wasm_functype_t");
  let functype_size = field(functype, "size", size_t);
  let () = seal(functype);

  let functype_new_0_0 =
    foreign("wasm_functype_new_0_0", void @-> returning(ptr(functype)));
  let functype_delete =
    foreign("wasm_functype_delete", ptr(functype) @-> returning(void));

  /* Val */
  type wasm_val;
  let val_: typ(structure(wasm_val)) = structure("wasm_val_t");
  let val_kind = field(val_, "kind", size_t);
  let () = seal(val_);

  /* Trap */
  type wasm_trap;
  let trap: typ(structure(wasm_trap)) = structure("wasm_trap_t");
  let trap_size = field(trap, "size", size_t);
  let () = seal(trap);

  /* Func */
  type wasm_func;
  let func: typ(structure(wasm_func)) = structure("wasm_func_t");
  let func_size = field(func, "size", size_t);
  let () = seal(func);

  let func_0_0_callback =
    typedef(
      funptr(Ctypes.(ptr(val_) @-> ptr(val_) @-> returning(ptr(trap)))),
      "wasm_func_callback_t",
    );

  let func_new =
    foreign(
      "wasm_func_new",
      ptr(store)
      @-> ptr(functype)
      @-> func_0_0_callback
      @-> returning(ptr(func)),
    );
  let func_delete =
    foreign("wasm_func_delete", ptr(func) @-> returning(void));

  /* Extern */
  type wasm_extern;
  let extern: typ(structure(wasm_extern)) = structure("wasm_extern_t");
  let extern_size = field(extern, "size", size_t);
  let () = seal(extern);

  let func_as_extern =
    foreign("wasm_func_as_extern", ptr(func) @-> returning(ptr(extern)));
  let extern_as_func =
    foreign("wasm_extern_as_func", ptr(extern) @-> returning(ptr(func)));

  module Extern_vec =
    Vector(
      F,
      {
        type t = ptr(structure(wasm_extern));
        let t = ptr(extern);
        let name = "wasm_extern";
      },
    );
  /* Instance */
  type wasm_instance;
  let instance: typ(structure(wasm_instance)) =
    structure("wasm_instance_t");
  let instance_size = field(instance, "size", size_t);
  let () = seal(instance);

  let instance_new =
    foreign(
      "wasm_instance_new",
      ptr(store)
      @-> ptr(module_)
      @-> ptr(ptr(extern))
      @-> ptr(void)
      @-> returning(ptr(instance)),
    );

  let instance_exports =
    foreign(
      "wasm_instance_exports",
      ptr(instance) @-> ptr(Extern_vec.t) @-> returning(void),
    );

  /* Call */
  let func_call =
    foreign(
      "wasm_func_call",
      ptr(func) @-> ptr(val_) @-> ptr(val_) @-> returning(ptr(void)),
    );
};
