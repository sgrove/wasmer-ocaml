echo "----"
dune exec library/stubgen.exe -- -c
echo "----c-bindings ^ | v ml-bindings"
dune exec library/stubgen.exe -- -ml
echo "----ml-bindings ^ | runnning..."
dune exec executable/WasmerOcamlApp.exe
