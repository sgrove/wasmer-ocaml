let readFile = filename => {
  let lines = ref([]);
  let chan = open_in(filename);
  try(
    {
      while (true) {
        lines := [input_line(chan), ...lines^];
      };
      lines^ |> String.concat("\n");
    }
  ) {
  | End_of_file =>
    close_in(chan);
    List.rev(lines^) |> String.concat("\n");
  };
};
