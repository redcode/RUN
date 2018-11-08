/* RUN Kit - common/Node.cpp
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

#include <RUN/Node.hpp>

using namespace RUN;


Node::Node()
	{
	point	 = 0.0;
	rotation = 0.0;
	scale	 = 1.0;
	alpha	 = 1.0;
	visible	 = true;
	}


Node::~Node()
	{
	}


void Node::set_point(Value3D<Real> point)
	{
	this->point = point;
	}


void Node::set_anchor(Value3D<Real> anchor)
	{
	this->anchor = anchor;
	}


void Node::set_rotation(Value3D<Real> rotation)
	{
	this->rotation = rotation;
	}


void Node::set_scale(Real scale)
	{
	this->scale = scale;
	}


// common/Node.cpp EOF
