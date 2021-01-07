#ifndef _MICRON_CORE_EVENT_EVENT_H
#define _MICRON_CORE_EVENT_EVENT_H

#include "EventCategory.h"

namespace Micron
{
	class Event
	{
	public:
		inline Event() noexcept = default;
		virtual inline ~Event() noexcept = default;

		virtual constexpr EventCategory GetCategory() const noexcept { return EventCategory::None; }
	};
}

#endif