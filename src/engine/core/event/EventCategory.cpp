#include "EventCategory.h"
#include "../Enum.h"

namespace Micron
{
	static Array<MultibyteString, 16> const eventCategoriesAsStrings =
	{
		"None",
		"KeyboardInput",
		"MouseInput"
	};

	MultibyteString ToString(EventCategory const &category) noexcept
	{ 
		return eventCategoriesAsStrings[EnumToUnsignedSizeType(category)];
	}
}