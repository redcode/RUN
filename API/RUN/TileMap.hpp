/* RUN Kit C++ API - TileMap.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_TileMap_HPP__
#define __RUN_TileMap_HPP__

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


#endif // __RUN_TileMap_HPP__
