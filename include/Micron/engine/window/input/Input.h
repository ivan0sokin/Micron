#ifndef _MICRON_WINDOW_INPUT_INPUT_H
#define _MICRON_WINDOW_INPUT_INPUT_H

#include "../../core/Core.h"

#include "keyboard/Keyboard.h"
#include "mouse/Mouse.h"

namespace Micron
{
	class Window;

	class Input
	{
		friend class ::Micron::Window;
	public:
		inline Input() noexcept = delete;
		inline ~Input() noexcept = delete;

		static void Reset() noexcept;

		static Optional<EventRc> PeekEvent() noexcept;

		inline static Bool IsEventBufferEmpty() noexcept { return eventBuffer.IsEmpty(); }
		inline static USize EventBufferSize() noexcept { return eventBuffer.Size(); }
		inline static Void ResizeEventBuffer(USize newSize) noexcept { eventBuffer.Resize(newSize); }
		inline static Void FlushEventBuffer() noexcept { eventBuffer.Flush(); }

		inline static Bool IsKeyPressed(Keycode const &keycode) noexcept { return keyboard->IsKeyPressed(keycode); }

		static Void EnableAutorepeat() noexcept;
		static Void DisableAutorepeat() noexcept;
		constexpr static Bool IsAutorepeatEnabled() noexcept { return keyboard->IsAutorepeatEnabled(); }

		constexpr static Bool IsMouseInWindow() noexcept { return mouse->IsInWindow(); }

		constexpr static Position const & GetLastMousePosition() noexcept { return mouse->GetLastPosition();; }
		constexpr static Mouse::ButtonStates const & GetLastMouseButtonStates() noexcept { return mouse->GetLastButtonStates(); }

		constexpr static Int64 GetLastMouseX() noexcept { return mouse->GetLastPositionX(); }
		constexpr static Int64 GetLastMouseY() noexcept { return mouse->GetLastPositionY(); }
		constexpr static Bool IsLeftButtonPressed() noexcept { return mouse->IsLeftPressed(); }
		constexpr static Bool IsMiddleButtonPressed() noexcept { return mouse->IsMiddlePressed(); }
		constexpr static Bool IsRightButtonPressed() noexcept { return mouse->IsRightPressed(); }

		static Void EnableRawMouseInput() noexcept;
		static Void DisableRawMouseInput() noexcept;
		constexpr static Bool IsRawMouseInputEnabled() noexcept { return mouse->IsRawInputEnabled(); }

		static Void EnableCursor() noexcept;
		static Void DisableCursor() noexcept;
		constexpr static Bool IsCursorEnabled() noexcept { return mouse->IsCursorEnabled(); }

		constexpr static Int32 GetLastMouseWheelOffset() noexcept { return mouse->GetLastWheelOffset(); }
	private:
		inline static Box<Keyboard> keyboard;
		inline static Box<Mouse> mouse;
		inline static EventBuffer eventBuffer = EventBuffer(64);
	};
}

#endif