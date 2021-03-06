#ifndef _MICRON_WINDOW_WINDOW_PREFERENCES_H
#define _MICRON_WINDOW_WINDOW_PREFERENCES_H

#include "../core/Core.h"

namespace Micron
{
	enum class PositionType : UInt16
	{
		Any = 0,
		Centered
	};

	class WindowPreferences
	{
	public:
		inline WindowPreferences() noexcept = default;
		inline ~WindowPreferences() noexcept = default;

		constexpr WindowPreferences & Title(MultibyteStringView title) noexcept { this->title = title; return *this; }
		constexpr WindowPreferences & Resolution(Resolution const &resolution) noexcept { this->resolution = resolution; return *this; };
		constexpr WindowPreferences & Position(Position const &position) noexcept { this->position = position; return *this; }
		constexpr WindowPreferences & PositionType(PositionType const &positionType) noexcept { this->positionType = positionType; return *this; }

		inline MultibyteStringView GetTitle() const noexcept { return title; }
		inline ::Micron::Resolution GetResolution() const noexcept { return resolution; }
		inline ::Micron::Position GetPosition() const noexcept { return position; }
		inline ::Micron::PositionType GetPositionType() const noexcept { return positionType; }
	private:
		MultibyteStringView title;
		::Micron::Resolution resolution;
		::Micron::Position position;
		::Micron::PositionType positionType = PositionType::Any;
	};
}

#endif