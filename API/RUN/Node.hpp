/* RUN Kit API - Node.hpp
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

#ifndef _RUN_Node_HPP_
#define _RUN_Node_HPP_

#include <RUN/scope.hpp>
#include <Z/classes/base/Value3D.hpp>

namespace RUN {
	using Zeta::Boolean;
	using Zeta::Real;
	using Zeta::Value3D;
}

class RUN_API RUN::Node {
	public:
	Node*		next;
	Node*		previous;
	Node*		parent;
	Node*		children;
	Matrix4x4<Real> transform;
	Value3D<Real>	point;
	Value3D<Real>	anchor;
	Value3D<Real>	rotation;
	Real		scale;
	Real		alpha;
	Boolean		visible;

	Node();
	virtual ~Node();

	void set_point(Value3D<Real> point);
	void set_anchor(Value3D<Real> anchor);
	void set_rotation(Value3D<Real> rotation);
	void set_scale(Real scale);
	void enter_transform();
	void exit_transform();
	void draw();
};

#endif // _RUN_Node_HPP_
