/* RUN Kit C++ API - Mouse.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Mouse_HPP__
#define __RUN_Mouse_HPP__

#include <RUN/namespace.hpp>
#include <Z/classes/base/Value2D.hpp>


namespace RUN {struct Mouse {
	Value2D<Real> point;
	UInt32        button_state;

	Mouse() : point(0.0), button_state(0) {}


	Z_INLINE_MEMBER operator bool() const
		{return button_state;}


	Z_INLINE_MEMBER operator Value2D<Real>() const
		{return point;}


	Z_INLINE_MEMBER Mouse &operator =(const Value2D<Real> &point)
		{
		this->point = point;
		return *this;
		}


	Z_INLINE_MEMBER bool operator[](UInt8 button) const
		{return button_state & (UInt32(1) << button);}


	Z_INLINE_MEMBER Mouse &operator +=(UInt8 button)
		{
		button_state |= UInt32(1) << button;
		return *this;
		}


	Z_INLINE_MEMBER Mouse &operator -=(UInt8 button)
		{
		button_state &= ~(UInt32(1) << button);
		return *this;
		}
};}


#endif // __RUN_Mouse_HPP__
