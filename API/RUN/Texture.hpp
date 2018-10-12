/* RUN Kit C++ API - Texture.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef _RUN_Texture_HPP_
#define _RUN_Texture_HPP_

#include <RUN/scope.hpp>
#include <Z/classes/mathematics/geometry/euclidean/Rectangle.hpp>

namespace RUN {
	using Zeta::Boolean;
	using Zeta::Real;
	using Zeta::Rectangle;
	using Zeta::UInt8;
	using Zeta::Value2D;
}

class RUN_API RUN::Texture {
	public:

	enum Format {
	};

	struct Frame {
		Rectangle<Real>  rectangle;
		Real		 rotation;
		Boolean		 flipped_x;
		Boolean		 flipped_y;
	};

	Format	      format;
	Value2D<Real> size;
	UInt8*	      data;
	Boolean	      binded;

	Texture(const String &file_path);
	~Texture();
	void bind();
	void unbind();

#	ifdef RUN_TEXTURE_PRIVATE_PROTOTYPES
		private: RUN_TEXTURE_PRIVATE_PROTOTYPES
#	endif
};

#endif // _RUN_Texture_HPP_
