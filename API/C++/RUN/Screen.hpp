/* RUN Kit C++ API - Screen.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Screen_HPP__
#define __RUN_Screen_HPP__

#include <RUN/scope.hpp>

class RUN_API RUN::Screen {

	static Screen main_screen();
	static Array<Screen> all_screens();

};

#endif // __RUN_Screen_HPP__
