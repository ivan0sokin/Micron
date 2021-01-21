#ifndef _MICRON_WINDOW_H
#define _MICRON_WINDOW_H

#include "../core/Core.h"
#include "input/Input.h"

#include <IOWindow/IOWindow.h>

namespace Micron
{
	struct Resolution
	{
		UInt32 width, height;
	};

	class Window
	{
	public:
		Window() noexcept = default;
		Window(UnicodeStringView title, Resolution const& resolution) noexcept;
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

		Bool SetTitle(UnicodeStringView title) noexcept;
		Bool SetResolution(Resolution const &resolution) noexcept;
		Bool SetPosition(Position const &position) noexcept;
		Bool SetPositionCentered() noexcept;

		inline UnicodeStringView GetTitle() const noexcept { return title; }
		inline UInt32 GetWidth() const noexcept { return resolution.width; }
		inline UInt32 GetHeight() const noexcept { return resolution.height; }
		inline Resolution GetResolution() const noexcept { return resolution; }

		Void SetMinimumResolution(Resolution const& resolution) noexcept;
		Void SetMaximumResolution(Resolution const& resolution) noexcept;
		Void SetMaximumPosition(Position const& position) noexcept;

		constexpr static UnicodeStringView DefaultTitle() noexcept { return L"Titleless window"; }
		constexpr static Resolution DefaultResolution() noexcept { return { 480, 360 }; }
	private:
		Void SetCallbacks() noexcept;
		Void SetWindowCallbacks() noexcept;
		Void SetInputCallbacks() noexcept;

		Void OnMouseButtonPressed(UInt32 button, Position const &position) noexcept;
		Void OnMouseButtonReleased(UInt32 button, Position const &position) noexcept;
	private:
		UnicodeString title;
		Resolution resolution;
		Position position;
	private:
		IOWindow internalWindow;
	};
}

#endif