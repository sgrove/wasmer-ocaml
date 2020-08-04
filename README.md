# wasmer-ocaml


[![CircleCI](https://circleci.com/gh/yourgithubhandle/wasmer-ocaml/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/wasmer-ocaml/tree/master)


**Contains the following libraries and executables:**

```
wasmer-ocaml@0.0.0
│
├─test/
│   name:    TestWasmerOcaml.exe
│   main:    TestWasmerOcaml
│   require: wasmer-ocaml.lib
│
├─library/
│   library name: wasmer-ocaml.lib
│   namespace:    WasmerOcaml
│   require:
│
└─executable/
    name:    WasmerOcamlApp.exe
    main:    WasmerOcamlApp
    require: wasmer-ocaml.lib
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x WasmerOcamlApp.exe 
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
