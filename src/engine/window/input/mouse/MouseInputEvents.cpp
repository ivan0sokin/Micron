#include "MouseInputEvents.h"

namespace Micron
{
	static Array<MultibyteString, 7> const eventTypesAsStrings =
	{
		"None",
		"ButtonAction",
		"WheelScroll",
		"Move",
		"RawMove",
		"Enter",
		"Leave"
	};

	MultibyteString Micron::ToString(MouseInputEventType const &mouseInputEventType) noexcept
	{
		return eventTypesAsStrings[EnumToUnsignedSizeType(mouseInputEventType)];
	}

	static Array<MultibyteString, 3> const buttonActionEventTypesAsStrings =
	{
		"None",
		"Release",
		"Press"
	};

	MultibyteString ToString(ButtonActionEventType const &buttonActionEventType) noexcept
	{
		return buttonActionEventTypesAsStrings[EnumToUnsignedSizeType(buttonActionEventType)];
	}
}