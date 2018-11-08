/* RUN Kit API - Color.hpp
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

#ifndef _RUN_Color_HPP_
#define _RUN_Color_HPP_

#include <RUN/scope.hpp>


template <class T> struct RUN::Color {
	T r, g, b, a;


	Z_INLINE Color(T r, T g, T b, T a)
	: r(r), g(g), b(b), a(a) {}


	Z_INLINE Color(T r, T g, T b)
	: r(r), g(g), b(b), a(1) {}


	Z_INLINE static Color black  () {return Color(T(0  ), T(0  ), T(0  ));}
	Z_INLINE static Color blue   () {return Color(T(0  ), T(0  ), T(1  ));}
	Z_INLINE static Color cyan   () {return Color(T(0  ), T(1  ), T(1  ));}
	Z_INLINE static Color green  () {return Color(T(0  ), T(1  ), T(0  ));}
	Z_INLINE static Color magenta() {return Color(T(1  ), T(0  ), T(1  ));}
	Z_INLINE static Color orange () {return Color(T(1  ), T(0.5), T(0  ));}
	Z_INLINE static Color purple () {return Color(T(0.5), T(0  ), T(0.5));}
	Z_INLINE static Color red    () {return Color(T(1  ), T(0  ), T(0  ));}
	Z_INLINE static Color white  () {return Color(T(1  ), T(1  ), T(1  ));}
	Z_INLINE static Color yellow () {return Color(T(1  ), T(1  ), T(0  ));}

};


#endif // _RUN_Color_HPP_
