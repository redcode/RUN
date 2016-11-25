/* RUN Kit C++ API - Keyboard.hpp
  ______ __ ______  ___
 /   - //  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Keyboard_HPP__
#define __RUN_Keyboard_HPP__

#include <RUN/namespace.hpp>

struct RUN_API RUN::Keyboard {

	struct RUN_API Key {

		enum {	UP				=   0,
			RIGHT				=   1,
			DOWN				=   2,
			LEFT				=   3,
			HOME				=   4,
			END				=   5,
			PAGE_UP				=   6,
			PAGE_DOWN			=   7,
			BACKSPACE			=   8, // Like ASCII
			TAB				=   9, // Like ASCII
			RETURN				=  10, // Like ASCII
			F1				=  11,
			F2				=  12,
			F3				=  13,
			F4				=  14,
			F5				=  15,
			F6				=  16,
			F7				=  17,
			F8				=  18,
			F9				=  19,
			F10				=  20,
			F11				=  21,
			F12				=  22,
			PRINT_SCREEN			=  23,
			SCROLL_LOCK			=  24,
			PAUSE				=  25,
			CAPS_LOCK			=  26,
			ESCAPE				=  27, // Like ASCII
			LEFT_SHIFT			=  28,
			LEFT_CONTROL			=  29,
			LEFT_COMMAND			=  30,
			LEFT_OPTION			=  31,
			SPACE				=  32, // Like ASCII
			RIGHT_OPTION			=  33,
			RIGHT_COMMAND			=  34,
			APPLICATION			=  35,
			RIGHT_CONTROL			=  36,
			RIGHT_SHIFT			=  37,
			INSERT				=  38,
			ANSI_APOSTROPHE			=  39, // Like ASCII
			ANSI_KEYPAD_SOLIDUS		=  40,
			ANSI_KEYPAD_HYPHEN_MINUS	=  41,
			ANSI_KEYPAD_ASTERISK		=  42, // Like ASCII
			ANSI_KEYPAD_PLUS_SIGN		=  43, // Like ASCII
			ANSI_COMMA			=  44, // Like ASCII
			ANSI_HYPHEN_MINUS		=  45, // Like ASCII
			ANSI_FULL_STOP			=  46, // Like ASCII
			ANSI_SOLIDUS			=  47, // Like ASCII
			ANSI_0				=  48, // Like ASCII
			ANSI_1				=  49, // Like ASCII
			ANSI_2				=  50, // Like ASCII
			ANSI_3				=  51, // Like ASCII
			ANSI_4				=  52, // Like ASCII
			ANSI_5				=  53, // Like ASCII
			ANSI_6				=  54, // Like ASCII
			ANSI_7				=  55, // Like ASCII
			ANSI_8				=  56, // Like ASCII
			ANSI_9				=  57, // Like ASCII
			ANSI_KEYPAD_ENTER		=  58,
			ANSI_SEMICOLON			=  59, // Like ASCII
			ANSI_KEYPAD_DECIMAL_SEPARATOR	=  60,
			ANSI_EQUALS_SIGN		=  61, // Like ASCII
			ANSI_KEYPAD_NUM_LOCK		=  62,
			ANSI_KEYPAD_0			=  63,
			ANSI_KEYPAD_1			=  64,
			ANSI_A				=  65, // Like ASCII
			ANSI_B				=  66, // Like ASCII
			ANSI_C				=  67, // Like ASCII
			ANSI_D				=  68, // Like ASCII
			ANSI_E				=  69, // Like ASCII
			ANSI_F				=  70, // Like ASCII
			ANSI_G				=  71, // Like ASCII
			ANSI_H				=  72, // Like ASCII
			ANSI_I				=  73, // Like ASCII
			ANSI_J				=  74, // Like ASCII
			ANSI_K				=  75, // Like ASCII
			ANSI_L				=  76, // Like ASCII
			ANSI_M				=  77, // Like ASCII
			ANSI_N				=  78, // Like ASCII
			ANSI_O				=  79, // Like ASCII
			ANSI_P				=  80, // Like ASCII
			ANSI_Q				=  81, // Like ASCII
			ANSI_R				=  82, // Like ASCII
			ANSI_S				=  83, // Like ASCII
			ANSI_T				=  84, // Like ASCII
			ANSI_U				=  85, // Like ASCII
			ANSI_V				=  86, // Like ASCII
			ANSI_W				=  87, // Like ASCII
			ANSI_X				=  88, // Like ASCII
			ANSI_Y				=  89, // Like ASCII
			ANSI_Z				=  90, // Like ASCII
			ANSI_LEFT_SQUARE_BRACKET	=  91, // Like ASCII
			ANSI_REVERSE_SOLIDUS		=  92, // Like ASCII
			ANSI_RIGHT_SQUARE_BRACKET	=  93, // Like ASCII
			ANSI_KEYPAD_2			=  94,
			ANSI_KEYPAD_3			=  95,
			ANSI_GRAVE_ACCENT		=  96, // Like ASCII
			ANSI_KEYPAD_4			=  97,
			ANSI_KEYPAD_5			=  98,
			ANSI_KEYPAD_6			=  99,
			ANSI_KEYPAD_7			= 100,
			ANSI_KEYPAD_8			= 101,
			ANSI_KEYPAD_9			= 102,
			APPLE_ANSI_KEYPAD_EQUALS_SIGN	= 103, // Apple keyboards
			UNUSED_1			= 104, // Unused
			UNUSED_2			= 105, // Unused
			UNUSED_3			= 106, // Unused
			UNUSED_4			= 107, // Unused
			UNUSED_5			= 108, // Unused
			UNUSED_6			= 109, // Unused
			UNUSED_7			= 110, // Unused
			UNUSED_8			= 111, // Unused
			UNUSED_9			= 112, // Unused
			UNUSED_10			= 113, // Unused
			UNUSED_11			= 114, // Unused
			JIS_EISU			= 115, // Japanese keyboards
			JIS_KANA			= 116, // Japanese keyboards
			JIS_LOW_LINE			= 117, // Japanese keyboards
			JIS_YEN_SIGN			= 118, // Japanese keyboards
			JIS_KEYPAD_COMMA		= 119, // Japanese keyboards
			ISO_SECTION			= 120, // ISO keyboards
			APPLE_F16			= 121, // Apple keyboards
			APPLE_F17			= 122, // Apple keyboards
			APPLE_F18			= 123, // Apple keyboards
			APPLE_F19			= 124, // Apple keyboards
			APPLE_F20			= 125, // Apple keyboards
			FUNCTION			= 126,
			DELETE				= 127  // Similar to ASCII
		};

		enum {INVALID = UNUSED_1};

		UInt8 scancode;

		Z_INLINE_MEMBER Key(UInt8 scancode) : scancode(scancode) {}
		Z_INLINE_MEMBER operator UInt8() const {return scancode;}

		Z_INLINE_MEMBER Boolean is_valid() const
			{return scancode != INVALID;}

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
