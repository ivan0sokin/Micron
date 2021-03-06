#ifndef _MICRON_WINDOW_H
#define _MICRON_WINDOW_H

#include "WindowPreferences.h"
#include "input/Input.h"

#include <IOWindow/IOWindow.h>

namespace Micron
{

	class Application;
	class Window
	{
		friend class ::Micron::Input;
		friend class ::Micron::Application;
	public:
		Window() noexcept;
		~Window() noexcept = default;

		Void SetPreferences(WindowPreferences const &preferences) noexcept;

		inline MultibyteStringView GetTitle() const noexcept { return title; }
		inline UInt32 GetWidth() const noexcept { return resolution.width; }
		inline UInt32 GetHeight() const noexcept { return resolution.height; }
		inline Resolution GetResolution() const noexcept { return resolution; }
		inline Position GetPosition() const noexcept { return position; }
		Position GetPositionCentered() noexcept;
		inline Resolution GetScreenResolution() const noexcept { return screenResolution; }

		Bool SetTitle(MultibyteStringView title) noexcept;
		Bool SetResolution(Resolution const &resolution) noexcept;
		Bool SetPosition(Position const &position) noexcept;
		Bool SetPositionCentered() noexcept;
		Bool SetScreenResolution(Resolution const &screenResolution) noexcept;

		Void SetMinimumResolution(Resolution const &resolution) noexcept;
		Void SetMaximumResolution(Resolution const &resolution) noexcept;
		Void SetMaximumPosition(Position const &position) noexcept;

		constexpr static MultibyteStringView DefaultTitle() noexcept { return "Titleless window"; }
		constexpr static Resolution DefaultResolution() noexcept { return { 480, 360 }; }
	private:
		Bool Open() noexcept;
		Void Close() noexcept;

		Void ProcessInputEvents() noexcept;

		Void OnScreenResolutionChange(Resolution const& screenResolution) noexcept;

		Void EnableAutorepeat() noexcept;
		Void DisableAutorepeat() noexcept;

		Void EnableRawMouseInput() noexcept;
		Void DisableRawMouseInput() noexcept;

		Void EnableCursor() noexcept;
		Void DisableCursor() noexcept;
	private:
		Void SetCallbacks() noexcept;
		Void SetWindowCallbacks() noexcept;
		Void SetInputCallbacks() noexcept;
		Void InitializeScreenResolution() noexcept;

		Bool CheckResolutionIsValid(Resolution const& resolution) const noexcept;
		Bool CheckPositionIsValid(Position const& position) const noexcept;

		Void OnMouseButtonPressed(UInt32 button, Position const &position) noexcept;
		Void OnMouseButtonReleased(UInt32 button, Position const &position) noexcept;
	private:
		MultibyteStringView title;
		Resolution resolution;
		Position position;
		Resolution minimumResolution = { 0, 0 }, maximumResolution = { 0x7FFFFFFF, 0x7FFFFFFF };
		Position maximumPosition = { 0x7FFFFFFF, 0x7FFFFFFF };
	private:
		inline static Resolution screenResolution;
	private:
		IOWindow internalWindow;
	};
}

#endif