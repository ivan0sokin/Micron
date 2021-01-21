#include "Platform.h"
#include "Enum.h"

namespace Micron
{
	static Array<MultibyteString, 3> const platformsAsStrings =
	{ 
		"Windows",
		"Linux",
		"MacOS"
	};
	
	MultibyteString ToString(Platform const &platform) noexcept { return platformsAsStrings[EnumToUnsignedSizeType(platform)]; }
}