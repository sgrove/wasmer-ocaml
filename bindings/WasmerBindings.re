open Ctypes;

/* module WasmerTypes = WasmerWrappedTypes.M(Wasmer_generated_type_stubs); */

module M = (F: FOREIGN) => {
  open F;
  let lastErrorLength =
    foreign("wasmer_last_error_length", void @-> returning(int));
};
