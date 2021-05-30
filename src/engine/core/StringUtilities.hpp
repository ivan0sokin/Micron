#ifndef _MICRON_ENGINE_CORE_STRING_UTILITIES_HPP
#define _MICRON_ENGINE_CORE_STRING_UTILITIES_HPP

#include "types/BasicTypes.h"
#include "types/ContainerTypes.h"

namespace Micron
{
    constexpr MultibyteString & TrimStringLeft(MultibyteString& string) noexcept
    {
        string.erase(string.cbegin(), std::ranges::find_if(std::as_const(string), [](Char c)
        {
            return !std::isspace(static_cast<Int32>(c));
        }));

        return string;
    }

    constexpr MultibyteString & TrimStringRight(MultibyteString &string) noexcept
    {
        string.erase(std::ranges::find_if(string.crbegin(), string.crend(), [](Char c)
        {
            return !std::isspace(static_cast<Int32>(c));
        }).base(), string.cend());

        return string;
    }

    constexpr MultibyteString & TrimString(MultibyteString &string) noexcept
    {
        return TrimStringLeft(TrimStringRight(string));
    }
}

#endif