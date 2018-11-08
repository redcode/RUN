/* RUN Kit API - Window.hpp
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

#ifndef _RUN_Window_HPP_
#define _RUN_Window_HPP_

#include <RUN/View.hpp>

class RUN_API RUN::Window {
	protected:
	void* native;

	public:

	typedef UInt8 Mode;

	enum {	Resizable	    = 1,
		PreserveAspectRatio = 2,
		FullScreen	    = 4
	};

	View *view;

	Window(const Value2D<Real> &cotent_size, Mode mode);
	virtual ~Window();

	Value2D<Real> content_size() const;
	void set_content_size(const Value2D<Real> &size);

	Value2D<Real> content_aspect_ratio() const;
	void set_content_aspect_ratio(const Value2D<Real> &aspect_ratio);

	String title() const;
	void set_title(const String &title);

	Boolean full_screen() const;
	void set_full_screen(Boolean);

	Boolean is_focused();
	Boolean is_maximized();
	Boolean is_minimized();
	Boolean is_visible();
};

#endif // _RUN_Window_HPP_
