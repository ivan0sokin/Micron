#ifndef _MICRON_WINDOW_H
#define _MICRON_WINDOW_H

#include "../core/Core.h"
#include "input/Input.h"

#include <IOWindow/IOWindow.h>

namespace Micron
{
	class Window
	{
	public:
		Window() noexcept = default;
		Window(StringView windowTitle, Resolution const &resolution) noexcept;
		~Window() noexcept = default;

		Bool Open() noexcept;
		Void Close() noexcept;

		Void ProcessInputEvents() noexcept;

		Void EnableAutorepeat() noexcept;
		Void DisableAutorepeat() noexcept;

		Void EnableRawMouseInput() noexcept;
		Void DisableRawMouseInput() noexcept;

		Void EnableCursor() noexcept;
		Void DisableCursor() noexcept;

		Void SetTitle(StringView title);
		Void SetWidth(UInt32 width);
		Void SetHeight(UInt32 height);
		Void SetResolution(Resolution const &resolution);
	private:
		Void OnMouseButtonPressed(UInt32 button, Position const &position) noexcept;
		Void OnMouseButtonReleased(UInt32 button, Position const &position) noexcept;
	private:
		StringView title;
		Resolution resolution;
	private:
		IOWindow internalWindow;
	};
}

#endif