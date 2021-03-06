/* RUN Kit API - Program.hpp
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

#ifndef _RUN_Program_HPP_
#define _RUN_Program_HPP_

#include <RUN/View.hpp>

class RUN_API RUN::Program {
	public:

	//-----------------------------------
	/// Pointer to the program singleton.
	//-----------------------------------
	static Program* singleton;

	protected:
	Array<View *> _active_views;

	public:

	//------------------------------------------------
	/// The number of arguments passed to the program.
	//------------------------------------------------
	int argc;

	//-----------------------------------------------
	/// The array of arguments passed to the program.
	//-----------------------------------------------
	char** argv;

	//------------------------------------------------------------
	/// Constructor.
	/// @param argc The number of arguments passed to the program.
	/// @param argv The array of arguments passed to the program.
	//------------------------------------------------------------
	Program(int argc, char **argv);

	//-------------
	/// Destructor.
	//-------------
	virtual ~Program();

	//------------------------------------
	/// Enters to the program's main loop.
	//------------------------------------
	void run();

#	if RUN_TARGET_IS_QUITABLE
		//-------------------------------------------------------------
		/// Exits the program's main loop, causing the program to quit.
		//-------------------------------------------------------------
		void quit();
#	endif

	void schedule_view(View *view);
	void unschedule_view(View *view);

	//------------------------------------------------------------
	/// Opens an URL using the operating system's default browser.
	/// @param url A string with the URL to open.
	/// @return @c true if the the URL was successfully opened;
	///	    @c false otherwise.
	//------------------------------------------------------------
	virtual Boolean open_url(const String &url);

	//----------------------------------------------------------------------
	/// Gets the path of the program's resources directory.
	/// @return A string with the path of the program's resources directory.
	//----------------------------------------------------------------------
	virtual String resources_path();

	//-------------------------------------------
	/// Gets the program's name.
	/// @return A string with the program's name.
	//-------------------------------------------
	virtual String name();

	//----------------------------------------------
	/// Gets the program's version.
	/// @return A string with the program's version.
	//----------------------------------------------
	virtual String version();

	//--------------------------------------------------------------------
	/// Gets the operating system's locale language.
	/// @return A string with the ISO 639-1 code of the operating system's
	/// locale language in lower case.
	//--------------------------------------------------------------------
	virtual String locale_language();

	//-----------------------------------
	/// Called before the program starts.
	//-----------------------------------
	virtual void will_start();

	//----------------------------------
	/// Called after the program starts.
	//----------------------------------
	virtual void did_start();

	//------------------------------------------------------------
	/// Called before transitioning from foreground to background.
	//------------------------------------------------------------
	virtual void will_enter_background();

	//-----------------------------------------------------------
	/// Called after transitioning from foreground to background.
	//-----------------------------------------------------------
	virtual void did_enter_background();

	//------------------------------------------------------------
	/// Called before transitioning from background to foreground.
	//------------------------------------------------------------
	virtual void will_enter_foreground();

	//-----------------------------------------------------------
	/// Called after transitioning from background to foreground.
	//-----------------------------------------------------------
	virtual void did_enter_foreground();

	//-------------------------------------
	/// Called before quitting the program.
	//-------------------------------------
	virtual void will_quit();
};

#endif // _RUN_Program_HPP_
