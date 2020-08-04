open Ctypes;

/* module WasmerTypes = WasmerWrappedTypes.M(Wasmer_generated_type_stubs); */

module M = (F: FOREIGN) => {
  // module Ctypes_for_stubs = {
  //   include Ctypes;

  //   let (@->) = F.(@->);
  //   let returning = F.returning;
  //   let foreign = F.foreign;
  // };
  // open Ctypes_for_stubs;
  /* open F; */
  let x = 10;
};
