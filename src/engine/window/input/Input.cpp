#include "Input.h"

#include "../../application/Application.h"

namespace Micron
{
	void Input::Reset() noexcept
	{
		keyboard = MakeBox<Keyboard>();
		mouse = MakeBox<Mouse>();
	}

	Optional<EventRc> Input::PeekEvent() noexcept
	{
		if (eventBuffer.Size() > static_cast<USize>(0))
		{
			EventRc event = eventBuffer.Front();
			eventBuffer.Pop();
			return event;
		}

		return std::nullopt;
	}

	Void Input::EnableAutorepeat() noexcept
	{
		Application::GetInstance()->window->EnableAutorepeat();
		keyboard->EnableAutorepeat();

		CoreLogger::Info("Autorepeat enabled");
	}

	Void Input::DisableAutorepeat() noexcept
	{
		Application::GetInstance()->window->DisableAutorepeat();
		keyboard->DisableAutorepeat();

		CoreLogger::Info("Autorepeat disabled");
	}

	Void Input::EnableRawMouseInput() noexcept
	{
		Application::GetInstance()->window->EnableRawMouseInput();
		mouse->EnableRawInput();

		CoreLogger::Info("Raw mouse input enabled");
	}

	Void Input::DisableRawMouseInput() noexcept
	{
		Application::GetInstance()->window->DisableRawMouseInput();
		mouse->DisableRawInput();

		CoreLogger::Info("Raw mouse input disabled");
	}

	Void Input::EnableCursor() noexcept
	{
		Application::GetInstance()->window->EnableCursor();
		mouse->EnableCursor();

		CoreLogger::Info("Cursor enabled");
	}

	Void Input::DisableCursor() noexcept
	{
		Application::GetInstance()->window->DisableCursor();
		mouse->DisableCursor();

		CoreLogger::Info("Cursor disabled");
	}
}