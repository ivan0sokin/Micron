#ifndef _MIRON_CORE_TIME_DATE_TIME_H
#define _MIRON_CORE_TIME_DATE_TIME_H

#include "../types/BasicTypes.h"
#include "../types/ContainerTypes.h"

#include <ctime>

namespace Micron
{
	enum class Month : UInt16
	{
		January = 0,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};

	MultibyteString ToString(Month const &month) noexcept;

	enum class Weekday : UInt16
	{
		Monday = 0,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday,
		Sunday
	};

	MultibyteString ToString(Weekday const &weekday) noexcept;

	struct Date
	{
		UInt32 monthday;
		UInt32 yearday;
		Weekday weekday;
		Month month;
		UInt32 year;
	};

	struct Time
	{
		UInt32 hour;
		UInt32 minute;
		UInt32 second;
	};

	class DateTime
	{
	public:
		static Date GetCurrentDate() noexcept;
		static Time GetCurrentLocalTime() noexcept;
		static Time GetCurrentGreenwichTime() noexcept;
	};
}

#endif