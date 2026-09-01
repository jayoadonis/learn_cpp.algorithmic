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
$ ctest --test-dir out/build/<generator_name>_<arch>/subproject_path -C <Debug|Release> [-VV] [-R <test_name_pattern>] [-L <label_name_pattern>]
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
#
---
#

## Sum-up CMake Scripts

```cmake
#REM: Root
cmake_minimum_required(VERSION 3.24)
project(project-name
  VERSIN 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()
_PROJECT_GROUP
_PROJECT_NAME
_PROJECT_VERSION
_PROJECT_TARGET_MAIN_NAME
_PROJECT_TARGET_MAIN_TYPE
_PROJECT_TARGET_TEST_NAME
_PROJECT_TARGET_TEST_TYPE
_PROJECT_INSTALL_CONFIG_PREFIX_NAME
_PROJECT_PRECOMPILED_DEPS_DIR
list APPEND CMAKE_PREFIX_PATH ${_PROJECT_PRECOMPILED_DEPS_DIR}
include(CTest)
add_subdirectory(src/main/cpp)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(src/test/cpp)
endif()
CPACK_PACKAGE_VENDOR
CPACK_PACKAGE_NAME
CPACK_PACKAGE_VERSION
CPACK_GENERATOR "ZIP;TGZ"
CPACK_RESOURCES_FILE_LICENSE
CPACK_VERBATIM_VARIABLES TRUE
include(CPack)


#REM: Subdirectory
FetchContent_Declare
FetchContent_MakeAvailable
file(GLOB_RECURSE _PRIVATE_SOURCES CONFIGURE_DEPENDS *.cc *.cxx *.cpp *.h *.hxx *.hpp *.tpp)
file(GLOB_RECURSE _PUBLIC_SOURCES CONFIGURE_DEPENDS *.h *.hxx *.hpp *.tpp)
add_executable | add_library ${_PROJECT_TARGET_(MAIN|TEST)_NAME}
set_target_properties
target_compile_features
target_compile_options
target_compile_definitions
target_sources
target_include_directories
target_link_libraries
if(BUILD_TESTING)
  add_library "project-main-interface" INTERFACE
  target_include_directory PRIVATE "path/to/private"
  target_link_libraries ${_PROJECT_TARGET_MAIN_NAME}
endif()
add_custom_command PRE_BUILD static resources for development build copy
add_custom_command POST_BUILD dlls for development build copy
#REM: [BEGIN] only for test target
target_compile_definitions(${_PROJECT_TARGET_TEST_NAME}
  PRIVATE
  CATCH_CONFIG_FAST_COMPILE
)
catch_discover_tests(${_PROJECT_TARGET_TEST_NAME}
  DISCOVERY_MODE PRE_TEST # REM: Prevents post-build script failures from killing the compiler run
  ADD_TAGS_AS_LABELS
  PROPERTIES
  LABELS "all"
)
#REM: [END] only for test target
include(GNUInstallDirs)
install bin lib archive inlucde
install static resources, pattern exclude or include
```
#
---
## Development Repository Structure
```bash
project-name/
|--- .gitignore
|--- .gitattributes
|--- CMakeLists.txt
|--- cmake/
|   |--- sync-copy-files.process.cmake            #REM: usually for windows dlls deps
|   \--- sync-copy-paths.process.cmake            #REM: usually for static resources
|--- out/
|   |--- build/
|   |--- install/                                 #REM: Staging
|   \--- dist/                                    #REM: zip, tgz, msi, dnf, & etc...
\--- src/
    |--- main/
    |   |--- cpp/
    |   |   |--- private/
    |   |   |   |--- pkg/main.{cc,cxx,cpp}        #REM: main exec target
    |   |   |   \--- pkg/**/*.{cc,cxx,cpp,h,hxx,hpp,tpp}
    |   |   \--- public/
    |   |       \--- pkg/**/*.{h,hxx,hpp,tpp}
    |   \--- resources/
    |       |--- config/
    |       |   |--- .env.development             #REM: Debug
    |       |   \--- .env.production              #REM: Release
    |       |--- document/
    |       \--- image/
    \--- test/
        |--- cpp/
        |   \--- private/
        |       |--- pkg/main.{cc,cxx,cpp}        #REM: test exec target
        |       |--- pkg/unit/**/*.{h,hxx,hpp,tpp}
        |       |--- pkg/integration/**/*.{h,hxx,hpp,tpp}
        |       \--- pkg/**/*.{c,cxx,cpp,h,hxx,hpp,tpp}
        \--- resources/
            |--- config/
            |   |--- .env.development.test
            |   \--- .env.production.test
            |--- document/
            \--- image/
```