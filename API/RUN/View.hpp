/* RUN Kit API - View.hpp
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

#ifndef _RUN_View_HPP_
#define _RUN_View_HPP_

#include <RUN/Backend.hpp>
#include <RUN/Scene.hpp>
#include <RUN/Color.hpp>
#include <Z/classes/base/Value2D.hpp>
#include <Z/classes/memory/Shared.hpp>

#if RUN_TARGET_HAS_KEYBOARD
#	include <RUN/Keyboard.hpp>
#endif

#if RUN_TARGET_HAS_MOUSE
#	include <RUN/Mouse.hpp>
#endif

#if RUN_TARGET_HAS_JOYSTICK
#	include <RUN/Joystick.hpp>
#endif

namespace RUN {
	using Zeta::Float;
	using Zeta::Natural;
	using Zeta::Shared;
	using Zeta::UInt8;
	using Zeta::Value2D;
}

class RUN_API RUN::View {
	public:
	void*		  native;
	Value2D<Real>	  size;
	Shared<Scene>	  root_scene;
	Scene*		  scene;
	Color<Float>	  background_color;

	//----------------------------------------------------------------
	/// The desired number of frames per second the view must execute.
	//----------------------------------------------------------------
	Natural volatile fps;

	protected:
	Boolean volatile _must_stop;

	private: struct {
		Boolean transitioning	    :1;
		Boolean reversed_transition :1;
	} _flags;

	public:

	View();
	~View();

	void create_native_view(const Value2D<Real> &size);
	void create_native_view(const Value2D<Real> &size, Backend backend);
	void destroy_view();
	void set_background_color(const Color<Float> &color);
	void update_geometry();
	void reset();
	void update(Real t);
	void draw();
	void set_scene(const Shared<Scene> &scene);
	void set_scene(const Shared<Scene> &scene, const Scene::Transition &transition);
	void push_scene(const Shared<Scene> &scene);
	void push_scene(const Shared<Scene> &scene, const Scene::Transition &transition);
	void pop_scene();
	void pop_scene(const Scene::Transition &transition);
	void pop_scene(Natural stack_level);
	void pop_scene(Natural stack_level, const Scene::Transition &transition);

#	if RUN_TARGET_HAS_KEYBOARD
		//---------------------------------------------------
		/// Maintains the state of every key of the keyboard.
		//---------------------------------------------------
		Keyboard keyboard;

		//-----------------------------------------------
		/// Called when a key of the keyboard is pressed.
		/// @param key The key that has been pressed.
		//-----------------------------------------------
		void key_down(Keyboard::Key key);

		//-----------------------------------------------
		// Called when a key of the keyboard is released.
		// @param key The key that has been released.
		//-----------------------------------------------
		void key_up(Keyboard::Key key);
#	endif

#	if RUN_TARGET_HAS_MOUSE
		//-----------------------------------
		/// Maintains the state of the mouse.
		//-----------------------------------
		Mouse mouse;

		//-------------------------------------------------
		/// Called when the mouse's cursor enters the view.
		/// @param point The point of the mouse's cursor.
		//-------------------------------------------------
		void mouse_entered(const Value2D<Real> &point);

		//------------------------------------------------
		/// Called when the mouse's cursor exits the view.
		/// @param point The point of the mouse's cursor.
		//------------------------------------------------
		void mouse_exited(const Value2D<Real> &point);

		//--------------------------------------------------------------
		/// Called when a mouse's button is pressed over the view.
		/// @param point The point of the mouse's cursor.
		/// @param button The index of the button that has been pressed.
		//--------------------------------------------------------------
		void mouse_down(const Value2D<Real> &point, UInt8 button);

		//---------------------------------------------------------------
		/// Called when a mouse's button is released.
		/// @param point The point of the mouse's cursor.
		/// @param button The index of the button that has been released.
		//---------------------------------------------------------------
		void mouse_up(const Value2D<Real> &point, UInt8 button);

		//-----------------------------------------------------
		/// Called when the mouse's cursor moves over the view.
		/// @param point The new point of the mouse's cursor.
		//-----------------------------------------------------
		void mouse_moved(const Value2D<Real> &point);

		//------------------------------------------------------
		/// Called when the mouse performs scroll over the view.
		/// @param movement The scroll in the X and Y axes.
		//------------------------------------------------------
		void mouse_scroll(const Value2D<Real> &movement);
#	endif

#	if RUN_TARGET_HAS_JOYSTICK
		private:
		Array<Joystick> _joysticks;

		public:
		void joystick_down (Joystick *joystick, UInt8 button);
		void joystick_up   (Joystick *joystick, UInt8 button);
		void joystick_moved(Joystick *joystick, UInt8 axis, Real angle);
#	endif

#	if RUN_TARGET_HAS_MULTITOUCH
		private:
		//Array<Touch> _touches;

		public:
		void touches_down();
		void touches_up();
		void touches_moved();
		void touches_cancelled();
#	endif
};


#endif // _RUN_View_HPP_
