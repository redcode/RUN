/* RUN Kit C++ API - Node.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Node_HPP__
#define __RUN_Node_HPP__

#include <RUN/namespace.hpp>
#include <Z/classes/base/Value3D.hpp>

namespace RUN {class RUN_API Node {
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
};}

#endif // __RUN_Node_HPP__
