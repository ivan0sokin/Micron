#include "Window.h"

#include "../application/Application.h"

namespace Micron
{
	Window::Window(UnicodeStringView title, Resolution const &resolution) noexcept :
		title{ title }, resolution{ resolution }
	{
		Input::Reset();
		this->SetCallbacks();
	}

	Void Window::SetMinimumResolution(Resolution const &resolution) noexcept
	{
		internalWindow.SetMinimumResolution({ resolution.width, resolution.height });
	}

	Void Window::SetMaximumResolution(Resolution const &resolution) noexcept
	{
		internalWindow.SetMaximumResolution({ resolution.width, resolution.height });
	}

	Void Window::SetMaximumPosition(Position const &position) noexcept
	{
		internalWindow.SetMaximumPosition({ position.x, position.y });
	}

	Void Window::SetCallbacks() noexcept
	{
		this->SetWindowCallbacks();
		this->SetInputCallbacks();
	}

	Void Window::SetWindowCallbacks() noexcept
	{
		internalWindow.OnKillFocus([&]()
		{
			Input::keyboard->ClearStates();
			_MICRON_DEBUG_LOG("KillFocusEvent()");
		});
		
		internalWindow.OnMove([&](Int32 x, Int32 y)
		{
			position.x = x;
			position.y = y;
			_MICRON_DEBUG_LOG("WindowMoveEvent(position: ({0}, {1}))", x, y);
		});

		internalWindow.OnResize([&](UInt32 width, UInt32 height)
		{
			resolution.width = width;
			resolution.height = height;
			_MICRON_DEBUG_LOG("WindowResizeEvent(resolution: {0}x{1})", width, height);
		});

		internalWindow.OnClose([&]()
		{
			Application::GetInstance()->Shutdown();
		});
	}

	Void Window::SetInputCallbacks() noexcept
	{
		internalWindow.OnKeyboardInput([&](UInt32 keycode, UInt32 scancode, UInt32 action)
		{
			switch (action)
			{
			case IO_KEY_RELEASE:
				Input::eventBuffer.Push(std::move(MakeRc<KeyReleaseEvent>(Key{ static_cast<Keycode>(keycode), scancode })));
				Input::keyboard->OnKeyRelease(static_cast<Keycode>(keycode)); _MICRON_DEBUG_LOG("KeyReleaseEvent(keycode: \"{0}\", scancode: {1})", ToString(static_cast<Keycode>(keycode)), scancode);
				break;
			case IO_KEY_PRESS:
				Input::eventBuffer.Push(std::move(MakeRc<KeyPressEvent>(Key{ static_cast<Keycode>(keycode), scancode })));
				Input::keyboard->OnKeyPress(static_cast<Keycode>(keycode)); _MICRON_DEBUG_LOG("KeyPressEvent(keycode: \"{0}\", scancode: {1})", ToString(static_cast<Keycode>(keycode)), scancode);
				break;
			default:
				break;
			}
		});

		internalWindow.OnMouseMove([&](Int32 x, Int32 y)
		{
			Input::eventBuffer.Push(std::move(MakeRc<MouseMoveEvent>(Position{ x, y })));
			Input::mouse->OnMouseMove(x, y); _MICRON_DEBUG_LOG("MouseMoveEvent(position: ({0}, {1}))", x, y);
		});

		internalWindow.OnRawMouseMove([&](Int32 dx, Int32 dy)
		{
			Input::eventBuffer.Push(std::move(MakeRc<MouseRawMoveEvent>(RawDelta{ dx, dy })));
			Input::mouse->OnRawMouseMove(dx, dy); _MICRON_DEBUG_LOG("MouseRawMoveEvent(rawDelta: ({0}, {1}))", dx, dy);
		});
		
		internalWindow.OnMouseInput([&](UInt32 button, UInt32 action, Int32 x, Int32 y)
		{
			switch (action)
			{
			case IO_MOUSE_BUTTON_RELEASE:
				Input::eventBuffer.Push(std::move(MakeRc<ButtonReleaseEvent>(static_cast<Button>(button), Position{ x, y })));
				this->OnMouseButtonReleased(button, Position{ x, y }); _MICRON_DEBUG_LOG("ButtonReleaseEvent(button: {0}, position: ({1}, {2}))", ToString(static_cast<Button>(button)), x, y);
				break;
			case IO_MOUSE_BUTTON_PRESS:
				Input::eventBuffer.Push(std::move(MakeRc<ButtonPressEvent>(static_cast<Button>(button), Position{ x, y })));
				this->OnMouseButtonPressed(button, Position{ x, y }); _MICRON_DEBUG_LOG("ButtonPressEvent(button: {0}, position: ({1}, {2}))", ToString(static_cast<Button>(button)), x, y);
				break;
			default:
				break;
			}
		});

		internalWindow.OnMouseScroll([&](Int32 deltaOffset, Int32 x, Int32 y)
		{
			Input::eventBuffer.Push(std::move(MakeRc<WheelScrollEvent>(deltaOffset, Position{ x, y })));
			Input::mouse->OnWheelMove(deltaOffset, x, y); _MICRON_DEBUG_LOG("WheelScrollEvent(deltaOffset: {0}, position: ({1}, {2}))", deltaOffset, x, y);
		});

		internalWindow.OnMouseEnter([&](UInt32 action)
		{
			switch (action)
			{
			case IO_MOUSE_ENTER:
				Input::eventBuffer.Push(std::move(MakeRc<MouseEnterEvent>()));
				Input::mouse->OnMouseEnter(); _MICRON_DEBUG_LOG("MouseEnterEvent()");
				break;
			case IO_MOUSE_LEAVE:
				Input::eventBuffer.Push(std::move(MakeRc<MouseLeaveEvent>()));
				Input::mouse->OnMouseLeave(); _MICRON_DEBUG_LOG("MouseLeaveEvent()");
				break;
			default:
				break;
			}
		});
	}

	Void Window::OnMouseButtonPressed(UInt32 button, Position const &position) noexcept
	{
		switch (button)
		{
		case IO_MOUSE_BUTTON_LEFT:
			Input::mouse->OnLeftPressed(position.x, position.y);
			break;
		case IO_MOUSE_BUTTON_MIDDLE:
			Input::mouse->OnMiddlePressed(position.x, position.y);
			break;
		case IO_MOUSE_BUTTON_RIGHT:
			Input::mouse->OnRightPressed(position.x, position.y);
			break;
		default:
			break;
		}
	}

	Void Window::OnMouseButtonReleased(UInt32 button, Position const &position) noexcept
	{
		switch (button)
		{
		case IO_MOUSE_BUTTON_LEFT:
			Input::mouse->OnLeftReleased(position.x, position.y);
			break;
		case IO_MOUSE_BUTTON_MIDDLE:
			Input::mouse->OnMiddleReleased(position.x, position.y);
			break;
		case IO_MOUSE_BUTTON_RIGHT:
			Input::mouse->OnRightReleased(position.x, position.y);
			break;
		default:
			break;
		}
	}

	bool Window::Open() noexcept
	{
		return internalWindow.Create(title, { resolution.width, resolution.height });
	}

	Void Window::Close() noexcept
	{
		internalWindow.Close();
	}

	Void Window::ProcessInputEvents() noexcept
	{
		internalWindow.ProcessEvents();
	}

	Void Window::EnableAutorepeat() noexcept
	{
		internalWindow.EnableAutorepeat();
	}

	Void Window::DisableAutorepeat() noexcept
	{
		internalWindow.DisableAutorepeat();
	}

	Void Window::EnableRawMouseInput() noexcept
	{
		internalWindow.EnableRawMouseInput();
	}

	Void Window::DisableRawMouseInput() noexcept
	{
		internalWindow.DisableRawMouseInput();
	}

	Void Window::EnableCursor() noexcept
	{
		internalWindow.EnableMouseCursor();
	}

	Void Window::DisableCursor() noexcept
	{
		internalWindow.DisableMouseCursor();
	}

	Bool Window::SetTitle(UnicodeStringView title) noexcept
	{
		Bool internalWindowTitleChanged = internalWindow.SetTitle(title);
		if (internalWindowTitleChanged)
			this->title = title;

		return internalWindowTitleChanged;
	}

	Bool Window::SetResolution(Resolution const &resolution) noexcept
	{
		Bool internalWindowResolutionChanged = internalWindow.SetResolution({ resolution.width, resolution.height });
		if (internalWindowResolutionChanged)
			this->resolution = resolution;

		return internalWindowResolutionChanged;
	}

	Bool Window::SetPosition(Position const& position) noexcept
	{
		Bool internalWindowPositionChanged = internalWindow.SetPosition({ position.x, position.y });
		if (internalWindowPositionChanged)
			this->position = position;

		return internalWindowPositionChanged;
	}
	
	Bool Window::SetPositionCentered() noexcept
	{
		Position centeredPosition = Position
		{
			static_cast<Int32>((GetSystemMetrics(SM_CXSCREEN) - resolution.width) * 0.5f),
			static_cast<Int32>((GetSystemMetrics(SM_CYSCREEN) - resolution.height) * 0.5f)
		};

		Bool internalWindowPositionChanged = internalWindow.SetPosition({ centeredPosition.x, centeredPosition.y });
		if (internalWindowPositionChanged)
			this->position = position;
		
		return internalWindowPositionChanged;
	}
}