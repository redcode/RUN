/* RUN Kit C++ API - configuration.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_configuration_HPP__
#define __RUN_configuration_HPP__

#include <Z/macros/language.h>
#include <Z/inspection/OS.h>

#define RUN_USE_IOS_BUG_WORKAROUNDS
#define RUN_USE_IOS_KEYBOARD

#ifndef RUN_API
#	ifdef RUN_STATIC
#		define RUN_API
#	else
#		define RUN_API Z_API
#	endif
#endif

#if Z_OS == Z_OS_MACOS || Z_OS == Z_OS_LINUX || Z_OS == Z_OS_WINDOWS

#	define RUN_TARGET_IS_WINDOWED  TRUE
#	define RUN_TARGET_HAS_KEYBOARD TRUE
#	define RUN_TARGET_HAS_MOUSE    TRUE
#	define RUN_TARGET_HAS_JOYSTICK TRUE

#elif Z_OS == Z_OS_IOS || Z_OS == Z_OS_ANDROID

#	define RUN_TARGET_IS_WINDOWED	 TRUE
#	define RUN_TARGET_HAS_MULTITOUCH TRUE
#	define RUN_TARGET_HAS_JOYSTICK	 TRUE

#	if Z_OS == Z_OS_IOS && defined(RUN_USE_IOS_KEYBOARD)
#		define RUN_TARGET_HAS_KEYBOARD TRUE
#	endif

#elif Z_OS == Z_OS_TVOS

#elif Z_OS == Z_OS_CELL_OS || Z_OS == Z_OS_ORBIS_OS

#	define RUN_TARGET_HAS_JOYSTICK TRUE

#endif

#ifndef RUN_TARGET_IS_WINDOWED
#	define RUN_TARGET_IS_WINDOWED FALSE
#endif

#ifndef RUN_TARGET_HAS_KEYBOARD
#	define RUN_TARGET_HAS_KEYBOARD FALSE
#endif

#ifndef RUN_TARGET_HAS_MOUSE
#	define RUN_TARGET_HAS_MOUSE FALSE
#endif

#ifndef RUN_TARGET_HAS_JOYSTICK
#	define RUN_TARGET_HAS_JOYSTICK FALSE
#endif

#ifndef RUN_TARGET_HAS_MULTITOUCH
#	define RUN_TARGET_HAS_MULTITOUCH FALSE
#endif

#endif // __RUN_configuration_HPP__
