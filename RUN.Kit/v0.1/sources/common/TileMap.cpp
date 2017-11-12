/* RUN - common/TileMap.cpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#include <RUN/TileMap.hpp>

using namespace RUN;


TileIndex TileMap::Layer::operator[](const Value2D<Natural> &point) const
	{
	return point <= _matrix_size
		? _matrix[_matrix_size.x * point.y + point.x]
		: 0;
	}


TileMap::TileMap(const String &file_path)
	{
	}


TileMap::~TileMap() {}


// common/TileMap.cpp EOF
