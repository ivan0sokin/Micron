#include "Keyboard.h"

namespace Micron
{
	static Array<MultibyteString, 512> keycodesAsStrings;
	MultibyteString ToString(Keycode const &keycode) noexcept { return keycodesAsStrings[EnumToUnsignedSizeType(keycode)]; }

	static Void FillKeycodesAsStringsArray() noexcept
	{
		for (auto &conversion : keycodesAsStrings)
		{
			conversion = "Unknown";
		}
		
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Spacebar)] = "Spacebar";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Apostrophe)] = "'";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Plus)] = "+";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Comma)] = ",";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Minus)] = "-";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Period)] = ".";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Slash)] = "/";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Semicolon)] = ";";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Equal)] = "=";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::LeftBracket)] = "[";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Backslash)] = "\\";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::RightBracket)] = "]";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::GraveAccent)] = "`";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Zero)] = "0";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::One)] = "1";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Two)] = "2";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Three)] = "3";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Four)] = "4";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Five)] = "5";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Six)] = "6";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Seven)] = "7";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Eight)] = "8";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Nine)] = "9";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::A)] = "A";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::B)] = "B";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::C)] = "C";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::D)] = "D";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::E)] = "E";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F)] = "F";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::G)] = "G";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::H)] = "H";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::I)] = "I";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::J)] = "J";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::K)] = "K";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::L)] = "L";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::M)] = "M";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::N)] = "N";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::O)] = "O";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::P)] = "P";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Q)] = "Q";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::R)] = "R";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::S)] = "S";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::T)] = "T";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::U)] = "U";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::V)] = "V";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::W)] = "W";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::X)] = "X";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Y)] = "Y";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Z)] = "Z";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadZero)] = "NumPad 0";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadOne)] = "NumPad 1";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadTwo)] = "NumPad 2";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadThree)] = "NumPad 3";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadFour)] = "NumPad 4";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadFive)] = "NumPad 5";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadSix)] = "NumPad 6";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadSeven)] = "NumPad 7";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadEight)] = "NumPad 8";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadNine)] = "NumPad 9";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadAdd)] = "NumPad +";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadSubtract)] = "NumPad -";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadMultiply)] = "NumPad *";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadDivide)] = "NumPad /";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadDecimal)] = "NumPad .";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadEqual)] = "NumPad =";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumPadEnter)] = "NumPad Enter";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::NumLock)] = "NumLock";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::ScrollLock)] = "ScrollLock";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::CapsLock)] = "CapsLock";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Clear)] = "Clear";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Escape)] = "Escape";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Backspace)] = "Backspace";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Tab)] = "Tab";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Enter)] = "Enter";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Select)] = "Select";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Print)] = "Print";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Execute)] = "Execute";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::PrintScreen)] = "Print Screen";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::PauseBreak)] = "Pause/Break";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Help)] = "Help";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::PageUp)] = "PageUp";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::PageDown)] = "PageDown";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::End)] = "End";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Home)] = "Home";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::LeftArrow)] = "Left Arrow";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::UpArrow)] = "Up Arrow";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::RightArrow)] = "Right Arrow";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::DownArrow)] = "Down Arrow";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Insert)] = "Insert";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Delete)] = "Delete";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Shift)] = "Shift";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Ctrl)] = "Ctrl";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Alt)] = "Alt";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::LeftShift)] = "Left Shift";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::RightShift)] = "Right Shift";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::LeftCtrl)] = "Left Ctrl";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::RightCtrl)] = "Right Ctrl";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::LeftAlt)] = "Left Alt";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::RightAlt)] = "Right Alt";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F1)] = "F1";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F2)] = "F2";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F3)] = "F3";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F4)] = "F4";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F5)] = "F5";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F6)] = "F6";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F7)] = "F7";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F8)] = "F8";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F9)] = "F9";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F10)] = "F10";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F11)] = "F11";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F12)] = "F12";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F13)] = "F13";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F14)] = "F14";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F15)] = "F15";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F16)] = "F16";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F17)] = "F17";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F18)] = "F18";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F19)] = "F19";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F20)] = "F20";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F21)] = "F21";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F22)] = "F22";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F23)] = "F23";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::F24)] = "F24";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::VolumeMute)] = "Volume Mute";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::VolumeUp)] = "Volume Up";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::VolumeDown)] = "Volume Down";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::LeftWindows)] = "Left Windows";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::RightWindows)] = "Right Windows";
		keycodesAsStrings[EnumToUnsignedSizeType(Keycode::Applications)] = "Applications";
	}

	Keyboard::Keyboard() noexcept
	{
		FillKeycodesAsStringsArray();
	}

	Void Keyboard::OnKeyPress(Keycode const &keycode) noexcept
	{
		keyStates[EnumToUnsignedSizeType(keycode)] = true;
	}

	Void Keyboard::OnKeyRelease(Keycode const &keycode) noexcept
	{
		keyStates[EnumToUnsignedSizeType(keycode)] = false;
	}

	Void Keyboard::ClearStates() noexcept
	{
		keyStates.reset();
	}
}