#include "TypeName.h"

#include <boost/type_index.hpp>

namespace Micron
{
	static Array<MultibyteString, 18> const basicTypesAsStrings =
	{
		"Int8",
		"Int16",
		"Int32",
		"Int64",
		"UInt8",
		"UInt16",
		"UInt32",
		"UInt64",
		"Real32",
		"Real64",
		"Float128",
		"Bool",
		"Void",
		"Byte",
		"MultibyteString",
		"MultibyteStringView",
		"UnicodeString",
		"UnicodeStringView"
	};

	static Array<MultibyteString, 10> const mathTypesAsStrings =
	{
		"Vector2f",
		"Vector3f",
		"Vector4f",
		"Vector2i",
		"Vector3i",
		"Vector4i",
		"Matrix2x2",
		"Matrix3x3",
		"Matrix4x4",
		"Quaternion"
	};
	
	MultibyteString TypeName::ToString(BasicType const &type) noexcept
	{
		return basicTypesAsStrings[EnumToUnsignedSizeType(type)];
	}

	MultibyteString TypeName::ToString(MathType const &type) noexcept
	{
		return mathTypesAsStrings[EnumToUnsignedSizeType(type)];
	}
}