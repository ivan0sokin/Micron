#include "DateTime.h"
#include "../Enum.h"

namespace Micron
{
	static std::tm GetLocalTimeStructure() noexcept;
	static std::tm GetGreenwichTimeStructure() noexcept;

	Date Micron::DateTime::GetCurrentDate() noexcept
	{
		std::tm tmLocal = GetLocalTimeStructure();
		return Date{ static_cast<UInt32>(tmLocal.tm_mday), static_cast<UInt32>(tmLocal.tm_yday + 1), static_cast<Weekday>(tmLocal.tm_wday), static_cast<Month>(tmLocal.tm_mon), static_cast<UInt32>(tmLocal.tm_year + 1900) };
	}

	Time DateTime::GetCurrentLocalTime() noexcept
	{
		std::tm tmLocal = GetLocalTimeStructure();
		return Time{ static_cast<UInt32>(tmLocal.tm_hour), static_cast<UInt32>(tmLocal.tm_min), static_cast<UInt32>(tmLocal.tm_sec) };
	}

	Time DateTime::GetCurrentGreenwichTime() noexcept
	{
		std::tm tmGreenwich = GetGreenwichTimeStructure();
		return Time{ static_cast<UInt32>(tmGreenwich.tm_hour), static_cast<UInt32>(tmGreenwich.tm_min), static_cast<UInt32>(tmGreenwich.tm_sec) };
	}

	static Array<MultibyteString, 7> const weekdaysAsString =
	{
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday",
		"Sunday"
	};

	MultibyteString ToString(Weekday const &weekday) noexcept
	{
		return weekdaysAsString[EnumToUnsignedSizeType(weekday)];
	}

	static Array<MultibyteString, 12> const monthsAsStrings =
	{
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	MultibyteString ToString(Month const &month) noexcept
	{
		return monthsAsStrings[EnumToUnsignedSizeType(month)];
	}

	static std::tm GetLocalTimeStructure() noexcept
	{
		std::time_t now = std::time(nullptr);

		std::tm result;
		errno_t lastError = localtime_s(&result, &now);

		if (lastError != 0)
			return std::tm{ };

		return result;
	}

	static std::tm GetGreenwichTimeStructure() noexcept
	{
		std::time_t now = std::time(nullptr);
		
		std::tm result;
		errno_t lastError = gmtime_s(&result, &now);

		if (lastError != 0)
			return std::tm{ };

		return result;
	}
}