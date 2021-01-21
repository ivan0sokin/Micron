#ifndef _MICRON_WINDOW_INPUT_MOUSE_BUTTON_MAPPINGS_H
#define _MICRON_WINDOW_INPUT_MOUSE_BUTTON_MAPPINGS_H

#include <IOWindow/IOMouseButtons.h>

#include "../../../core/Core.h"

#define MAX_MOUSE_BUTTONS 64

namespace Micron
{
	enum class Button : UInt16
	{
		Left = IO_MOUSE_BUTTON_LEFT,
		Right = IO_MOUSE_BUTTON_RIGHT,
		Middle = IO_MOUSE_BUTTON_MIDDLE,
		Backward = IO_MOUSE_BUTTON_4,
		Forward = IO_MOUSE_BUTTON_5
	};

	MultibyteString ToString(Button const &button) noexcept;
}

#endif