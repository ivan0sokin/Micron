#ifndef _MICRON_ENGINE_CORE_STRING_CONVERTER_H
#define _MICRON_ENGINE_CORE_STRING_CONVERTER_H

#include "types/ContainerTypes.h"

namespace Micron
{
	class StringConverter
	{
	public:
		static UnicodeString MultibyteToUnicode(MultibyteString const &multibyteString) noexcept;
		static MultibyteString UnicodeToMultibyte(UnicodeString const &unicodeString) noexcept;
	};
}

#endif