/* RUN Kit C++ API - Mouse.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Mouse_HPP__
#define __RUN_Mouse_HPP__

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


#endif // __RUN_Mouse_HPP__
