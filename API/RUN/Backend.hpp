/* RUN Kit C++ API - Backend.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef _RUN_Backend_HPP_
#define _RUN_Backend_HPP_

#include <RUN/scope.hpp>

namespace RUN {

	enum Backend {
		Default,
		DirectX,
		Metal,
		OpenGL,
		Vulkan
	};

}

#endif // _RUN_Backend_HPP_
