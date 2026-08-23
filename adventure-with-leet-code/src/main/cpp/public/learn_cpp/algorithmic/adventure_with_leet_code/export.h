
/**
 * project: adventure-with-leet-code
 * group: learn_cpp.algorithmic
 *
 */
#ifndef LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_EXPORT_H
#define LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_EXPORT_H

#if defined(_WIN32)
//REM: Windows (MSVC, MINGW[GCC|CLANG], CYGWIN[GCC|CLANG], MSYS2[GCC|CLANG])
# if defined(LCXXA_AWLEETCODE_BUILD_STATIC)
#   define LCXXA_AWLEETCODE_API
# else
    //REM: '__cpp_modules' is enable if CXX 20+ Modules
#   if defined(LCXXA_AWLEETCODE_BUILD_EXPORT)
#     if defined(__cpp_modules)
        //REM: C++20 modules, 'export' handles linkage natively.
#       define LCXXA_AWLEETCODE_API
#     else
        //REM: dllexport is safely preserved.
#       define LCXXA_AWLEETCODE_API __declspec(dllexport)
#     endif
#   else
#     if defined(__cpp_modules)
        //REM: C++20 modules, 'import' handles linkage natively.
#       define LCXXA_AWLEETCODE_API
#     else
        //REM: dllimport is safely preserved.
#       define LCXXA_AWLEETCODE_API __declspec(dllimport)
#     endif
#   endif
# endif
# define LCXXA_AWLEETCODE_API_INTERNAL

#elif defined(__GNUC__) || defined(__clang__)
//REM: Linux or MacOS (GCC, CLANG)
//REM: In here does not need to '__cpp_modules' transformation
# if defined(LCXXA_AWLEETCODE_BUILD_STATIC)
#   define LCXXA_AWLEETCODE_API
# else
#   define LCXXA_AWLEETCODE_API __attribute__((visibility("default")))
# endif
# define LCXXA_AWLEETCODE_API_INTERNAL __attribute__((visibility("hidden")))

#else 
//REM: Unknown Compiler
# define LCXXA_AWLEETCODE_API
# define LCXXA_AWLEETCODE_API_INTERNAL
#endif

//REM: === 2. Modernized Deprecation Feature Checking ===
//REM: We check if the compiler supports standard C++ attributes (C++14 onwards)
#if defined(__has_cpp_attribute)
# if __has_cpp_attribute(deprecated)
#   define LCXXA_AWLEETCODE_API_DEPRECATED [[deprecated]]
#   define LCXXA_AWLEETCODE_API_DEPRECATED_MSG(msg) [[deprecated("[DEPRECATED] " msg)]]
#   define LCXXA_AWLEETCODE_HAS_MODERN_DEPRECATED 1
# endif
#endif

//REM: Fallback to legacy C++03 vendor-specific attributes if modern features don't exist
#ifndef LCXXA_AWLEETCODE_HAS_MODERN_DEPRECATED
# if defined(_WIN32)
#   define LCXXA_AWLEETCODE_API_DEPRECATED __declspec(deprecated)
#   define LCXXA_AWLEETCODE_API_DEPRECATED_MSG(msg) __declspec(deprecated("[DEPRECATED] " msg))
# elif defined(__GNUC__) || defined(__clang__)
#   define LCXXA_AWLEETCODE_API_DEPRECATED __attribute__((deprecated))
#   define LCXXA_AWLEETCODE_API_DEPRECATED_MSG(msg) __attribute__((deprecated("[DEPRECATED] " msg)))
# else
#   define LCXXA_AWLEETCODE_API_DEPRECATED
#   define LCXXA_AWLEETCODE_API_DEPRECATED_MSG(msg)
# endif
#endif

#endif