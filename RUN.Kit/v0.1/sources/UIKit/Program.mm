/* RUN - UIKit/Program.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#define Z_USE_GC_GEOMETRY

#import <RUN/Program.hpp>
#import <UIKit/UIKit.h>
#import <objc/objc.h>
#import <objc/message.h>

using namespace RUN;

static NSAutoreleasePool *pool;


@interface _RUNApplication : UIApplication @end
@implementation _RUNApplication @end


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


	- (BOOL) application:			 (_RUNApplication *) application
		 willFinishLaunchingWithOptions: (NSDictionary	  *) optiona
		{
		[application setStatusBarStyle: UIStatusBarStyleDefault];
		Program::singleton->will_start();
		return YES;
		}


	- (BOOL) application:			(_RUNApplication) application
		 didFinishLaunchingWithOptions: (NSDictionary  *) options
		{
		Program::singleton->did_start();
		return YES;
		}


	- (void) applicationWillResignActive:	 (id) _ {Program::singleton->will_enter_background();}
	- (void) applicationDidEnterBackground:	 (id) _ {Program::singleton->did_enter_background ();}
	- (void) applicationWillEnterForeground: (id) _ {Program::singleton->will_enter_foreground();}
	- (void) applicationDidBecomeActive:	 (id) _ {Program::singleton->did_enter_foreground ();}
	- (void) applicationWillTerminate:	 (id) _ {Program::singleton->will_quit		  ();}


@end


#ifdef RUN_USE_IOS_BUG_WORKAROUNDS

	static IMP NSString_original_rangeOfString_options_range_locale;


	static NSRange NSString_rangeOfString_options_range_locale(
		id		       self,
		SEL		       _cmd,
		NSString*	       searchString,
		NSStringCompareOptions mask,
		NSRange		       rangeOfReceiverToSearch,
		NSLocale*	       locale
	)
		{
		if (searchString)
			{
			@try	{
				return ((NSRange(*)(id, SEL, NSString *, NSStringCompareOptions, NSRange, NSLocale *))
				NSString_original_rangeOfString_options_range_locale)
					(self, _cmd, searchString, mask, rangeOfReceiverToSearch, locale);
				}

			@catch (NSException *exception) {}
			}

#		ifdef RUN_USE_IOS_BUG_MESSAGES
			NSLog	(@"Bug calling -[NSString rangeOfString:options:range:locale:]\n"
				  "\tself                    => %@\n"
				  "\tsearchString            => %@\n"
				  "\tmask                    => %lu\n"
				  "\trangeOfReceiverToSearch => %@",
				 self, searchString, mask, NSStringFromRange(rangeOfReceiverToSearch));
#		endif

		return NSMakeRange(NSNotFound, 0);
		}


	static IMP class_replace_method(Class klass, SEL method_name, IMP new_implementation)
		{
		Method original_method = class_getInstanceMethod(klass, method_name);
		IMP original_implementation = method_getImplementation(original_method);

		class_replaceMethod(klass, method_name, new_implementation, method_getDescription(original_method)->types);
		return original_implementation;
		}

#endif



Program::Program(int argc, char **argv) : argc(argc), argv(argv)
	{
#	ifdef RUN_USE_IOS_BUG_WORKAROUNDS
		//-------------------------------------------------------------------------.
		// There is a bug in some versions of iOS that causes the program to crash |
		// when using bluetooth keyboards and certain key combinations are used.   |
		// This affects to any app (but some Apple ones seem to be unaffected).    |
		// A NSInvalidArgumentException is triggered with the following reason:    |
		//									   |
		// '*** -[__NSCFString rangeOfString:options:range:locale:]: nil argument' |
		//									   |
		// To fix this, we replace the original method that triggers the exception |
		// with a more permissive one.						   |
		//-------------------------------------------------------------------------'
		NSString_original_rangeOfString_options_range_locale = class_replace_method
			(NSString.class, @selector(rangeOfString:options:range:locale:),
			 (IMP)NSString_rangeOfString_options_range_locale);
#	endif

	//-------------------------------------.
	// Create the global autorelease pool. |
	//-------------------------------------'
	pool = [[NSAutoreleasePool alloc] init];
	singleton = this;
	}


Program::~Program()
	{
	[pool drain];

#	ifdef RUN_USE_IOS_BUG_WORKAROUNDS
		NSString_original_rangeOfString_options_range_locale = class_replace_method
			(NSString.class, @selector(rangeOfString:options:range:locale:),
			 (IMP)NSString_rangeOfString_options_range_locale);
#	endif

	singleton = NULL;
	}


void Program::run()
	{UIApplicationMain(argc, argv, @"_RUNApplication", @"_RUNApplicationDelegate");}


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

