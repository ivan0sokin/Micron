#include "Window.h"

#include "../application/Application.h"

namespace Micron
{
	Window::Window() noexcept
	{
		Input::Reset();
		this->SetCallbacks();
		this->InitializeScreenResolution();
	}

	Void Window::SetPreferences(WindowPreferences const &preferences) noexcept
	{
		title = preferences.GetTitle();
		if (title.empty())
			CoreLogger::Warn("Window title is empty");

		Resolution const requiredResolution = preferences.GetResolution();
		if (CheckResolutionIsValid(requiredResolution))
			resolution = requiredResolution;
		else
		{
			resolution = minimumResolution;
			CoreLogger::Error("Required window resolution is invalid. Switching to minimum");
		}

		switch (preferences.GetPositionType())
		{
		case PositionType::Any:
		{
			Position const requiredPosition = preferences.GetPosition();
			if (CheckPositionIsValid(requiredPosition))
				position = requiredPosition;
			else
			{
				position = { 0, 0 };
				CoreLogger::Error("Required window position is invalid. Moving to left upper corner");
			}

			break;
		}
		case PositionType::Centered:
		{
			position = this->GetPositionCentered();
			break;
		}
		default:
			break;
		}
	}

	Void Window::SetMinimumResolution(Resolution const &resolution) noexcept
	{
		minimumResolution = resolution;
		internalWindow.SetMinimumResolution({ resolution.width, resolution.height });
	}

	Void Window::SetMaximumResolution(Resolution const &resolution) noexcept
	{
		maximumResolution = resolution;
		internalWindow.SetMaximumResolution({ resolution.width, resolution.height });
	}

	Void Window::SetMaximumPosition(Position const &position) noexcept
	{
		maximumPosition = position;
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
			_MICRON_DEBUG_LOG("KillFocusEvent()");
			Input::keyboard->ClearStates();
		});
		
		internalWindow.OnMove([&](Int32 x, Int32 y)
		{
			_MICRON_DEBUG_LOG("WindowMoveEvent(position: ({0}, {1}))", x, y);
			position.x = x;
			position.y = y;
		});

		internalWindow.OnResize([&](UInt32 width, UInt32 height)
		{
			_MICRON_DEBUG_LOG("WindowResizeEvent(resolution: {0}x{1})", width, height);
			resolution.width = width;
			resolution.height = height;
		});

		internalWindow.OnScreenResize([&](UInt32 width, UInt32 height)
		{
			_MICRON_DEBUG_LOG("ScreenResizeEvent(resolution: {0}x{1})", width, height);
			screenResolution.width = width;
			screenResolution.height = height;
		});

		internalWindow.OnClose([&]()
		{
			_MICRON_DEBUG_LOG("WindowCloseEvent()");
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
				_MICRON_DEBUG_LOG("KeyReleaseEvent(keycode: \"{0}\", scancode: {1})", ToString(static_cast<Keycode>(keycode)), scancode);
				Input::eventBuffer.Push(std::move(MakeRc<KeyReleaseEvent>(Key{ static_cast<Keycode>(keycode), scancode })));
				Input::keyboard->OnKeyRelease(static_cast<Keycode>(keycode));
				break;
			case IO_KEY_PRESS:
				_MICRON_DEBUG_LOG("KeyPressEvent(keycode: \"{0}\", scancode: {1})", ToString(static_cast<Keycode>(keycode)), scancode);
				Input::eventBuffer.Push(std::move(MakeRc<KeyPressEvent>(Key{ static_cast<Keycode>(keycode), scancode })));
				Input::keyboard->OnKeyPress(static_cast<Keycode>(keycode)); 
				break;
			default:
				break;
			}
		});

		internalWindow.OnMouseMove([&](Int32 x, Int32 y)
		{
			_MICRON_DEBUG_LOG("MouseMoveEvent(position: ({0}, {1}))", x, y);
			Input::eventBuffer.Push(std::move(MakeRc<MouseMoveEvent>(Position{ x, y })));
			Input::mouse->OnMouseMove(x, y);
		});

		internalWindow.OnRawMouseMove([&](Int32 dx, Int32 dy)
		{
			_MICRON_DEBUG_LOG("MouseRawMoveEvent(rawDelta: ({0}, {1}))", dx, dy);
			Input::eventBuffer.Push(std::move(MakeRc<MouseRawMoveEvent>(RawDelta{ dx, dy })));
			Input::mouse->OnRawMouseMove(dx, dy);
		});
		
		internalWindow.OnMouseInput([&](UInt32 button, UInt32 action, Int32 x, Int32 y)
		{
			switch (action)
			{
			case IO_MOUSE_BUTTON_RELEASE:
				_MICRON_DEBUG_LOG("ButtonReleaseEvent(button: {0}, position: ({1}, {2}))", ToString(static_cast<Button>(button)), x, y);
				Input::eventBuffer.Push(std::move(MakeRc<ButtonReleaseEvent>(static_cast<Button>(button), Position{ x, y })));
				this->OnMouseButtonReleased(button, Position{ x, y });
				break;
			case IO_MOUSE_BUTTON_PRESS:
				_MICRON_DEBUG_LOG("ButtonPressEvent(button: {0}, position: ({1}, {2}))", ToString(static_cast<Button>(button)), x, y);
				Input::eventBuffer.Push(std::move(MakeRc<ButtonPressEvent>(static_cast<Button>(button), Position{ x, y })));
				this->OnMouseButtonPressed(button, Position{ x, y });
				break;
			default:
				break;
			}
		});

		internalWindow.OnMouseScroll([&](Int32 deltaOffset, Int32 x, Int32 y)
		{
			_MICRON_DEBUG_LOG("WheelScrollEvent(deltaOffset: {0}, position: ({1}, {2}))", deltaOffset, x, y);
			Input::eventBuffer.Push(std::move(MakeRc<WheelScrollEvent>(deltaOffset, Position{ x, y })));
			Input::mouse->OnWheelMove(deltaOffset, x, y);
		});

		internalWindow.OnMouseEnter([&](UInt32 action)
		{
			switch (action)
			{
			case IO_MOUSE_ENTER:
				_MICRON_DEBUG_LOG("MouseEnterEvent()");
				Input::eventBuffer.Push(std::move(MakeRc<MouseEnterEvent>()));
				Input::mouse->OnMouseEnter();
				break;
			case IO_MOUSE_LEAVE:
				_MICRON_DEBUG_LOG("MouseLeaveEvent()");
				Input::eventBuffer.Push(std::move(MakeRc<MouseLeaveEvent>()));
				Input::mouse->OnMouseLeave();
				break;
			default:
				break;
			}
		});
	}

	Void Window::InitializeScreenResolution() noexcept
	{
		auto screenResolution = internalWindow.GetScreenResolution();

		Window::screenResolution.width = screenResolution.first;
		Window::screenResolution.height = screenResolution.second;
	}

	Bool Window::CheckResolutionIsValid(Resolution const &resolution) const noexcept
	{
		return
		(
			resolution.width > minimumResolution.width &&
			resolution.height > minimumResolution.height &&
			resolution.width < maximumResolution.width &&
			resolution.height < maximumResolution.height
		);
	}

	Bool Window::CheckPositionIsValid(Position const &position) const noexcept
	{
		return
		(
			position.x < maximumPosition.x &&
			position.y < maximumPosition.y
		);
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

	Bool Window::Open() noexcept
	{
		return internalWindow.Create(title, { resolution.width, resolution.height }, { position.x, position.y });
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

	Void Window::OnScreenResolutionChange(Resolution const &screenResolution) noexcept
	{
		Window::screenResolution = screenResolution;
	}

	Position Window::GetPositionCentered() noexcept
	{
		Position centeredPosition = Position
		{
			static_cast<Int32>((screenResolution.width - resolution.width) * 0.5f),
			static_cast<Int32>((screenResolution.height - resolution.height) * 0.5f)
		};

		return centeredPosition;
	}

	Bool Window::SetTitle(MultibyteStringView title) noexcept
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

	Bool Window::SetPosition(Position const &position) noexcept
	{
		Bool internalWindowPositionChanged = internalWindow.SetPosition({ position.x, position.y });
		if (internalWindowPositionChanged)
			this->position = position;

		return internalWindowPositionChanged;
	}
	
	Bool Window::SetPositionCentered() noexcept
	{
		Position const centeredPosition = this->GetPositionCentered();
		
		return this->SetPosition(centeredPosition);
	}

	Bool Window::SetScreenResolution(Resolution const &screenResolution) noexcept
	{
		return internalWindow.SetScreenResolution({ screenResolution.width, screenResolution.height });
	}
}