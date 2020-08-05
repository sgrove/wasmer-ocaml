open Ctypes;
open Ctypes_static;
open Wasmer_stubgen;

type size_t = Unsigned.size_t;

module type Vector_S = {
  type data;
  type t = structure(data);
  let t: typ(t);

  let size: field(size_t, t);
  let data: field(ptr(data), t);

  let new_uninitialized: (ptr(t), size_t) => unit;
  let delete: ptr(t) => unit;
};

type wasm_engine;
let engine: typ(wasm_engine);
let engine_new: unit => ptr(wasm_engine);

type wasm_store;
let store: typ(wasm_store);
let store_new: ptr(wasm_engine) => ptr(wasm_store);
type byte;
module Byte_vec: Vector_S with type data = char;

type wasm_module;
let module_: typ(wasm_module);
let module_size: field(size_t, wasm_module);
let module_new: (ptr(wasm_store), ptr(Byte_vec.t)) => ptr(wasm_module);
type wasm_functype;
let functype: typ(wasm_functype);
let functype_size: field(size_t, wasm_functype);
let functype_new_0_0: unit => ptr(wasm_functype);
let functype_delete: ptr(wasm_functype) => unit;
type wasm_val;
let val_: typ(wasm_val);
let val_kind: field(size_t, wasm_val);
type wasm_trap;
let trap: typ(wasm_trap);
let trap_size: field(size_t, wasm_trap);
type wasm_func;
let func: typ(wasm_func);
let func_size: field(size_t, wasm_func);
let func_0_0_callback:
  typ((ptr(wasm_val), ptr(wasm_val)) => ptr(wasm_trap));
let func_new:
  (
    ptr(wasm_store),
    ptr(wasm_functype),
    (ptr(wasm_val), ptr(wasm_val)) => ptr(wasm_trap)
  ) =>
  ptr(wasm_func);
let func_delete: ptr(wasm_func) => unit;
type wasm_extern;
let extern: typ(wasm_extern);
let extern_addr: wasm_extern => ptr(wasm_extern);
let extern_size: field(size_t, wasm_extern);
let func_as_extern: ptr(wasm_func) => ptr(wasm_extern);
let extern_as_func: ptr(wasm_extern) => ptr(wasm_func);
module Extern_vec: Vector_S with type data = wasm_extern;
type wasm_instance;
let instance: typ(wasm_instance);
let instance_size: field(size_t, wasm_instance);
let instance_new:
  (ptr(wasm_store), ptr(wasm_module), ptr(ptr(wasm_extern)), ptr(unit)) =>
  ptr(wasm_instance);
let instance_exports: (ptr(wasm_instance), ptr(Extern_vec.t)) => unit;
let func_call: (ptr(wasm_func), ptr(wasm_val), ptr(wasm_val)) => ptr(unit);

let makeByteVec: unit => ptr(Byte_vec.t);
let makeExternVec: unit => ptr(Extern_vec.t);

let val_null: ptr(wasm_val);
