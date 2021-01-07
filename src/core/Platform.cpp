#include "Platform.h"

namespace Micron
{
	static Array<String, 3> const platformsAsStrings =
	{ 
		"Windows",
		"Linux",
		"MacOS"
	};
	
	String ToString(Platform const &platform) noexcept { return platformsAsStrings[EnumToUnsignedSizeType(platform)]; }
}