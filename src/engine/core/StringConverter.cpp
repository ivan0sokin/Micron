#include "StringConverter.h"

namespace Micron
{
	UnicodeString StringConverter::MultibyteToUnicode(MultibyteString const &multibyteString) noexcept
	{
		return UnicodeString(multibyteString.begin(), multibyteString.end());
	}

	MultibyteString StringConverter::UnicodeToMultibyte(UnicodeString const &unicodeString) noexcept
	{
		return MultibyteString(unicodeString.begin(), unicodeString.end());
	}
}