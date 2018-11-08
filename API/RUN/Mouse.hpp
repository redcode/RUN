/* RUN Kit API - Mouse.hpp
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

#ifndef _RUN_Mouse_HPP_
#define _RUN_Mouse_HPP_

#include <RUN/scope.hpp>
#include <Z/classes/base/Value2D.hpp>

namespace RUN {
	using Zeta::Real;
	using Zeta::UInt8;
	using Zeta::UInt32;
	using Zeta::Value2D;
}


struct RUN::Mouse {
	Value2D<Real> point;
	UInt32        button_state;

	Mouse() : point(0.0), button_state(0) {}


	Z_INLINE operator bool() const
		{return button_state;}


	Z_INLINE operator Value2D<Real>() const
		{return point;}


	Z_INLINE Mouse &operator =(const Value2D<Real> &point)
		{
		this->point = point;
		return *this;
		}


	Z_INLINE bool operator[](UInt8 button) const
		{return button_state & (UInt32(1) << button);}


	Z_INLINE Mouse &operator +=(UInt8 button)
		{
		button_state |= UInt32(1) << button;
		return *this;
		}


	Z_INLINE Mouse &operator -=(UInt8 button)
		{
		button_state &= ~(UInt32(1) << button);
		return *this;
		}
};


#endif // _RUN_Mouse_HPP_
