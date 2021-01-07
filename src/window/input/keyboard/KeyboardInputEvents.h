#ifndef _MICRON_INPUT_KEYBOARD_KEYBOARD_INPUT_EVENTS_H
#define _MICRON_INPUT_KEYBOARD_KEYBOARD_INPUT_EVENTS_H

#include "KeyMappings.h"

namespace Micron
{
	enum class KeyActionEventType : UInt16
	{
		None = 0,
		Release,
		Press
	};

	String ToString(KeyActionEventType const &keyActionEventType) noexcept;

	struct Key
	{
		Keycode keycode;
		UInt32 scancode;
	};

	class KeyboardInputEvent : public Event
	{
	public:
		inline KeyboardInputEvent() noexcept = default;
		virtual inline ~KeyboardInputEvent() noexcept = default;

		constexpr KeyboardInputEvent(Key const &key) noexcept :
			key{ key }
		{}

		constexpr EventCategory GetCategory() const noexcept override { return EventCategory::KeyboardInput; }
		virtual constexpr KeyActionEventType GetType() const noexcept { return KeyActionEventType::None; }

		constexpr Key const & GetKey() const noexcept { return key; }
	private:
		Key key;
	};

	using KeyboardInputEventRc = Rc<KeyboardInputEvent>;

	class KeyReleaseEvent : public KeyboardInputEvent
	{
	public:
		inline KeyReleaseEvent() noexcept = default;
		virtual inline ~KeyReleaseEvent() noexcept = default;

		constexpr KeyReleaseEvent(Key const &key) noexcept :
			KeyboardInputEvent(key)
		{}

		constexpr KeyActionEventType GetType() const noexcept override { return KeyActionEventType::Release; }
	};

	class KeyPressEvent : public KeyboardInputEvent
	{
	public:
		inline KeyPressEvent() noexcept = default;
		virtual inline ~KeyPressEvent() noexcept = default;

		constexpr KeyPressEvent(Key const &key) noexcept :
			KeyboardInputEvent(key)
		{}

		constexpr KeyActionEventType GetType() const noexcept override { return KeyActionEventType::Press; }
	};
}

#endif