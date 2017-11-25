/* RUN Kit C++ API - World.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_World_HPP__
#define __RUN_World_HPP__

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

class RUN_API RUN::World {
	public:
	void*		  native_context;
	Value2D<Real>	  size;
	Shared<Scene>	  root_scene;
	Scene*		  scene;
	Color<Float>	  background_color;

	/*! The desired number of frames per second the world must execute. */
	Natural volatile fps;

	protected:
	Boolean volatile _must_stop;

	private: struct {
		Boolean transitioning	    :1;
		Boolean reversed_transition :1;
	} _flags;

	public:

	World();
	~World();

	void create_view(const Value2D<Real> &size);
	void create_view(const Value2D<Real> &size, Backend backend);
	void destroy_view();

	void set_background_color(const Color<Float> &color);

	void update_geometry();
	void reset();
	void update(Real t);
	void draw();

	void set_scene(const Shared<Scene> &scene);
	void push_scene(const Shared<Scene> &scene);
	void push_scene(const Shared<Scene> &scene, const Scene::Transition &transition);
	void pop_scene();
	void pop_scene(const Scene::Transition &transition);
	void pop_scene(Natural scene_index);
	void pop_scene(Natural scene_index, const Scene::Transition &transition);

#	if RUN_TARGET_HAS_KEYBOARD
		//---------------------------------------------------
		/// Maintains the state of every key of the keyboard.
		//---------------------------------------------------
		Keyboard keyboard;

		//-----------------------------------------------
		/// Called when a key of the keyboard is pressed.
		/// @param key The key that has been pressed.
		//-----------------------------------------------
		void keyboard_down(Keyboard::Key key);

		//------------------------------------------------
		/// Called when a key of the keyboard is released.
		/// @param key The key that has been released.
		//------------------------------------------------
		void keyboard_up(Keyboard::Key key);
#	endif

#	if RUN_TARGET_HAS_MOUSE
		//-----------------------------------
		/// Maintains the state of the mouse.
		//-----------------------------------
		Mouse mouse;

		//---------------------------------------------------------
		/// Called when the mouse's cursor enters the world's view.
		/// @param point The point of the mouse's cursor.
		//---------------------------------------------------------
		void mouse_entered(const Value2D<Real> &point);

		//--------------------------------------------------------
		/// Called when the mouse's cursor exits the world's view.
		/// @param point The point of the mouse's cursor.
		//--------------------------------------------------------
		void mouse_exited(const Value2D<Real> &point);

		//----------------------------------------------------------------
		/// Called when a mouse's button is pressed over the world's view.
		/// @param point The point of the mouse's cursor.
		/// @param button The index of the button that has been pressed.
		//----------------------------------------------------------------
		void mouse_down(const Value2D<Real> &point, UInt8 button);

		//---------------------------------------------------------------
		/// Called when a mouse's button is released.
		/// @param point The point of the mouse's cursor.
		/// @param button The index of the button that has been released.
		//---------------------------------------------------------------
		void mouse_up(const Value2D<Real> &point, UInt8 button);

		//-------------------------------------------------------------
		/// Called when the mouse's cursor moves over the world's view.
		/// @param point The new point of the mouse's cursor.
		//-------------------------------------------------------------
		void mouse_moved(const Value2D<Real> &point);

		//--------------------------------------------------------------
		/// Called when the mouse performs scroll over the world's view.
		/// @param movement The scroll in the X and Y axes.
		//--------------------------------------------------------------
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
		void touches_down ();
		void touches_up();
		void touches_moved();
		void touches_cancelled();
#	endif
};


#endif // __RUN_World_HPP__
