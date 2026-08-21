# learn_cpp.algorithmic.adventure-with-leet-code

## Table of Content
+ [Easy (1)](#easy-toc)
+ [Project Structure](#project-structure-toc)
+ [Runtime Path Resource Handling](#runtime-path-resource-handling-toc)
---
## Easy [^ToC](#table-of-content)
+ [2SUM](src/main/cpp/public/learn_cpp/algorithmic/adventure_with_leet_code/easy/)
---
## Project Structure [^ToC](#table-of-content)
```bash
adventure-with-leet-code/ #REM (library)
|--- .gitattributes
|--- .gitignore
|--- CMakeLists.txt
|--- cmake/
|--- out/
|   |--- build/
|   |--- install/
|   \--- dist/ #REM: (zip;tar;msi)
\--- src/
    |--- main/
    |   |--- cpp/
    |   |   |--- CMakeLists.txt
    |   |   |--- private/learn_cpp/algoritmic/adventure_with_leet_code/**/*.<cc,cxx,cpp,h,hxx,hpp,tpp>
    |   |   \--- public/learn_cpp/algoritmic/adventure_with_leet_code/**/*.<hxx,hpp,tpp>
    |   \--- resources/ #REM: (runtime path: read-only)
    |       |--- data/template.sqlite
    |       \--- .env.toml
    \--- test/ #REM: (executable)
       |--- cpp/
       |   |--- CMakeLists.txt
       |   \--- private/learn_cpp/algoritmic/adventure_with_leet_code/**/*.<cc,cxx,cpp,h,hxx,hpp,tpp>
       \--- resources/ #REM: (runtime path: read-only)
           |--- data/template.test.sqlite
           \--- .env.test.toml
```
---
## Runtime Path Resource Handling [^ToC](#table-of-content)
| OS | App Bundle Resource [Seed data]\(READ_ONLY) | Persistent (READ_WRITE) | Temporary (READ_WRITE) | embedded
|---|---|---|---|---
| Windows | `C:\Program Files\<project_name>\resources` | `C:\Users\<user_name>\AppData\Roaming\<project_name>\resources` | `C:\Users\<user_name>\AppData\Local\Temp\<project_name>\resources` | ---
| Linux | `/usr/share/<project_name>/resources` | `~/.local/share/<project_name>/resources` | `/tmp/<project_name>/resources` or `$XDG_RUNTIME_DIR/<project_name>/resources` or `~/.config/<project_name>/resources` | ---
| MacOS | `<project_name>.app/contents/resources` | `~/library/application support/<project_name>/resources` | `~/Library/Caches/TemporaryItems/<project_name>/resources` | ---
---