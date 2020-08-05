open Ctypes;
open Wasmer_stubgen;

let engine: typ(structure([ | `engine]));
let engine_new:
  result(unit => return(Ctypes_static.ptr(structure([ | `engine]))));

let store: typ(structure([ | `store]));
let store_new:
  result(
    Ctypes_static.ptr(structure([ | `engine])) =>
    return(Ctypes_static.ptr(structure([ | `store]))),
  );
type byte;
module Byte_vec: {
  type nonrec t = typ(structure(char));
  let name: string;
  let t: typ(structure(t));
  let size: field(Unsigned.size_t, structure(t));
  let data: field(Ctypes_static.ptr(char), structure(t));
  let new_uninitialized:
    result(
      (Ctypes_static.ptr(structure(t)), Unsigned.size_t) => return(unit),
    );
  let delete: result(Ctypes_static.ptr(structure(t)) => return(unit));
};
type wasm_module;
let module_: typ(structure(wasm_module));
let module_size: field(Unsigned.size_t, structure(wasm_module));
let module_new:
  result(
    (
      pointer(structured([ | `store], [ | `Struct]), [ | `C]),
      pointer(structured(Byte_vec.t, [ | `Struct]), [ | `C])
    ) =>
    return(pointer(structured(wasm_module, [ | `Struct]), [ | `C])),
  );
type wasm_functype;
let functype: typ(structure(wasm_functype));
let functype_size: field(Unsigned.size_t, structure(wasm_functype));
let functype_new_0_0:
  result(unit => return(Ctypes_static.ptr(structure(wasm_functype))));
let functype_delete:
  result(Ctypes_static.ptr(structure(wasm_functype)) => return(unit));
type wasm_val;
let val_: typ(structure(wasm_val));
let val_kind: field(Unsigned.size_t, structure(wasm_val));
type wasm_trap;
let trap: typ(structure(wasm_trap));
let trap_size: field(Unsigned.size_t, structure(wasm_trap));
type wasm_func;
let func: typ(structure(wasm_func));
let func_size: field(Unsigned.size_t, structure(wasm_func));
let func_0_0_callback:
  typ(
    (
      Ctypes_static.ptr(structure(wasm_val)),
      Ctypes_static.ptr(structure(wasm_val))
    ) =>
    Ctypes_static.ptr(structure(wasm_trap)),
  );
let func_new:
  result(
    (
      Ctypes_static.ptr(structure([ | `store])),
      Ctypes_static.ptr(structure(wasm_functype)),
      (
        Ctypes_static.ptr(structure(wasm_val)),
        Ctypes_static.ptr(structure(wasm_val))
      ) =>
      Ctypes_static.ptr(structure(wasm_trap))
    ) =>
    return(Ctypes_static.ptr(structure(wasm_func))),
  );
let func_delete:
  result(Ctypes_static.ptr(structure(wasm_func)) => return(unit));
type wasm_extern;
let extern: typ(structure(wasm_extern));
let extern_size: field(Unsigned.size_t, structure(wasm_extern));
let func_as_extern:
  result(
    Ctypes_static.ptr(structure(wasm_func)) =>
    return(Ctypes_static.ptr(structure(wasm_extern))),
  );
let extern_as_func:
  result(
    Ctypes_static.ptr(structure(wasm_extern)) =>
    return(Ctypes_static.ptr(structure(wasm_func))),
  );
module Extern_vec: {
  type nonrec t = typ(structure(ptr(structure(wasm_extern))));
  let name: string;
  let t: typ(structure(t));
  let size: field(Unsigned.size_t, structure(t));
  let data:
    field(Ctypes_static.ptr(ptr(structure(wasm_extern))), structure(t));
  let new_uninitialized:
    result(
      (Ctypes_static.ptr(structure(t)), Unsigned.size_t) => return(unit),
    );
  let delete: result(Ctypes_static.ptr(structure(t)) => return(unit));
};
type wasm_instance;
let instance: typ(structure(wasm_instance));
let instance_size: field(Unsigned.size_t, structure(wasm_instance));
let instance_new:
  result(
    (
      Ctypes_static.ptr(structure([ | `store])),
      Ctypes_static.ptr(structure(wasm_module)),
      Ctypes_static.ptr(Ctypes_static.ptr(structure(wasm_extern))),
      Ctypes_static.ptr(unit)
    ) =>
    return(Ctypes_static.ptr(structure(wasm_instance))),
  );
let instance_exports:
  result(
    (
      Ctypes_static.ptr(structure(wasm_instance)),
      Ctypes_static.ptr(structure(Extern_vec.t))
    ) =>
    return(unit),
  );
let func_call:
  result(
    (
      Ctypes_static.ptr(structure(wasm_func)),
      Ctypes_static.ptr(structure(wasm_val)),
      Ctypes_static.ptr(structure(wasm_val))
    ) =>
    return(Ctypes_static.ptr(unit)),
  );

let makeByteVec:
  unit => pointer(structured(Byte_vec.t, [ | `Struct]), [ | `C]);
let makeExternVec:
  unit => pointer(structured(Extern_vec.t, [ | `Struct]), [ | `C]);

let val_null: ptr(structure(wasm_val));
