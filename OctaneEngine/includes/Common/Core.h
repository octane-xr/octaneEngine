#pragma once
#include <queue>
#include <vector>
#include <string>
#include <bitset>
#include <memory>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <unordered_map>

//include spdlog
#define FMT_HEADER_ONLY
#define SPDLOG_FMT_EXTERNAL
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

//import, export
#ifdef OCTANE_EXPORT
    #ifdef _MSC_VER
        #define OCTANE_API __declspec(dllexport)
    #else  
        #define OCTANE_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define OCTANE_API __declspec(dllimport)
    #else
        #define OCTANE_API
    #endif
#endif

//runtime assertion
#define OCTANE_ASSERT assert

//static assertion
#if defined(__clang__) || defined(__gcc__)
    #define OCTANE_STATIC_ASSERT __cpp_static_assert
#else
    #define OCTANE_STATIC_ASSERT static_assert
#endif

//function inlining
#if defined(__clang__) || defined(__gcc__)
    #define OCTANE_INLINE __attribute__((always_inline)) inline
    #define OCTANE_NOINLINE __attribute__((noinline))
    
#elif defined(_MSC_VER)
    #define OCTANE_INLINE __forceinline
    #define OCTANE_NOINLINE __declspec(noinline)

#else
    #define OCTANE_INLINE inline
    #define OCTANE_NOINLINE

#endif

