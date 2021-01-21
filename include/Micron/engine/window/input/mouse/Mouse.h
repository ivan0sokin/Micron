#ifndef _MICRON_WINDOW_INPUT_MOUSE_H
#define _MICRON_WINDOW_INPUT_MOUSE_H

#include "MouseInputEvents.h"

namespace Micron
{
	class Window;
	class Mouse
	{
		friend class ::Micron::Window;
	public:
		struct ButtonStates
		{
			Bool isLeftPressed = false;
			Bool isMiddlePressed = false;
			Bool isRightPressed = false;
		};
	public:
		Mouse() noexcept;
		inline ~Mouse() noexcept = default;
		inline Mouse(Mouse const &other) = delete;
		inline Mouse(Mouse &&other) = delete;

		constexpr Position const & GetLastPosition() const noexcept { return lastPosition; }
		constexpr Int64 GetLastPositionX() const noexcept { return lastPosition.x; }
		constexpr Int64 GetLastPositionY() const noexcept { return lastPosition.y; }

		constexpr ButtonStates const & GetLastButtonStates() const noexcept { return lastButtonStates; }
		constexpr Bool IsLeftPressed() const noexcept { return lastButtonStates.isLeftPressed; }
		constexpr Bool IsRightPressed() const noexcept { return lastButtonStates.isRightPressed; }
		constexpr Bool IsMiddlePressed() const noexcept { return lastButtonStates.isMiddlePressed; }

		constexpr Bool IsInWindow() const noexcept { return isInWindow; }

		constexpr Void EnableRawInput() noexcept { isRawInputEnabled = true; }
		constexpr Void DisableRawInput() noexcept { isRawInputEnabled = false; }
		constexpr Bool IsRawInputEnabled() const noexcept { return isRawInputEnabled; }

		constexpr Void EnableCursor() noexcept { isCursorEnabled = true; }
		constexpr Void DisableCursor() noexcept { isCursorEnabled = false; }
		constexpr Bool IsCursorEnabled() const noexcept { return isCursorEnabled; }

		constexpr Int32 GetLastWheelOffset() const noexcept { return lastOffset; }
	private:
		Void OnMouseMove(Int32 x, Int32 y) noexcept;
		Void OnRawMouseMove(Int32 dx, Int32 dy) noexcept;

		Void OnLeftReleased(Int32 x, Int32 y) noexcept;
		Void OnLeftPressed(Int32 x, Int32 y) noexcept;
		Void OnMiddleReleased(Int32 x, Int32 y) noexcept;
		Void OnMiddlePressed(Int32 x, Int32 y) noexcept;
		Void OnRightReleased(Int32 x, Int32 y) noexcept;
		Void OnRightPressed(Int32 x, Int32 y) noexcept;

		Void OnWheelMove(Int32 deltaOffset, Int32 x, Int32 y) noexcept;

		Void OnMouseEnter() noexcept;
		Void OnMouseLeave() noexcept;
	private:
		Position lastPosition;
		RawDelta lastRawMove;
		ButtonStates lastButtonStates;
		Int32 lastOffset = 0;

		Bool isInWindow = false;
		Bool isRawInputEnabled = false;
		Bool isCursorEnabled = true;
	};
}

#endif