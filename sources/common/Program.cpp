/* RUN - common/Program.cpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#include <RUN/Program.hpp>

using namespace RUN;

Program *Program::singleton = NULL;


void Program::schedule_view(View *view)
	{
	_active_views.push_back(view);
	}


void Program::unschedule_view(View *view)
	{
	for (auto i = _active_views.size(); i;) if (_active_views[--i] == view)
		{
		_active_views.erase(_active_views.begin() + i);
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
