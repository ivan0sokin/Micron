#include "KeyboardInputEvents.h"

namespace Micron
{
	static Array<MultibyteString, 3> const keyActionEventTypesAsStrings =
	{
		"None",
		"Release",
		"Press"
	};

	MultibyteString ToString(KeyActionEventType const &keyActionEventType) noexcept
	{
		return keyActionEventTypesAsStrings[EnumToUnsignedSizeType(keyActionEventType)];
	}
}