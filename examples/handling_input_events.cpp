#include <Micron/Micron.h>

class TestApplication : public Micron::Application
{
public:
	TestApplication() noexcept
	{
		ApplicationLogger = Micron::MakeRc<Micron::Logger>("TestApplication");

		this->InitializeApplicationDescription(Micron::ApplicationDescription
		{
			"Test application name",
			"Some window title",
			Micron::Resolution { 600, 700 }
		});

        ApplicationLogger->Debug("Constructor");
	}


	~TestApplication() noexcept override
	{
        ApplicationLogger->Debug("Destructor");
	}
private:
	virtual void OnInitialize() noexcept override
	{
		ApplicationLogger->Debug("OnInitialize()");
	}

	virtual void OnUserUpdate() noexcept override
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

	void HandleKeyboardInput(Micron::KeyboardInputEventRc keyboardInputEvent) noexcept
	{
		using namespace Micron;

		ApplicationLogger->Trace("\"{0}\", keycode: {1}, scancode: {2}, action: {3}", ToString(keyboardInputEvent->GetKey().keycode), keyboardInputEvent->GetKey().keycode, keyboardInputEvent->GetKey().scancode, ToString(keyboardInputEvent->GetType()));
		
		if (keyboardInputEvent->GetType() != KeyActionEventType::Press)
			return;

		switch (keyboardInputEvent->GetKey().keycode)
		{
		case Keycode::F1:
			Input::EnableCursor();
			ApplicationLogger->Info("Cursor enabled! IsCursorEnabled state is {}", ToString(Input::IsCursorEnabled()));
			break;
		case Keycode::F2:
			Input::DisableCursor();
			ApplicationLogger->Info("Cursor disabled! IsCursorEnabled state is {}", ToString(Input::IsCursorEnabled()));
			break;
		case Keycode::F3:
			Input::EnableRawMouseInput();
			ApplicationLogger->Info("Raw mouse input enabled! IsRawMouseInputEnabled state is {}", ToString(Input::IsRawMouseInputEnabled()));
			break;
		case Keycode::F4:
			Input::DisableRawMouseInput();
			ApplicationLogger->Info("Raw mouse input disabled! IsRawMouseInputEnabled state is {}", ToString(Input::IsRawMouseInputEnabled()));
			break;
		case Keycode::F5:
			Input::EnableAutorepeat();
			ApplicationLogger->Info("Autorepeat enabled! IsAutorepeatEnabled is {}", ToString(Input::IsAutorepeatEnabled()));
			break;
		case Keycode::F6:
			Input::DisableAutorepeat();
			ApplicationLogger->Info("Autorepeat disabled! IsAutorepeatEnabled is {}", ToString(Input::IsAutorepeatEnabled()));
			break;
		case Keycode::F7:
			ApplicationLogger->Info("Input::eventBuffer size is: {0}, is empty state: {1}", Input::EventBufferSize(), ToString(Input::IsEventBufferEmpty()));
			break;
		case Keycode::F8:
			Input::FlushEventBuffer();
			ApplicationLogger->Info("Event buffer flushed!");
			break;
		case Keycode::F9:
			ApplicationLogger->Info("Last mouse position: ({0}, {1})", Input::GetLastMouseX(), Input::GetLastMouseY());
			break;
		case Keycode::F10:
			ApplicationLogger->Info("Last mouse offset: {}", Input::GetLastMouseWheelOffset());
			break;
		case Keycode::Escape:
			this->ShutDown();
			break;
		default:
			break;
		}
	}

	void HandleMouseInput(Micron::MouseInputEventRc mouseInputEvent) noexcept
	{
		using namespace Micron;

		switch (mouseInputEvent->GetType())
		{
		case MouseInputEventType::ButtonAction:
		{
			ButtonActionEventRc btnActionEvent = DynamicPointerCast<ButtonActionEvent>(mouseInputEvent);
			ApplicationLogger->Info("{0} button, action: {1}, at: ({2}, {3})", ToString(btnActionEvent->GetButton()), ToString(btnActionEvent->GetActionType()), btnActionEvent->GetPositionX(), btnActionEvent->GetPositionY());
			break;
		}
		case MouseInputEventType::WheelScroll:
		{
			WheelScrollEventRc wheelScrollEvent = DynamicPointerCast<WheelScrollEvent>(mouseInputEvent);
			ApplicationLogger->Info("Offset: {0}, at: ({1}, {2})", wheelScrollEvent->GetOffset(), wheelScrollEvent->GetPositionX(), wheelScrollEvent->GetPositionY());
			break;
		}
		case MouseInputEventType::Move:
		{
			MouseMoveEventRc mouseMoveEvent = DynamicPointerCast<MouseMoveEvent>(mouseInputEvent);
			ApplicationLogger->Trace("Mouse has moved to: ({0}, {1})", mouseMoveEvent->GetPositionX(), mouseMoveEvent->GetPositionY());
			break;
		}
		case MouseInputEventType::RawMove:
		{
			MouseRawMoveEventRc mouseRawMoveEvent = DynamicPointerCast<MouseRawMoveEvent>(mouseInputEvent);
			ApplicationLogger->Trace("Mouse has moved by: ({0}, {1})", mouseRawMoveEvent->GetRawDeltaX(), mouseRawMoveEvent->GetRawDeltaY());
			break;
		}
		case MouseInputEventType::Enter:
		{
			ApplicationLogger->Info("Mouse entered! Last mouse position: ({0}, {1})", Input::GetLastMouseX(), Input::GetLastMouseY());
			break;
		}
		case MouseInputEventType::Leave:
		{
			ApplicationLogger->Info("Mouse leaved! Last mouse position: ({0}, {1})", Input::GetLastMouseX(), Input::GetLastMouseY());
			break;
		}
		default:
			break;
		}
	}

	virtual void OnDestroy() noexcept override
	{
		ApplicationLogger->Debug("OnDestroy()");
	}
private:
	Micron::Rc<Micron::Logger> ApplicationLogger;
};

static Micron::Rc<Micron::Application> applicationInstance = Micron::MakeRc<TestApplication>();

Micron::Rc<Micron::Application> Micron::Application::GetInstance() noexcept
{
	return applicationInstance;
}