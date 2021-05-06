#include "Mouse.h"

namespace Micron
{
    static Array<MultibyteString, MAX_MOUSE_BUTTONS> buttonsAsStrings;
    MultibyteString ToString(Button const &button) noexcept { return buttonsAsStrings[EnumToUnsignedSizeType(button)]; }

    static Void FillButtonsAsStringsArray()
    {
        buttonsAsStrings[EnumToUnsignedSizeType(Button::Left)] = "Left";
        buttonsAsStrings[EnumToUnsignedSizeType(Button::Right)] = "Right";
        buttonsAsStrings[EnumToUnsignedSizeType(Button::Middle)] = "Middle";
        buttonsAsStrings[EnumToUnsignedSizeType(Button::Backward)] = "Backward";
        buttonsAsStrings[EnumToUnsignedSizeType(Button::Forward)] = "Forward";
        
        for (USize i = 5; i < MAX_MOUSE_BUTTONS; ++i)
        {
            buttonsAsStrings[i] = ToString(i) + MultibyteString("-th");
        }

        for (USize i = 20; i < 60; i += 10)
        {
            buttonsAsStrings[i] = ToString(i) + MultibyteString("-st");
            buttonsAsStrings[i + 1] = ToString(i + 1) + MultibyteString("-nd");
            buttonsAsStrings[i + 2] = ToString(i + 2) + MultibyteString("-rd");
        }
    }

    Mouse::Mouse() noexcept
    {
        FillButtonsAsStringsArray();
    }

    Void Mouse::OnWheelMove(Int32 deltaOffset, Int32 x, Int32 y) noexcept
    {
        lastOffset += deltaOffset;

        lastPosition.x = x;
        lastPosition.y = y;
    }

    Void Mouse::OnMouseMove(Int32 x, Int32 y) noexcept
    {
        lastPosition.x = x;
        lastPosition.y = y;
    }

    Void Mouse::OnRawMouseMove(Int32 dx, Int32 dy) noexcept
    {
        lastRawMove.dx = dx;
        lastRawMove.dy = dy;
    }

    Void Mouse::OnLeftReleased(Int32 x, Int32 y) noexcept
    {
        lastButtonStates.isLeftPressed = false;

        lastPosition.x = x;
        lastPosition.y = y;
    }

    Void Mouse::OnLeftPressed(Int32 x, Int32 y) noexcept
    {
        lastButtonStates.isLeftPressed = true;

        lastPosition.x = x;
        lastPosition.y = y;
    }

    Void Mouse::OnMiddleReleased(Int32 x, Int32 y) noexcept
    {
        lastButtonStates.isMiddlePressed = false;

        lastPosition.x = x;
        lastPosition.y = y;
    }

    Void Mouse::OnMiddlePressed(Int32 x, Int32 y) noexcept
    {
        lastButtonStates.isMiddlePressed = true;

        lastPosition.x = x;
        lastPosition.y = y;
    }

    Void Mouse::OnRightReleased(Int32 x, Int32 y) noexcept
    {
        lastButtonStates.isRightPressed = false;

        lastPosition.x = x;
        lastPosition.y = y;
    }

    Void Mouse::OnRightPressed(Int32 x, Int32 y) noexcept
    {
        lastButtonStates.isRightPressed = true;

        lastPosition.x = x;
        lastPosition.y = y;
    }

    Void Mouse::OnMouseEnter() noexcept
    {
        isInWindow = true;
    }

    Void Mouse::OnMouseLeave() noexcept
    {
        isInWindow = false;
    }
}