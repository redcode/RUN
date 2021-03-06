/* RUN Kit - common/View.cpp
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

#include <RUN/View.hpp>

using namespace RUN;


View::View()
: background_color(Color<Float>::black())
	{}


View::~View()
	{
	destroy_view();
	}


void View::create_native_view(const Value2D<Real> &size)
	{create_native_view(size, Backend::Default);}


void View::update_geometry()
	{
	}


void View::reset()
	{
	}


void View::update(Real t)
	{
	}


void View::draw()
	{
	}


void View::set_scene(const Shared<Scene> &scene)
	{
	this->scene = (this->root_scene = scene).get();
	}


void set_scene(const Shared<Scene> &scene, const Scene::Transition &transition)
	{
	}


void View::push_scene(const Shared<Scene> &scene)
	{
	}


void View::push_scene(const Shared<Scene> &scene, const Scene::Transition &transition)
	{
	}


void View::pop_scene()
	{
	}


void View::pop_scene(const Scene::Transition &transition)
	{
	}


void View::pop_scene(Natural stack_level)
	{
	}


void View::pop_scene(Natural stack_level, const Scene::Transition &transition)
	{
	}


#if RUN_TARGET_HAS_KEYBOARD

	void View::key_down(Keyboard::Key key)
		{
		keyboard += key;
		}


	void View::key_up(Keyboard::Key key)
		{
		keyboard -= key;
		}

#endif


#if RUN_TARGET_HAS_MOUSE

	void View::mouse_entered(const Value2D<Real> &point)
		{
		mouse = point;
		}


	void View::mouse_exited(const Value2D<Real> &point)
		{
		}


	void View::mouse_down(const Value2D<Real> &point, UInt8 button)
		{
		mouse += button;
		}


	void View::mouse_up(const Value2D<Real> &point, UInt8 button)
		{
		mouse -= button;
		}


	void View::mouse_moved(const Value2D<Real> &point)
		{
		mouse = point;
		}


	void View::mouse_scroll(const Value2D<Real> &movement)
		{
		}

#endif


#if RUN_TARGET_HAS_MULTITOUCH

	void View::touches_down()
		{
		}


	void View::touches_moved()
		{
		}


	void View::touches_up()
		{
		}


	void View::touches_cancelled()
		{
		}

#endif


// common/View.cpp EOF
