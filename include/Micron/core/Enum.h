#ifndef _MICRON_CORE_ENUM_H
#define _MICRON_CORE_ENUM_H

#include "types/BasicTypes.h"

#include <concepts>

namespace Micron
{
	template <std::signed_integral SignedIntegral, std::_Has_class_or_enum_type T> constexpr SignedIntegral EnumToInt(T const &value) noexcept { return static_cast<SignedIntegral>(value); }
	template <std::unsigned_integral UnsignedIntegral, std::_Has_class_or_enum_type T> constexpr UnsignedIntegral EnumToUnsignedInt(T const &value) noexcept { return static_cast<UnsignedIntegral>(value); }
	template <std::_Has_class_or_enum_type T> constexpr Size EnumToSizeType(T const &value) noexcept { return static_cast<Size>(value); }
	template <std::_Has_class_or_enum_type T> constexpr USize EnumToUnsignedSizeType(T const &value) noexcept { return static_cast<USize>(value); }
	template <std::_Has_class_or_enum_type T> constexpr Byte EnumToByte(T const &value) noexcept { return static_cast<Byte>(value); }
}

#endif