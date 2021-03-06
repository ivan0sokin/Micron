#include <Micron/Micron.h>

/*
	If you define _MICRON_DEBUG,
	core logger will always send you all incoming events.
	So you do not need "printing" events if you are debugging.
	Also you have to call a function SetPreferences to initialize working window.
*/

using namespace Micron;

class ExampleApplication : public Application
{
public:
	ExampleApplication() noexcept
	{
		this->name = "ExampleApplication";

		applicationLogger = MakeRc<Logger>("ExampleApplication");
		applicationLogger->Debug("Beginning");
	}

	~ExampleApplication() noexcept override
	{
		applicationLogger->Debug("Ending");
	}
private:
	virtual void OnInitialize() noexcept override
	{
		applicationLogger->Debug("Initializing");

		this->GetWindow()->SetPreferences(WindowPreferences()
			.Title("Example title")
			.Resolution({ 1280, 720 })
			.PositionType(PositionType::Centered)
		);
	}
	
	virtual void OnUserUpdate(Real32 deltaTime) noexcept override
	{
		using namespace Micron;

		EventRc event;
		while (!Input::IsEventBufferEmpty())
		{
			event = Input::PeekEvent().value();

			switch (event->GetCategory())
			{
			case EventCategory::KeyboardInput:
				this->HandleKeyboardInput(DynamicPointerCast<KeyboardInputEvent>(event));
				break;
			case EventCategory::MouseInput:
				this->HandleMouseInput(DynamicPointerCast<MouseInputEvent>(event));
				break;
			default:
				break;
			}
		}
	}

	void HandleKeyboardInput(KeyboardInputEventRc keyboardInputEvent) noexcept
	{
		using namespace Micron;

		applicationLogger->Trace("\"{0}\", keycode: {1}, scancode: {2}, action: {3}", ToString(keyboardInputEvent->GetKey().keycode), keyboardInputEvent->GetKey().keycode, keyboardInputEvent->GetKey().scancode, ToString(keyboardInputEvent->GetType()));

		if (keyboardInputEvent->GetType() != KeyActionEventType::Press)
			return;

		switch (keyboardInputEvent->GetKey().keycode)
		{
		case Keycode::F1:
			Input::EnableCursor();
			applicationLogger->Info("Cursor enabled! IsCursorEnabled state is {}", ToString(Input::IsCursorEnabled()));
			break;
		case Keycode::F2:
			Input::DisableCursor();
			applicationLogger->Info("Cursor disabled! IsCursorEnabled state is {}", ToString(Input::IsCursorEnabled()));
			break;
		case Keycode::F3:
			Input::EnableRawMouseInput();
			applicationLogger->Info("Raw mouse input enabled! IsRawMouseInputEnabled state is {}", ToString(Input::IsRawMouseInputEnabled()));
			break;
		case Keycode::F4:
			Input::DisableRawMouseInput();
			applicationLogger->Info("Raw mouse input disabled! IsRawMouseInputEnabled state is {}", ToString(Input::IsRawMouseInputEnabled()));
			break;
		case Keycode::F5:
			Input::EnableAutorepeat();
			applicationLogger->Info("Autorepeat enabled! IsAutorepeatEnabled is {}", ToString(Input::IsAutorepeatEnabled()));
			break;
		case Keycode::F6:
			Input::DisableAutorepeat();
			applicationLogger->Info("Autorepeat disabled! IsAutorepeatEnabled is {}", ToString(Input::IsAutorepeatEnabled()));
			break;
		case Keycode::F7:
			applicationLogger->Info("Input::eventBuffer size is: {0}, is empty state: {1}", Input::EventBufferSize(), ToString(Input::IsEventBufferEmpty()));
			break;
		case Keycode::F8:
			Input::FlushEventBuffer();
			applicationLogger->Info("Event buffer flushed!");
			break;
		case Keycode::F9:
			applicationLogger->Info("Last mouse position: ({0}, {1})", Input::GetLastMouseX(), Input::GetLastMouseY());
			break;
		case Keycode::F10:
			applicationLogger->Info("Last mouse offset: {}", Input::GetLastMouseWheelOffset());
			break;
		case Keycode::Escape:
			this->Shutdown();
			break;
		default:
			break;
		}
	}

	void HandleMouseInput(MouseInputEventRc mouseInputEvent) noexcept
	{
		using namespace Micron;

		switch (mouseInputEvent->GetType())
		{
		case MouseInputEventType::ButtonAction:
		{
			ButtonActionEventRc btnActionEvent = DynamicPointerCast<ButtonActionEvent>(mouseInputEvent);
			applicationLogger->Info("{0} button, action: {1}, at: ({2}, {3})", ToString(btnActionEvent->GetButton()), ToString(btnActionEvent->GetActionType()), btnActionEvent->GetPositionX(), btnActionEvent->GetPositionY());
			break;
		}
		case MouseInputEventType::WheelScroll:
		{
			WheelScrollEventRc wheelScrollEvent = DynamicPointerCast<WheelScrollEvent>(mouseInputEvent);
			applicationLogger->Info("Offset: {0}, at: ({1}, {2})", wheelScrollEvent->GetOffset(), wheelScrollEvent->GetPositionX(), wheelScrollEvent->GetPositionY());
			break;
		}
		case MouseInputEventType::Move:
		{
			MouseMoveEventRc mouseMoveEvent = DynamicPointerCast<MouseMoveEvent>(mouseInputEvent);
			applicationLogger->Trace("Mouse has moved to: ({0}, {1})", mouseMoveEvent->GetPositionX(), mouseMoveEvent->GetPositionY());
			break;
		}
		case MouseInputEventType::RawMove:
		{
			MouseRawMoveEventRc mouseRawMoveEvent = DynamicPointerCast<MouseRawMoveEvent>(mouseInputEvent);
			applicationLogger->Trace("Mouse has moved by: ({0}, {1})", mouseRawMoveEvent->GetRawDeltaX(), mouseRawMoveEvent->GetRawDeltaY());
			break;
		}
		case MouseInputEventType::Enter:
		{
			applicationLogger->Info("Mouse entered! Last mouse position: ({0}, {1})", Input::GetLastMouseX(), Input::GetLastMouseY());
			break;
		}
		case MouseInputEventType::Leave:
		{
			applicationLogger->Info("Mouse leaved! Last mouse position: ({0}, {1})", Input::GetLastMouseX(), Input::GetLastMouseY());
			break;
		}
		default:
			break;
		}
	}

	virtual void OnDestroy() noexcept override
	{
		applicationLogger->Debug("Destroying objects");
	}
private:
	Rc<Logger> applicationLogger;
};

static Rc<Application> applicationInstance = MakeRc<ExampleApplication>();

Rc<Application> Application::GetInstance() noexcept
{
	return applicationInstance;
}