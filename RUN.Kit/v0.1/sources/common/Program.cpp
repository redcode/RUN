/* RUN - common/Program.cpp
  ______ __ ______  ___
 /   - //  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#include <RUN/Program.hpp>

using namespace RUN;

Program *Program::singleton = NULL;


void Program::schedule_world(World *world)
	{
	_active_worlds.push_back(world);
	}


void Program::unschedule_world(World *world)
	{
	for (auto i = _active_worlds.size(); i;) if (_active_worlds[--i] == world)
		{
		_active_worlds.erase(_active_worlds.begin() + i);
		return;
		}
	}


void Program::will_start	   () {}
void Program::did_start		   () {}
void Program::will_enter_background() {}
void Program::did_enter_background () {}
void Program::will_enter_foreground() {}
void Program::did_enter_foreground () {}
void Program::will_quit		   () {}


// common/Program.cpp EOF
