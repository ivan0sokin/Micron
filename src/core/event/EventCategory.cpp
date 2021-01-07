#include "EventCategory.h"

namespace Micron
{
	static Array<String, 16> const eventCategoriesAsStrings =
	{
		"None",
		"KeyboardInput",
		"MouseInput"
	};

	String ToString(EventCategory const &category) noexcept
	{ 
		return eventCategoriesAsStrings[EnumToUnsignedSizeType(category)];
	}
}