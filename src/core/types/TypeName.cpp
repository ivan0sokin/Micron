#include "TypeName.h"

namespace Micron
{
	static Array<String, 16> const basicTypesAsStrings =
	{
		"Int8",
		"Int16",
		"Int32",
		"Int64",
		"UInt8",
		"UInt16",
		"UInt32",
		"UInt64",
		"Float32",
		"Float64",
		"Float128",
		"Bool",
		"Void",
		"Byte",
		"String",
		"StringView"
	};

	static Array<String, 10> const mathTypesAsStrings =
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
	
	String TypeName::ToString(BasicType const &type) noexcept
	{
		return basicTypesAsStrings[EnumToUnsignedSizeType(type)];
	}

	String TypeName::ToString(MathType const &type) noexcept
	{
		return mathTypesAsStrings[EnumToUnsignedSizeType(type)];
	}
}