#ifndef _MICRON_CORE_TYPENAME_H
#define _MICRON_CORE_TYPENAME_H

#include "BasicTypes.h"
#include "ContainerTypes.h"
#include "MathTypes.h"
#include "../Enum.h"

namespace Micron
{
	enum class BasicType : UInt16
	{
		INT8 = 0,
		INT16,
		INT32,
		INT64,
		UINT8,
		UINT16,
		UINT32,
		UINT64,
		FLOAT32,
		FLOAT64,
		FLOAT128,
		BOOL,
		
		BYTE,
		MULTIBYTESTRING,
		MULTIBYTESTRINGVIEW,
		UNICODESTRING,
		UNICODESTRINGVIEW
	};

	enum class MathType : UInt16
	{
		FVECTOR2 = 0,
		FVECTOR3,
		FVECTOR4,
		IVECTOR2,
		IVECTOR3,
		IVECTOR4,
		MATRIX2,
		MATRIX3,
		MATRIX4,
		QUATERNION
	};

	class TypeName
	{
	public:
		static MultibyteString ToString(BasicType const &type) noexcept;
		static MultibyteString ToString(MathType const &type) noexcept;
	};
}

#endif