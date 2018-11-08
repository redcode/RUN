/* RUN Kit API - TileMap.hpp
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

#ifndef _RUN_TileMap_HPP_
#define _RUN_TileMap_HPP_

#include <RUN/scope.hpp>
#include <Z/classes/base/Value2D.hpp>

namespace RUN {
	using Zeta::Natural;
	using Zeta::Value2D;
	using Zeta::Real;

	typedef Zeta::UInt16 TileIndex;
}


class RUN_API RUN::TileMap {
	public:

	class Layer {
		protected:
		TileIndex*	 _matrix;
		Value2D<Natural> _matrix_size;

		public:
		TileIndex operator[](const Value2D<Natural> &point) const;
	};

	Array<Layer>  layers;
	Value2D<Real> tile_size;
	Value2D<Real> size_in_tiles;

	TileMap(const String &file_path);
	~TileMap();

#	ifdef RUN_TILE_MAP_PRIVATE_PROTOTYPES
		private: RUN_TILE_MAP_PRIVATE_PROTOTYPES
#	endif
};


#endif // _RUN_TileMap_HPP_
