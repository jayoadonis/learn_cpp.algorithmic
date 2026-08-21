
/**
 * project: adventure-with-leet-code 
 * group: learn_cpp.algorithmic
 *
 */
#ifndef LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_EXPORT_H
#define LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_EXPORT_H

#if defined(_WIN32)
//REM: Windows: MSVC, MSYS2(GCC, CLANG), MINGW(GCC, CLANG), CYGWIN(GCC, CLANG) and a-like...
# if defined(LCXXA_AWLEETCODE_BUILD_STATIC)
#   define LCXXA_AWLEETCODE_API
# else
#   if defined(LCXXA_AWLEETCODE_BUILD_EXPORT)
#     define LCXXA_AWLEETCODE_API __declspec(dllexport)
#   else
#     define LCXXA_AWLEETCODE_API __declspec(dllimport)
#   endif
# endif
# define LCXXA_AWLEETCODE_API_INTERNAL
# define LCXXA_AWLEETCODE_API_DEPRECATED __declspec(deprecated)
# define LCXXA_AWLEETCODE_API_DEPRECATED_MSG(msg) __declspec(deprecated("[DEPRECATED] " msg))

#elif defined(__GNUC__) || defined(__clang__)
//REM: Linux or Apple: (GCC, CLANG)
# if defined(LCXXA_AWLEETCODE_BUILD_STATIC)
#   define LCXXA_AWLEETCODE_API
# else
#   define LCXXA_AWLEETCODE_API __attribute__((visibility("default")))
# endif
# define LCXXA_AWLEETCODE_API_INTERNAL __attribute__((visibility("hidden")))
# define LCXXA_AWLEETCODE_API_DEPRECATED __attribute__((deprecated))
# define LCXXA_AWLEETCODE_API_DEPRECATED_MSG(msg) __attribute__((deprecated("[DEPRECATED] " msg)))

#else 
# define LCXXA_AWLEETCODE_API
# define LCXXA_AWLEETCODE_API_INTERNAL
# define LCXXA_AWLEETCODE_API_DEPRECATED
# define LCXXA_AWLEETCODE_API_DEPRECATED_MSG(msg)
#endif

#endif