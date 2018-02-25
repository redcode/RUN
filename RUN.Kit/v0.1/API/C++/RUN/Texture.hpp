/* RUN Kit C++ API - Texture.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Texture_HPP__
#define __RUN_Texture_HPP__

#include <RUN/namespace.hpp>
#include <Z/classes/mathematics/geometry/euclidean/Rectangle.hpp>


namespace RUN {class RUN_API Texture {
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
};}


#endif // __RUN_Texture_HPP__
