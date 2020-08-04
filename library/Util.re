let foo = () =>
  print_endline(
    "Hello, "
    ++ (Wasmer_stubgen.wasmer_1_wasmer_last_error_length() |> string_of_int),
  );
