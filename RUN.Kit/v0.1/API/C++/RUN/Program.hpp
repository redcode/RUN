/* RUN Kit C++ API - Program.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Program_HPP__
#define __RUN_Program_HPP__

#include <RUN/World.hpp>
#include <Z/inspection/OS.h>

namespace RUN {class RUN_API Program {
	protected:
#	if Z_OS == Z_OS_MACOS || Z_OS == Z_OS_IOS
		void* _native_context;
#	endif

	Array<World *> _active_worlds;

	public:

	//-----------------------------------
	/// Pointer to the program singleton.
	//-----------------------------------
	static Program* singleton;

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

	//--------------------------------
	/// Exits the program's main loop.
	//--------------------------------
	void exit();

	//-------------------------------------------------------------
	/// Exits the program's main loop, causing the program to quit.
	//-------------------------------------------------------------
	void quit();

	void schedule_world(World *world);
	void unschedule_world(World *world);

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
};}

#endif // __RUN_Program_HPP__
