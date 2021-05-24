#include "StringConverter.h"

namespace Micron
{
	UnicodeString StringConverter::MultibyteToUnicode(MultibyteString const &multibyteString) noexcept
	{
		return UnicodeString(multibyteString.cbegin(), multibyteString.cend());
	}

	MultibyteString StringConverter::UnicodeToMultibyte(UnicodeString const &unicodeString) noexcept
	{
		return MultibyteString(unicodeString.cbegin(), unicodeString.cend());
	}
}