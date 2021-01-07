#include "Input.h"

#include "../../core/Application.h"

namespace Micron
{
	void Input::Reset() noexcept
	{
		keyboard = MakeBox<Keyboard>();
		mouse = MakeBox<Mouse>();
		eventBuffer = MakeBox<EventBuffer>(64);
	}

	Optional<EventRc> Input::PeekEvent() noexcept
	{
		if (eventBuffer->Size() > static_cast<USize>(0))
		{
			EventRc event = eventBuffer->Front();
			eventBuffer->Pop();
			return event;
		}

		return std::nullopt;
	}

	Void Input::EnableAutorepeat() noexcept
	{
		Application::GetInstance()->window->EnableAutorepeat();
		keyboard->EnableAutorepeat();
	}

	Void Input::DisableAutorepeat() noexcept
	{
		Application::GetInstance()->window->DisableAutorepeat();
		keyboard->DisableAutorepeat();
	}

	Void Input::EnableRawMouseInput() noexcept
	{
		Application::GetInstance()->window->EnableRawMouseInput();
		mouse->EnableRawInput();
	}

	Void Input::DisableRawMouseInput() noexcept
	{
		Application::GetInstance()->window->DisableRawMouseInput();
		mouse->DisableRawInput();
	}

	Void Input::EnableCursor() noexcept
	{
		Application::GetInstance()->window->EnableCursor();
		mouse->EnableCursor();
	}

	Void Input::DisableCursor() noexcept
	{
		Application::GetInstance()->window->DisableCursor();
		mouse->DisableCursor();
	}
}