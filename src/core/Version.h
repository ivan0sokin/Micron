#ifndef _MICRON_CORE_VERSION_H
#define _MICRON_CORE_VERSION_H

#include "types/BasicTypes.h"
#include "types/ContainerTypes.h"

namespace Micron
{
    struct Version
    {
        UInt8 major, minor, patch;
        
        inline Version() noexcept = default;
        inline ~Version() noexcept = default;

        explicit constexpr Version(UInt8 major, UInt8 minor = 0, UInt8 patch = 0) noexcept :
            major{ major }, minor{ minor }, patch{ patch }
        {}
        template <std::convertible_to<UInt8> T> explicit constexpr Version(T major, T minor = static_cast<T>(0), T patch = static_cast<T>(0)) noexcept :
            major{ static_cast<UInt8>(major)  }, minor{ static_cast<UInt8>(minor) }, patch{ static_cast<UInt8>(patch) }
        {}

        constexpr Array<UInt8, 3> ToArray() noexcept { return { major, minor, patch }; }
        constexpr Span<UInt8, 3> ToSpan() noexcept { return Span<UInt8, 3>(&major, &patch); }

        constexpr UInt8 & operator[](std::size_t index) noexcept { return (&this->major)[index]; }
        constexpr UInt8 const & operator[](std::size_t index) const noexcept { return (&this->major)[index]; }
    };
}

#endif