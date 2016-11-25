/* RUN - common/Node.cpp
  ______ __ ______  ___
 /   - //  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

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
