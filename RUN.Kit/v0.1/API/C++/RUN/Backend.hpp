/* RUN Kit C++ API - Backend.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Backend_HPP__
#define __RUN_Backend_HPP__

#include <RUN/namespace.hpp>

namespace RUN {

	enum Backend {
		DEFAULT,
		DIRECT_X,
		METAL,
		OPEN_GL,
		VULKAN
	};

}

#endif // __RUN_Backend_HPP__
