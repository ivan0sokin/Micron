#ifndef _MICRON_ENGINE_CORE_ENUM_H
#define _MICRON_ENGINE_CORE_ENUM_H

#include "types/BasicTypes.h"

#include <concepts>

namespace Micron
{
	template <std::integral Integral, std::_Has_class_or_enum_type T> constexpr Integral EnumToIntegral(T const &value) noexcept { return static_cast<Integral>(value); }
	template <std::_Has_class_or_enum_type T> constexpr Size EnumToSizeType(T const &value) noexcept { return static_cast<Size>(value); }
	template <std::_Has_class_or_enum_type T> constexpr USize EnumToUnsignedSizeType(T const &value) noexcept { return static_cast<USize>(value); }
	template <std::_Has_class_or_enum_type T> constexpr Byte EnumToByte(T const &value) noexcept { return static_cast<Byte>(value); }
}

#endif