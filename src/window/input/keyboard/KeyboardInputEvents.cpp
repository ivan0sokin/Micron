#include "KeyboardInputEvents.h"

namespace Micron
{
	static Array<String, 3> const keyActionEventTypesAsStrings =
	{
		"None",
		"Release",
		"Press"
	};

	String ToString(KeyActionEventType const &keyActionEventType) noexcept
	{
		return keyActionEventTypesAsStrings[EnumToUnsignedSizeType(keyActionEventType)];
	}
}