/* RUN Kit C++ API - Color.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Color_HPP__
#define __RUN_Color_HPP__

#include <RUN/namespace.hpp>


namespace RUN {template <class T> struct Color {
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

};}


#endif // __RUN_Color_HPP__
