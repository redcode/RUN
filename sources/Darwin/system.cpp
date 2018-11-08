/* RUN Kit - Darwin/system.cpp
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

#include <RUN/scope.hpp>
#include <Z/types/base.hpp>
#include <mach/mach_time.h>

using namespace RUN;
using namespace Zeta;

static Boolean			 ticks_started = false;
static UInt64			 start_ticks;
static mach_timebase_info_data_t mach_base_info;


void initialize_ticks(void)
	{
	if (!ticks_started)
		{
		mach_timebase_info(&mach_base_info);
		start_ticks = mach_absolute_time();
		ticks_started = true;
		}
	}


UInt64 ticks(void)
	{
	return	((mach_absolute_time() - start_ticks) * mach_base_info.numer)
		/ mach_base_info.denom;
	}


// Darwin/system.cpp EOF
