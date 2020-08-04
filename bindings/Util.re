let foo = () =>
  print_endline(
    "Hello, "
    ++ (Wasmer_stubgen.wasmer_wrapped_stub_1_sum(10, 10) |> string_of_int),
  );
