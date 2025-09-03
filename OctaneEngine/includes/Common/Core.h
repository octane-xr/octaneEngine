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
#include <GL/glew.h>

//include spdlog
#define FMT_HEADER_ONLY
#define SPDLOG_FMT_EXTERNAL
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#define GLEW_STATIC


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

//console logging
#ifdef OCTANE_ENABLE_LOG
    namespace Octane
    {
        struct OCTANE_API Logger
        {
            using SPDLog = std::shared_ptr<spdlog::logger>;
            OCTANE_INLINE Logger()
            {
                m_SPD = spdlog::stdout_color_mt("stdout");
                spdlog::set_level(spdlog::level::trace);
                spdlog::set_pattern("%^[%T]: [#%t] %v%$");
            }

            OCTANE_INLINE static SPDLog& Ref()
            {
                static Logger logger;
                return logger.m_SPD;
            }

        private:
            SPDLog m_SPD;

        };
    }

    //logging macros
    #define OCTANE_TRACE(...) Octane::Logger::Ref()->trace(__VA_ARGS__)
    #define OCTANE_DEBUG(...) Octane::Logger::Ref()->debug(__VA_ARGS__)
    #define OCTANE_INFO(...) Octane::Logger::Ref()->info(__VA_ARGS__)
    #define OCTANE_WARN(...) Octane::Logger::Ref()->warn(__VA_ARGS__)
    #define OCTANE_ERROR(...) Octane::Logger::Ref()->error(__VA_ARGS__)
    #define OCTANE_FATAL(...) Octane::Logger::Ref()->critical(__VA_ARGS__)

#else  
    #define OCTANE_TRACE
    #define OCTANE_DEBUG
    #define OCTANE_INFO
    #define OCTANE_WARN
    #define OCTANE_ERROR
    #define OCTANE_FATAL

#endif

//typeid
namespace Octane
{
    template <typename T>
    OCTANE_INLINE constexpr uint32_t TypeID()
    {
        return static_cast<uint32_t>(reinterpret_cast<std::uintptr_t>(&typeid(T)));

    }
}

//free allocated memory
#define OCTANE_DELETE(ptr) if (ptr != nullptr) {delete (ptr); ptr=nullptr;}
