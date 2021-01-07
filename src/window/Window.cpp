#include "Window.h"

#include "../core/Application.h"

namespace Micron
{
	Window::Window(StringView windowTitle, Resolution const &resolution) noexcept :
		title{ windowTitle }, resolution{ resolution }
	{
		Input::Reset();

		internalWindow.OnKeyboardInput([&](UInt32 keycode, UInt32 scancode, UInt32 action)
		{
			switch(action)
			{ 
			case IO_KEY_RELEASE:
				Input::eventBuffer->Push(std::move(MakeRc<KeyReleaseEvent>(Key{ static_cast<Keycode>(keycode), scancode })));
				Input::keyboard->OnKeyRelease(static_cast<Keycode>(keycode));
				break;
			case IO_KEY_PRESS:
				Input::eventBuffer->Push(std::move(MakeRc<KeyPressEvent>(Key{ static_cast<Keycode>(keycode), scancode })));
				Input::keyboard->OnKeyPress(static_cast<Keycode>(keycode));
				break;
			default:
				break;
			}
		});

		internalWindow.OnKillFocus([&]()
		{
			Input::keyboard->ClearStates();
		});

		internalWindow.OnMouseMove([&](Int32 x, Int32 y)
		{
			Input::eventBuffer->Push(std::move(MakeRc<MouseMoveEvent>(Position{ x, y })));
			Input::mouse->OnMouseMove(x, y);
		});

		internalWindow.OnRawMouseMove([&](Int32 dx, Int32 dy)
		{
			Input::eventBuffer->Push(std::move(MakeRc<MouseRawMoveEvent>(RawDelta{ dx, dy })));
			Input::mouse->OnRawMouseMove(dx, dy);
		});
		
		internalWindow.OnMouseInput([&](UInt32 button, UInt32 action, Int32 x, Int32 y)
		{
			switch (action)
			{
			case IO_MOUSE_BUTTON_RELEASE:
				Input::eventBuffer->Push(std::move(MakeRc<ButtonReleaseEvent>(static_cast<Button>(button), Position{ x, y })));
				this->OnMouseButtonReleased(button, Position{ x, y });
				break;
			case IO_MOUSE_BUTTON_PRESS:
				Input::eventBuffer->Push(std::move(MakeRc<ButtonPressEvent>(static_cast<Button>(button), Position{ x, y })));
				this->OnMouseButtonPressed(button, Position{ x, y });
				break;
			default:
				break;
			}
		});

		internalWindow.OnMouseScroll([&](Int32 deltaOffset, Int32 x, Int32 y)
		{
			Input::eventBuffer->Push(std::move(MakeRc<WheelScrollEvent>(deltaOffset, Position{ x, y })));
			Input::mouse->OnWheelMove(deltaOffset, x, y);
		});

		internalWindow.OnMouseEnter([&](UInt32 action)
		{
			switch (action)
			{
			case IO_MOUSE_ENTER:
				Input::eventBuffer->Push(std::move(MakeRc<MouseEnterEvent>()));
				Input::mouse->OnMouseEnter();
				break;
			case IO_MOUSE_LEAVE:
				Input::eventBuffer->Push(std::move(MakeRc<MouseLeaveEvent>()));
				Input::mouse->OnMouseLeave();
				break;
			default:
				break;
			}
		});
		
		internalWindow.OnClose([&]()
		{
			Application::GetInstance()->ShutDown();
		});
	}

	bool Window::Open() noexcept
	{
		return internalWindow.Create(title, resolution.width, resolution.height);
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

	Void Window::SetTitle(StringView title)
	{
		// internalWindow.SetTitle(title);
	}

	Void Window::SetWidth(UInt32 width)
	{
		// internalWindow.SetWidth(width);
	}

	Void Window::SetHeight(UInt32 height)
	{
		// internalWindow.SetHeight(height);
	}

	Void Window::SetResolution(Resolution const &resolution)
	{
		// internalWindow.SetResolution(resolution.width, resolution.height);
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
}