/* RUN - Darwin/system.cpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#include <RUN/namespace.hpp>
#include <mach/mach_time.h>

using namespace RUN;

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
