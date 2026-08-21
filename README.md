# learn_cpp.algorithmic

## Table of Content
+ [Feature](#feature-project)
+ [Run](#run)
  + [Configuration](#configuration-toc)
  + [Build](#build-toc)
  + [Test](#test-toc)
  + [Run Executable](#run-executable-toc)
  + [Install](#install-toc)
  + [Packaging](#packaging-toc)

## Feature (Project)
+ [adventure-with-leet-code](adventure-with-leet-code/)

## Run
### Configuration [^ToC](#table-of-content)
```bash
#REM: Single-Config
$ cmake -S . -B out/build/<generator_name>_<arch> [-G <generator_name>] [-DCMAKE_BUILD_TYPE=<Debug|Release>] [-D...] [--fresh]

#REM: Multi-Config (MSVC)
$ cmake -S . -B out/build/<generator_name>_<arch> [-G <generator_name>] [-D...] [-T host=<arch> -A <arch>] [--fresh]

#REM: Multi-Config 
$ cmake -S . -B out/build/<generator_name>_<arch> [-G <generator_name>] [-D...] [--fresh]
```

### Build [^ToC](#table-of-content)
```bash
#REM: Single-Config
$ cmake --build out/build/<generator_name>_<arch> [--clean-first] [--verbose] [--target <target_name>]

#REM: Multi-Config
$ cmake --build out/build/<generator_name>_<arch> --config <Debug|Release> [--clean-first] [--verbose] [--target <target_name>]
```

### Test [^ToC](#table-of-content)
```bash
$ ctest --test-dir out/build/<generator_name>_<arch> -C <Debug|Release> [-VV] [-R <test_name_pattern>] [-L <label_name_pattern>]
```

### Run Executable [^ToC](#table-of-content)
```bash
#REM: Single-Config
$ ./out/build/<generator_name>_<arch>/[subproject_path]/<binary_name>[.exe]

#REM: Multi-Config
$ ./out/build/<generator_name>_<arch>/[subproject_path]/<Debug|Release>/<binary_name>[.exe]
```

### Install [^ToC](#table-of-content)
```bash
$ cmake --install out/build/<generator_name>_<arch> --config <Debug|Release> [--verbose] [--prefix ./out/install] [--component <install_component_name>]
```

### Packaging [^ToC](#table-of-content)
```bash
$ cpack --config out/build/<generator_name>_<arch>/CPackConfig.cmake -B ./out/dist -C <Debug|Release> [-D CPACK_COMPONENTS_ALL="<install_component_name>"]
```
