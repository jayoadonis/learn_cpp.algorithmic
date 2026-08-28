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

---

## Installation Application Layout (STANDARD)
```bash
#REM: Linux Style layout (both unix/unix-like)
/usr/local/                    #REM: Or /opt/my_project/
├── bin/
│   └── my_app                 #REM: The executable binary or script
├── lib/
│   └── libmy_app_shared.dylib #REM: Shared libraries (macOS uses .dylib instead of .so)
├── share/
│   ├── doc/my_app/            #REM: Documentation and licenses
│   └── my_app/
│       ├── icons/             #REM: Application icons
│       └── config.conf        #REM: Global configuration files
└── include/
    └── my_app.h               #REM: Header files (if distributing a development library)
```
```bash
#REM: Apple App bundle Layout (MacOS)
MyApplication.app/             #REM: Looks like a single clickable icon in Finder
└── Contents/
    ├── Info.plist             #REM: Metadata (App name, version, permissions, icons)
    ├── MacOS/
    │   └── MyApplication      #REM: The actual executable binary
    ├── Resources/
    │   ├── AppIcon.icns       #REM: Apple-format icon file
    │   ├── Assets.car         #REM: Compiled UI assets
    │   └── en.lproj/          #REM: Localization/Language files
    ├── Frameworks/
    │   └── Embedded.framework #REM: Bundled private libraries and dependencies
    └── PlugIns/               #REM: Optional app extensions or plugins
```
```bash
#REM: Windows App Layout
C:\\Program Files\\MyApplication\\    #REM: The root application folder
├── MyApplication.exe                 #REM: The main clickable executable file
├── app_icon.ico                      #REM: Windows-format icon file
├── config.json                       #REM: Local configuration or settings file
├── System.Data.SQLite.dll            #REM: Dynamic Link Library (Windows equivalent to Linux .so)
├── OpenSSL.dll                       #REM: Third-party dependency library
└── assets\\                          #REM: Subfolder for static assets
    ├── images\\                      #REM: UI images and graphic assets
    └── locales\\                     #REM: Language and translation files
```

## Installation Application Layout (OUR WAY)
```bash
#REM: Linux Style layout (both unix/unix-like)
/usr/local/                    #REM: Or /opt/my_project/
├── bin/
│   └── my_app                 #REM: The executable binary or script
├── lib/
│   └── libmy_app_shared.dylib #REM: Shared libraries (macOS uses .dylib instead of .so)
├── share/
│   ├── doc/my_app/            #REM: Documentation and licenses
│   └── my_app/
│       └── resources/               
│           ├── icons/         #REM: Application icons
│           └── config.conf    #REM: Global configuration files
└── include/
    └── my_app.h               #REM: Header files (if distributing a development library)
```
```bash
#REM: Apple App bundle Layout (MacOS) [Same with the standard]
MyApplication.app/             #REM: Looks like a single clickable icon in Finder
└── Contents/
    ├── Info.plist             #REM: Metadata (App name, version, permissions, icons)
    ├── MacOS/
    │   └── MyApplication      #REM: The actual executable binary
    ├── Resources/
    │   ├── AppIcon.icns       #REM: Apple-format icon file
    │   ├── Assets.car         #REM: Compiled UI assets
    │   └── en.lproj/          #REM: Localization/Language files
    ├── Frameworks/
    │   └── Embedded.framework #REM: Bundled private libraries and dependencies
    └── PlugIns/               #REM: Optional app extensions or plugins
```
```bash
#REM: Windows App Layout
C:\\Program Files\\MyApplication\\    #REM: The root application folder
├── bin\\
│   ├── MyApplication.exe             #REM: The main clickable executable file
│   ├── app_icon.ico                  #REM: Windows-format icon file
│   ├── System.Data.SQLite.dll        #REM: Dynamic Link Library (Windows equivalent to Linux .so)
│   └── OpenSSL.dll                   #REM: Third-party dependency library
└── resources\\                       #REM: Subfolder for static assets
    ├── images\\                      #REM: UI images and graphic assets
    ├── locales\\                     #REM: Language and translation files
    └── config.json                   #REM: Local configuration or settings file
```