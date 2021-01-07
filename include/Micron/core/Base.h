#ifndef _MICRON_CORE_BASE_H
#define _MICRON_CORE_BASE_H

#include <memory>
#include <cstddef>
#include <cassert>

#include "Platform.h"

#if defined(DEBUG) || defined(_DEBUG)
    #define MICRON_DEBUG
#endif

#if defined(MICRON_DEBUG)
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

#if defined(MICRON_DEBUG)
    #define MICRON_ASSERT(condition) assert(condition)
#else
    #define MICRON_ASSERT(condition)
#endif

#define MICRON_EXTRA_SHUTDOWN() exit(-1)

namespace Micron
{
    template <typename T> using Box = std::unique_ptr<T>;
    template <typename T> using Rc = std::shared_ptr<T>;

    template <typename T, typename ...Args> constexpr Box<T> MakeBox(Args &&...args) noexcept
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    template <typename T, typename ...Args> constexpr Rc<T> MakeRc(Args &&...args) noexcept
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    
    template <typename T, typename U> constexpr Rc<T> DynamicPointerCast(Rc<U> const &other) noexcept
    {
        return std::dynamic_pointer_cast<T, U>(other);
    }
}

#endif