// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

// Copyright (c) 2023 Haoyang Wu 

#ifndef INCLUDE_JET_MACROS_H_
#define INCLUDE_JET_MACROS_H_

// platform
#if defined(_WIN32) || defined(_WIN64)
#   define JET_WINDOWS
#elif defined(__APPLE__)
#   define JET_APPLE
#   ifndef JET_IOS
#       define JET_MACOSX
#   endif
#elif defined(linux) || defined(__linux__)
#   define JET_LINUX
#endif

// debugging mode
#if defined(DEBUG) || defined(_DEBUG)
#   define JET_DEBUG_MODE
#   include <cassert>
#   define JET_ASSERT(x) assert(x)
#else
#   define JET_ASSERT(x)
#endif

// make a class non-copyable
#ifdef __cplusplus
#define JET_NON_COPYABLE(ClassName) \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete;
#endif

// ensures `ssize_t` type is correctly defined
//  for Windows when compiling with Microsoft Visual C++
#if defined(JET_WINDOWS) && defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

// stringifying and concatenating
#define JET_DIAG_STR(s) #s
#define JET_DIAG_JOINSTR(x, y) JET_DIAG_STR(x ## y)

// compiler-specific pragma directives, control of warnings
#ifdef _MSC_VER
#define JET_DIAG_DO_PRAGMA(x) __pragma (#x)
#define JET_DIAG_PRAGMA(compiler, x) JET_DIAG_DO_PRAGMA(warning(x))
#else
#define JET_DIAG_DO_PRAGMA(x) _Pragma (#x)
#define JET_DIAG_PRAGMA(compiler, x) JET_DIAG_DO_PRAGMA(compiler diagnostic x)
#endif

#if defined(__clang__)
# define JET_DISABLE_CLANG_WARNING(clang_option) \
    JET_DIAG_PRAGMA(clang, push) \
    JET_DIAG_PRAGMA(clang, ignored JET_DIAG_JOINSTR(-W, clang_option))
# define JET_ENABLE_CLANG_WARNING(clang_option) JET_DIAG_PRAGMA(clang, pop)
# define JET_DISABLE_MSVC_WARNING(gcc_option)
# define JET_ENABLE_MSVC_WARNING(gcc_option)
# define JET_DISABLE_GCC_WARNING(gcc_option)
# define JET_ENABLE_GCC_WARNING(gcc_option)
#elif defined(_MSC_VER)
# define JET_DISABLE_CLANG_WARNING(gcc_option)
# define JET_ENABLE_CLANG_WARNING(gcc_option)
# define JET_DISABLE_MSVC_WARNING(msvc_errorcode) \
    JET_DIAG_PRAGMA(msvc, push) \
    JET_DIAG_DO_PRAGMA(warning(disable:##msvc_errorcode))
# define JET_ENABLE_MSVC_WARNING(msvc_errorcode) JET_DIAG_PRAGMA(msvc, pop)
# define JET_DISABLE_GCC_WARNING(gcc_option)
# define JET_ENABLE_GCC_WARNING(gcc_option)
#elif defined(__GNUC__)
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
# define JET_DISABLE_CLANG_WARNING(gcc_option)
# define JET_ENABLE_CLANG_WARNING(gcc_option)
# define JET_DISABLE_MSVC_WARNING(gcc_option)
# define JET_ENABLE_MSVC_WARNING(gcc_option)
# define JET_DISABLE_GCC_WARNING(gcc_option) \
    JET_DIAG_PRAGMA(GCC, push) \
    JET_DIAG_PRAGMA(GCC, ignored JET_DIAG_JOINSTR(-W, gcc_option))
# define JET_ENABLE_GCC_WARNING(gcc_option) JET_DIAG_PRAGMA(GCC, pop)
#else
# define JET_DISABLE_CLANG_WARNING(gcc_option)
# define JET_ENABLE_CLANG_WARNING(gcc_option)
# define JET_DISABLE_MSVC_WARNING(gcc_option)
# define JET_ENABLE_MSVC_WARNING(gcc_option)
# define JET_DISABLE_GCC_WARNING(gcc_option) \
    JET_DIAG_PRAGMA(GCC, ignored JET_DIAG_JOINSTR(-W, gcc_option))
# define JET_ENABLE_GCC_WARNING(gcc_option) \
    JET_DIAG_PRAGMA(GCC, warning JET_DIAG_JOINSTR(-W, gcc_option))
#endif
#endif

#endif  // INCLUDE_JET_MACROS_H_