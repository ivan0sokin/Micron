#include "MouseInputEvents.h"

namespace Micron
{
	static Array<String, 7> const eventTypesAsStrings =
	{
		"None",
		"ButtonAction",
		"WheelScroll",
		"Move",
		"RawMove",
		"Enter",
		"Leave"
	};

	String Micron::ToString(MouseInputEventType const &mouseInputEventType) noexcept
	{
		return eventTypesAsStrings[EnumToUnsignedSizeType(mouseInputEventType)];
	}

	static Array<String, 3> const buttonActionEventTypesAsStrings =
	{
		"None",
		"Release",
		"Press"
	};

	String ToString(ButtonActionEventType const &buttonActionEventType) noexcept
	{
		return buttonActionEventTypesAsStrings[EnumToUnsignedSizeType(buttonActionEventType)];
	}
}