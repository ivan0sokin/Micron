#ifndef _MICRON_CORE_H
#define _MICRON_CORE_H

#define MICRON_VERSION_MAJOR 0
#define MICRON_VERSION_MINOR 0
#define MICRON_VERSION_PATCH 1

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