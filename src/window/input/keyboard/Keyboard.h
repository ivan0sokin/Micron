#ifndef _MICRON_WINDOW_INPUT_KEYBOARD_KEYBOARD_H
#define _MICRON_WINDOW_INPUT_KEYBOARD_KEYBOARD_H

#include "KeyboardInputEvents.h"

namespace Micron
{
	class Window;
	class Keyboard
	{
		friend class ::Micron::Window;
	public:
		Keyboard() noexcept;
		inline ~Keyboard() noexcept = default;
		inline Keyboard(Keyboard const &other) = delete;
		inline Keyboard(Keyboard &&other) = delete;

		inline Bool IsKeyPressed(Keycode const &keycode) noexcept { return keyStates[EnumToUnsignedSizeType(keycode)]; }

		Void ClearStates() noexcept;

		inline Void EnableAutorepeat() noexcept { isAutorepeatEnabled = true; }
		inline Void DisableAutorepeat() noexcept { isAutorepeatEnabled = false; }
		constexpr Bool IsAutorepeatEnabled() const noexcept { return isAutorepeatEnabled; }
	private:
		Void OnKeyPress(Keycode const& keycode) noexcept;
		Void OnKeyRelease(Keycode const& keycode) noexcept;
	private:
		constexpr static USize maxKeysSupported = 512;
	private:
		Bool isAutorepeatEnabled = false;
		BitSet<maxKeysSupported> keyStates;
	};
}

#endif