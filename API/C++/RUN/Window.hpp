/* RUN Kit C++ API - Window.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Window_HPP__
#define __RUN_Window_HPP__

#include <RUN/World.hpp>

class RUN_API RUN::Window {
	protected:
	void* native_context;

	public:

	typedef UInt8 Mode;

	enum {	Resizable	    = 1,
		PreserveAspectRatio = 2,
		FullScreen	    = 4
	};

	World *world;

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

#endif // __RUN_Window_HPP__
