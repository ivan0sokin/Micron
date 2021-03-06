#ifndef _MICRON_CORE_TYPES_BASIC_TYPES_H
#define _MICRON_CORE_TYPES_BASIC_TYPES_H

#include <cstddef>
#include <cstdint>

typedef float float32_t;
typedef double float64_t;
typedef long double float128_t;

namespace std
{
	using ::float32_t;
	using ::float64_t;
	using ::float128_t;
}

namespace Micron
{
	using Size = std::ptrdiff_t;
	using USize = std::size_t;

	using Int8 = std::int8_t;
	using Int16 = std::int16_t;
	using Int32 = std::int32_t;
	using Int64 = std::int64_t;
	using UInt8 = std::uint8_t;
	using UInt16 = std::uint16_t;
	using UInt32 = std::uint32_t;
	using UInt64 = std::uint64_t;

	using Real32 = std::float32_t;
	using Real64 = std::float64_t;
	using Real128 = std::float128_t;
	
	using Bool = bool;
	using Void = void;
	using Byte = UInt8;

	using Char = char;
	using WideChar = wchar_t;
}

#endif 