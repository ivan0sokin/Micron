#ifndef _MICRON_CORE_EVENT_EVENT_CATEGORY_H
#define _MICRON_CORE_EVENT_EVENT_CATEGORY_H

#include "../types/BasicTypes.h"
#include "../types/ContainerTypes.h"
#include "../Enum.h"

namespace Micron
{
	enum class EventCategory : UInt16
	{
		None = 0,
		KeyboardInput,
		MouseInput
	};

	String ToString(EventCategory const &category) noexcept;
}

#endif