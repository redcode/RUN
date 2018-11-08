/* RUN Kit - common/Program.cpp
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
