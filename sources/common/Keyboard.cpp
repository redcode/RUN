/* RUN Kit - common/Keyboard.cpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
-------------------------------------------------------------------------------
This library is  free software: you can redistribute it  and/or modify it under
the terms  of the GNU  Lesser General Public License  as published by  the Free
Software Foundation, either  version 3 of the License, or  (at your option) any
later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received  a copy of the GNU Lesser General Public License along
with this library. If not, see <http://www.gnu.org/licenses/>.
---------------------------------------------------------------------------- */

#include <RUN/Keyboard.hpp>

using namespace RUN;

static Char const *const ansi_key_names[] {
	"↑", "→", "↓", "←",
#	if Z_OS == Z_OS_MACOS
		"↖︎", "↘︎",
#	else
		"⇤", "⇥",
#	endif
	"⇞", "⇟", "⌫", "↹", "⏎",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
#	if Z_OS == Z_OS_MACOS
		"F13", "F14", "F15",
#	else
		"⎙", "ScrLock", "Pause",
#	endif
	"⇪", "Esc", "L⇧", "L⌃",
#	if Z_OS == Z_OS_MACOS
		"L⌘",
#	else
		"L⊞",
#	endif
	"L⌥", "Space", "R⌥",
#	if Z_OS == Z_OS_MACOS
		"R⌘",
#	else
		"R⊞",
#	endif
	"Menu", "R⌃", "R⇧",
#	if Z_OS == Z_OS_MACOS
		"Help",
#	else
		"Insert",
#	endif
	"'",
	"KP /", "KP -", "KP *", "KP +",
	",", "-", ".", "/",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	"KP ⌅", ";", "KP .", "=",
#	if Z_OS == Z_OS_MACOS
		"⌧",
#	else
		"NumLock",
#	endif
	"KP 0", "KP 1",
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
	"[", "\\", "]",
	"KP 2", "KP 3",
	"`",
	"KP 4", "KP 5", "KP 6", "KP 7", "KP 8", "KP 9", "KP =",
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	"英数", "かな", "KP _", "¥", "KP ,",
	"ISO",
	"F16", "F17", "F18", "F19", "F20",
	"Fn", "⌦"
};


const Char *Keyboard::Key::name() const
	{return ansi_key_names[scancode];}


// common/Keyboard.cpp EOF
