/* RUN Kit API - Texture.hpp
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
