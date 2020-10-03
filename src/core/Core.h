#ifndef _MICRON_CORE_H
#define _MICRON_CORE_H

#define MICRON_VERSION_MAJOR 0
#define MICRON_VERSION_MINOR 0
#define MICRON_VERSION_PATCH 2

#include "Platform.h"

#ifdef MICRON_DEBUG
    #if MICRON_PLATFORM == MICRON_PLATFORM_WINDOWS
        #define MICRON_DEBUG_BREAK() __debugbreak()
    #elif MICRON_PLATFORM == MICRON_PLATFORM_LINUX
        #include <signal.h>
        #define MICRON_DEBUG_BREAK() raise(SIGTRAP)
    #else
        #error "Abort for the current platform is not supported"
    #endif
#else
    #define MICRON_DEBUG_BREAK()
#endif

#define _MICRON_CORE_ASSERT(condition) { if (!(condition)) { _MICRON_CORE_LOG_ERROR("File {}: Assertion on line {} failed", __FILE__, __LINE__); MICRON_DEBUG_BREAK(); } }
#define MICRON_ASSERT(condition) { if (!(condition)) { MICRON_LOG_ERROR("File {}: Assertion on line {} failed", __FILE__, __LINE__); MICRON_DEBUG_BREAK(); } }

#include <memory>

namespace Micron
{
    
    template <typename T>
    using Box = std::unique_ptr<T>;
    template <typename T>
    using Rc = std::shared_ptr<T>;

    template <typename T, typename ...Args>
    constexpr Box<T> MakeBox(Args &&...args) noexcept
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    template <typename T, typename ...Args>
    constexpr Rc<T> MakeRc(Args &&...args) noexcept
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif