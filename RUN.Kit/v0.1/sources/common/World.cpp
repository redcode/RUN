/* RUN - common/World.cpp
  ______ __ ______  ___
 /   - //  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#include <RUN/World.hpp>

using namespace RUN;


World::World()
: background_color(Color<Float>::black())
	{
	}


World::~World()
	{
	destroy_view();
	}


void World::create_view(const Value2D<Real> &size)
	{create_view(size, Backend::DEFAULT);}


void World::update_geometry()
	{
	}


void World::reset()
	{
	}


void World::update(Real t)
	{
	}


void World::draw()
	{
	}


void World::set_scene(const Shared<Scene> &scene)
	{
	this->root_scene = scene;
	this->scene = this->root_scene.get();
	}


void World::push_scene(const Shared<Scene> &scene)
	{
	}


void World::push_scene(const Shared<Scene> &scene, const Scene::Transition &transition)
	{
	}


void World::pop_scene()
	{
	}


void World::pop_scene(const Scene::Transition &transition)
	{
	}


void World::pop_scene(Natural scene_index)
	{
	}


void World::pop_scene(Natural scene_index, const Scene::Transition &transition)
	{
	}


#if RUN_TARGET_HAS_KEYBOARD

	void World::keyboard_down(Keyboard::Key key)
		{
		keyboard += key;
		}


	void World::keyboard_up(Keyboard::Key key)
		{
		keyboard -= key;
		}

#endif


#if RUN_TARGET_HAS_MOUSE

	void World::mouse_entered(const Value2D<Real> &point)
		{
		mouse = point;
		}


	void World::mouse_exited(const Value2D<Real> &point)
		{
		}


	void World::mouse_down(const Value2D<Real> &point, UInt8 button)
		{
		mouse += button;
		}


	void World::mouse_up(const Value2D<Real> &point, UInt8 button)
		{
		mouse -= button;
		}


	void World::mouse_moved(const Value2D<Real> &point)
		{
		mouse = point;
		}


	void World::mouse_scroll(const Value2D<Real> &movement)
		{
		}

#endif


#if RUN_TARGET_HAS_MULTITOUCH

	void World::touches_down()
		{
		}


	void World::touches_moved()
		{
		}


	void World::touches_up()
		{
		}


	void World::touches_cancelled()
		{
		}

#endif


// common/World.cpp EOF
