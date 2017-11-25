/* RUN Kit C++ API - Keyboard.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Keyboard_HPP__
#define __RUN_Keyboard_HPP__

#include <RUN/namespace.hpp>
#include <Z/formats/keymap/Z.h>

struct RUN_API RUN::Keyboard {

	struct RUN_API Key {
		enum {	Up			   = Z_KEY_CODE_UP,
			Right			   = Z_KEY_CODE_RIGHT,
			Down			   = Z_KEY_CODE_DOWN,
			Left			   = Z_KEY_CODE_LEFT,
			Home			   = Z_KEY_CODE_HOME,
			End			   = Z_KEY_CODE_END,
			PageUp			   = Z_KEY_CODE_PAGE_UP,
			PageDown		   = Z_KEY_CODE_PAGE_DOWN,
			Backspace		   = Z_KEY_CODE_BACKSPACE,
			Tab			   = Z_KEY_CODE_TAB,
			Return			   = Z_KEY_CODE_RETURN,
			F1			   = Z_KEY_CODE_F1,
			F2			   = Z_KEY_CODE_F2,
			F3			   = Z_KEY_CODE_F3,
			F4			   = Z_KEY_CODE_F4,
			F5			   = Z_KEY_CODE_F5,
			F6			   = Z_KEY_CODE_F6,
			F7			   = Z_KEY_CODE_F7,
			F8			   = Z_KEY_CODE_F8,
			F9			   = Z_KEY_CODE_F9,
			F10			   = Z_KEY_CODE_F10,
			F11			   = Z_KEY_CODE_F11,
			F12			   = Z_KEY_CODE_F12,
			PrintScreen		   = Z_KEY_CODE_PRINT_SCREEN,
			ScrollLock		   = Z_KEY_CODE_SCROLL_LOCK,
			Pause			   = Z_KEY_CODE_PAUSE,
			CapsLock		   = Z_KEY_CODE_CAPS_LOCK,
			Escape			   = Z_KEY_CODE_ESCAPE,
			LeftShift		   = Z_KEY_CODE_LEFT_SHIFT,
			LeftControl		   = Z_KEY_CODE_LEFT_CONTROL,
			LeftCommand		   = Z_KEY_CODE_LEFT_COMMAND,
			LeftOption		   = Z_KEY_CODE_LEFT_OPTION,
			Space			   = Z_KEY_CODE_SPACE,
			RightOption		   = Z_KEY_CODE_RIGHT_OPTION,
			RightCommand		   = Z_KEY_CODE_RIGHT_COMMAND,
			Application		   = Z_KEY_CODE_APPLICATION,
			RightControl		   = Z_KEY_CODE_RIGHT_CONTROL,
			RightShift		   = Z_KEY_CODE_RIGHT_SHIFT,
			Insert			   = Z_KEY_CODE_INSERT,
			ANSIApostrophe		   = Z_KEY_CODE_ANSI_APOSTROPHE,
			ANSIKeypadSolidus	   = Z_KEY_CODE_ANSI_KEYPAD_SOLIDUS,
			ANSIKeypadHyphenMinus	   = Z_KEY_CODE_ANSI_KEYPAD_HYPHEN_MINUS,
			ANSIKeypadAsterisk	   = Z_KEY_CODE_ANSI_KEYPAD_ASTERISK,
			ANSIKeypadPlusSign	   = Z_KEY_CODE_ANSI_KEYPAD_PLUS_SIGN,
			ANSIComma		   = Z_KEY_CODE_ANSI_COMMA,
			ANSIHyphenMinus            = Z_KEY_CODE_ANSI_HYPHEN_MINUS,
			ANSIFullStop		   = Z_KEY_CODE_ANSI_FULL_STOP,
			ANSISolidus		   = Z_KEY_CODE_ANSI_SOLIDUS,
			ANSIDigit0		   = Z_KEY_CODE_ANSI_0,
			ANSIDigit1		   = Z_KEY_CODE_ANSI_1,
			ANSIDigit2		   = Z_KEY_CODE_ANSI_2,
			ANSIDigit3		   = Z_KEY_CODE_ANSI_3,
			ANSIDigit4		   = Z_KEY_CODE_ANSI_4,
			ANSIDigit5		   = Z_KEY_CODE_ANSI_5,
			ANSIDigit6		   = Z_KEY_CODE_ANSI_6,
			ANSIDigit7		   = Z_KEY_CODE_ANSI_7,
			ANSIDigit8		   = Z_KEY_CODE_ANSI_8,
			ANSIDigit9		   = Z_KEY_CODE_ANSI_9,
			ANSIKeypadEnter		   = Z_KEY_CODE_ANSI_KEYPAD_ENTER,
			ANSISemicolon		   = Z_KEY_CODE_ANSI_SEMICOLON,
			ANSIKeypadDecimalSeparator = Z_KEY_CODE_ANSI_KEYPAD_DECIMAL_SEPARATOR,
			ANSIEqualsSign		   = Z_KEY_CODE_ANSI_EQUALS_SIGN,
			ANSIKeypadNumLock	   = Z_KEY_CODE_ANSI_KEYPAD_NUM_LOCK,
			ANSIKeypadDigit0	   = Z_KEY_CODE_ANSI_KEYPAD_0,
			ANSIKeypadDigit1	   = Z_KEY_CODE_ANSI_KEYPAD_1,
			ANSILetterA		   = Z_KEY_CODE_ANSI_A,
			ANSILetterB		   = Z_KEY_CODE_ANSI_B,
			ANSILetterC		   = Z_KEY_CODE_ANSI_C,
			ANSILetterD		   = Z_KEY_CODE_ANSI_D,
			ANSILetterE		   = Z_KEY_CODE_ANSI_E,
			ANSILetterF		   = Z_KEY_CODE_ANSI_F,
			ANSILetterG		   = Z_KEY_CODE_ANSI_G,
			ANSILetterH		   = Z_KEY_CODE_ANSI_H,
			ANSILetterI		   = Z_KEY_CODE_ANSI_I,
			ANSILetterJ		   = Z_KEY_CODE_ANSI_J,
			ANSILetterK		   = Z_KEY_CODE_ANSI_K,
			ANSILetterL		   = Z_KEY_CODE_ANSI_L,
			ANSILetterM		   = Z_KEY_CODE_ANSI_M,
			ANSILetterN		   = Z_KEY_CODE_ANSI_N,
			ANSILetterO		   = Z_KEY_CODE_ANSI_O,
			ANSILetterP		   = Z_KEY_CODE_ANSI_P,
			ANSILetterQ		   = Z_KEY_CODE_ANSI_Q,
			ANSILetterR		   = Z_KEY_CODE_ANSI_R,
			ANSILetterS		   = Z_KEY_CODE_ANSI_S,
			ANSILetterT		   = Z_KEY_CODE_ANSI_T,
			ANSILetterU		   = Z_KEY_CODE_ANSI_U,
			ANSILetterV		   = Z_KEY_CODE_ANSI_V,
			ANSILetterW		   = Z_KEY_CODE_ANSI_W,
			ANSILetterX		   = Z_KEY_CODE_ANSI_X,
			ANSILetterY		   = Z_KEY_CODE_ANSI_Y,
			ANSILetterZ		   = Z_KEY_CODE_ANSI_Z,
			ANSILeftSquareBracket	   = Z_KEY_CODE_ANSI_LEFT_SQUARE_BRACKET,
			ANSIReverseSolidus	   = Z_KEY_CODE_ANSI_REVERSE_SOLIDUS,
			ANSIRightSquareBracket	   = Z_KEY_CODE_ANSI_RIGHT_SQUARE_BRACKET,
			ANSIKeypadDigit2	   = Z_KEY_CODE_ANSI_KEYPAD_2,
			ANSIKeypadDigit3	   = Z_KEY_CODE_ANSI_KEYPAD_3,
			ANSIGraveAccent		   = Z_KEY_CODE_ANSI_GRAVE_ACCENT, // Like ASCII
			ANSIKeypadDigit4	   = Z_KEY_CODE_ANSI_KEYPAD_4,
			ANSIKeypadDigit5	   = Z_KEY_CODE_ANSI_KEYPAD_5,
			ANSIKeypadDigit6	   = Z_KEY_CODE_ANSI_KEYPAD_6,
			ANSIKeypadDigit7	   = Z_KEY_CODE_ANSI_KEYPAD_7,
			ANSIKeypadDigit8	   = Z_KEY_CODE_ANSI_KEYPAD_8,
			ANSIKeypadDigit9	   = Z_KEY_CODE_ANSI_KEYPAD_9,
			AppleANSIKeypadEqualsSign  = Z_KEY_CODE_APPLE_ANSI_KEYPAD_EQUALS_SIGN,
			F13			   = Z_KEY_CODE_F13,
			F14			   = Z_KEY_CODE_F14,
			F15			   = Z_KEY_CODE_F15,
			F16			   = Z_KEY_CODE_F16,
			F17			   = Z_KEY_CODE_F17,
			F18			   = Z_KEY_CODE_F18,
			F19			   = Z_KEY_CODE_F19,
			F20			   = Z_KEY_CODE_F20,
			F21			   = Z_KEY_CODE_F21,
			F22			   = Z_KEY_CODE_F22,
			F23			   = Z_KEY_CODE_F23,
			F24			   = Z_KEY_CODE_F24,
			JISEisu			   = Z_KEY_CODE_JIS_EISU,
			JISKana			   = Z_KEY_CODE_JIS_KANA,
			JISLowLine		   = Z_KEY_CODE_JIS_LOW_LINE,
			JISYenSign		   = Z_KEY_CODE_JIS_YEN_SIGN,
			JISKeypadComma		   = Z_KEY_CODE_JIS_KEYPAD_COMMA,
			ISOSection		   = Z_KEY_CODE_ISO_SECTION,
			VolumeUp		   = Z_KEY_CODE_VOLUME_UP,
			VolumeDown		   = Z_KEY_CODE_VOLUME_DOWN,
			Mute			   = Z_KEY_CODE_MUTE,
			Unused0			   = Z_KEY_CODE_UNUSED_0,
			Function		   = Z_KEY_CODE_FUNCTION,
			Delete			   = Z_KEY_CODE_DELETE
		};

		enum {Invalid = Z_KEY_CODE_INVALID};

		UInt8 scancode;

		Z_INLINE_MEMBER Key(UInt8 scancode) : scancode(scancode) {}
		Z_INLINE_MEMBER operator UInt8() const {return scancode;}

		Z_INLINE_MEMBER Boolean is_valid() const
			{return scancode != Invalid;}

		const Character *name() const;

	};

	UInt8 state[16];

	Keyboard() : state() {}


	Z_INLINE_MEMBER operator bool() const
		{
#		ifdef Z_UINT128
			return bool(*(UInt128 *)state);
#		else
			return bool(((UInt64 *)state)[0]) || bool(((UInt64 *)state)[1]);
#		endif
		}


	Z_INLINE_MEMBER bool operator[](Key key) const
		{return state[key / 8] & ~(1 << (key % 8));}



	Z_INLINE_MEMBER Keyboard &operator +=(Key key)
		{
		state[key / 8] |= 1 << (key % 8);
		return *this;
		}


	Z_INLINE_MEMBER Keyboard &operator -=(Key key)
		{
		state[key / 8] &= ~(1 << (key % 8));
		return *this;
		}
};

#endif // __RUN_Keyboard_HPP__
