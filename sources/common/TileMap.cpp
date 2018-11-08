/* RUN Kit - common/TileMap.cpp
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
