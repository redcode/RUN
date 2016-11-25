/* RUN - UIKit/Program.mm
  ______ __ ______  ___
 /   - //  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#define Z_USE_GC_GEOMETRY

#import <RUN/Program.hpp>
#import <UIKit/UIKit.h>

using namespace RUN;

static NSAutoreleasePool *pool;


@interface _RUNApplicationDelegate : UIResponder <UIApplicationDelegate> {
	UIWindow* _window;
}
@end


@implementation _RUNApplicationDelegate


	- (id) init
		{
		if ((self = [super init]))
			{
			}

		return self;
		}


	- (BOOL) application:			 (UIApplication *) application
		 willFinishLaunchingWithOptions: (NSDictionary	*) optiona
		{
		[application setStatusBarStyle: UIStatusBarStyleDefault];
		 Program::singleton->will_start();
		 return YES;
		 }


	- (BOOL) application: (id) a didFinishLaunchingWithOptions:  (id) o {Program::singleton->did_start (); return YES;}

	- (void) applicationWillResignActive:	 (id) _ {Program::singleton->will_enter_background();}
	- (void) applicationDidEnterBackground:	 (id) _ {Program::singleton->did_enter_background ();}
	- (void) applicationWillEnterForeground: (id) _ {Program::singleton->will_enter_foreground();}
	- (void) applicationDidBecomeActive:	 (id) _ {Program::singleton->did_enter_foreground ();}
	- (void) applicationWillTerminate:	 (id) _ {Program::singleton->will_quit		  ();}


@end


Program::Program(int argc, char **argv) : argc(argc), argv(argv)
	{
	//-------------------------------------.
	// Create the global autorelease pool. |
	//-------------------------------------'
	pool = [[NSAutoreleasePool alloc] init];
	singleton = this;
	}


Program::~Program()
	{
	}


void Program::run()
	{
	UIApplicationMain(argc, argv, nil, NSStringFromClass([_RUNApplicationDelegate class]));
	}


/*String Program::resources_path()
	{
	}
*/


Boolean Program::open_url(const String &url)
	{
	auto application = UIApplication.sharedApplication;
	auto u = [NSURL URLWithString: @(url.c_str())];

	if ([application respondsToSelector: @selector(openURL:)])
		return [application openURL: u];

	[application openURL: u options: @{} completionHandler: nil];
	return true;
	}


// UIKit/Program.mm
