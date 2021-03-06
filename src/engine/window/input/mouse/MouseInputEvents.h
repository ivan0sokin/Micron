#ifndef _MICRON_WINDOW_INPUT_MOUSE_MOUSE_INPUT_EVENTS_H
#define _MICRON_WINDOW_INPUT_MOUSE_MOUSE_INPUT_EVENTS_H

#include "ButtonMappings.h"

namespace Micron
{
	enum class MouseInputEventType : UInt16
	{
		None = 0,
		ButtonAction,
		WheelScroll,
		Move,
		RawMove,
		Enter,
		Leave
	};

	MultibyteString ToString(MouseInputEventType const &mouseInputEventType) noexcept;

	class MouseInputEvent : public Event
	{
	public:
		inline MouseInputEvent() noexcept = default;
		virtual inline ~MouseInputEvent() noexcept = default;

		constexpr EventCategory GetCategory() const noexcept override { return EventCategory::MouseInput; }
		virtual constexpr MouseInputEventType GetType() const noexcept { return MouseInputEventType::None; }
	};

	using MouseInputEventRc = Rc<MouseInputEvent>;

	enum class ButtonActionEventType : UInt16
	{
		None = 0,
		Release,
		Press
	};

	MultibyteString ToString(ButtonActionEventType const &buttonActionEventType) noexcept;

	class ButtonActionEvent : public MouseInputEvent
	{
	public:
		inline ButtonActionEvent() noexcept = default;
		virtual inline ~ButtonActionEvent() noexcept = default;

		constexpr ButtonActionEvent(Button const &button, Position const &position) noexcept :
			button{ button }, position{ position }
		{}

		constexpr Button GetButton() const noexcept { return button; }
		constexpr Position const & GetPosition() const noexcept { return position; }
		constexpr Int64 GetPositionX() const noexcept { return position.x; }
		constexpr Int64 GetPositionY() const noexcept { return position.y; }

		constexpr MouseInputEventType GetType() const noexcept override { return MouseInputEventType::ButtonAction; }
		virtual constexpr ButtonActionEventType GetActionType() const noexcept { return ButtonActionEventType::None; }
	private:
		Button button;
		Position position;
	};

	using ButtonActionEventRc = Rc<ButtonActionEvent>;

	class ButtonReleaseEvent : public ButtonActionEvent
	{
	public:
		inline ButtonReleaseEvent() noexcept = default;
		virtual inline ~ButtonReleaseEvent() noexcept = default;

		constexpr ButtonReleaseEvent(Button const &button, Position const &position) noexcept :
			ButtonActionEvent(button, position)
		{}

		constexpr ButtonActionEventType GetActionType() const noexcept override { return ButtonActionEventType::Release; }
	};

	class ButtonPressEvent : public ButtonActionEvent
	{
	public:
		inline ButtonPressEvent() noexcept = default;
		virtual inline ~ButtonPressEvent() noexcept = default;

		constexpr ButtonPressEvent(Button const &button, Position const &position) noexcept :
			ButtonActionEvent(button, position)
		{}

		constexpr ButtonActionEventType GetActionType() const noexcept override { return ButtonActionEventType::Press; }
	};

	MultibyteString ToString(ButtonActionEventType const& buttonActionEventType) noexcept;

	class WheelScrollEvent : public MouseInputEvent
	{
	public:
		inline WheelScrollEvent() noexcept = default;
		virtual inline ~WheelScrollEvent() noexcept = default;

		constexpr WheelScrollEvent(Int32 offset, Position const &position) noexcept :
			offset{ offset }, position{ position }
		{}

		Int32 GetOffset() const noexcept { return offset; }
		constexpr Position const & GetPosition() const noexcept { return position; }
		constexpr Int64 GetPositionX() const noexcept { return position.x; }
		constexpr Int64 GetPositionY() const noexcept { return position.y; }

		constexpr MouseInputEventType GetType() const noexcept override { return MouseInputEventType::WheelScroll; }
	private:
		Int32 offset;
		Position position;
	};

	using WheelScrollEventRc = Rc<WheelScrollEvent>;

	class MouseMoveEvent : public MouseInputEvent
	{
	public:
		inline MouseMoveEvent() noexcept = default;
		virtual inline ~MouseMoveEvent() noexcept = default;

		constexpr MouseMoveEvent(Position const &position) noexcept :
			position{ position }
		{}

		constexpr Position const & GetPosition() const noexcept { return position; }
		constexpr Int64 GetPositionX() const noexcept { return position.x; }
		constexpr Int64 GetPositionY() const noexcept { return position.y; }

		constexpr MouseInputEventType GetType() const noexcept { return MouseInputEventType::Move; }
	private:
		Position position;
	};

	using MouseMoveEventRc = Rc<MouseMoveEvent>;

	struct RawDelta
	{
		Int32 dx, dy;
	};

	class MouseRawMoveEvent : public MouseInputEvent
	{
	public:
		inline MouseRawMoveEvent() noexcept = default;
		virtual inline ~MouseRawMoveEvent() noexcept = default;

		constexpr MouseRawMoveEvent(RawDelta const &rawDelta) noexcept :
			rawDelta{ rawDelta }
		{}

		constexpr RawDelta const & GetRawDelta() const noexcept { return rawDelta; }
		inline Int64 GetRawDeltaX() const noexcept { return rawDelta.dx; }
		inline Int64 GetRawDeltaY() const noexcept { return rawDelta.dy; }

		constexpr MouseInputEventType GetType() const noexcept { return MouseInputEventType::RawMove; }
	private:
		RawDelta rawDelta;
	};

	using MouseRawMoveEventRc = Rc<MouseRawMoveEvent>;

	class MouseEnterEvent : public MouseInputEvent
	{
	public:
		inline MouseEnterEvent() noexcept = default;
		virtual inline ~MouseEnterEvent() noexcept = default;

		constexpr MouseInputEventType GetType() const noexcept { return MouseInputEventType::Enter; }
	};

	class MouseLeaveEvent : public MouseInputEvent
	{
	public:
		inline MouseLeaveEvent() noexcept = default;
		virtual inline ~MouseLeaveEvent() noexcept = default;

		constexpr MouseInputEventType GetType() const noexcept { return MouseInputEventType::Leave; }
	};
}

#endif