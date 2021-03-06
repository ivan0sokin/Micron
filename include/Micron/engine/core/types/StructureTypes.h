#ifndef _MICRON_CORE_TYPES_STRUCTURE_TYPES
#define _MICRON_CORE_TYPES_STRUCTURE_TYPES

#include "BasicTypes.h"

namespace Micron
{
	struct Position
	{
		Int32 x, y;
	};

	struct Resolution
	{
		UInt32 width, height;
	};
}

#endif