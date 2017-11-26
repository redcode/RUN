/* RUN - UIKit/Program.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#define Z_USE_GC_GEOMETRY

#import <RUN/Program.hpp>
#import "_RUNView.h"
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


	- (BOOL) application:			(_RUNApplication *) application
		 didFinishLaunchingWithOptions: (NSDictionary	 *) options
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


#ifdef RUN_USE_IOS_KEYBOARD

#	include <Z/hardware/BUS/USB.h>
#	include <Z/formats/keymap/Z.h>
#	include "ObjCSecret.hpp"
#	include "Selector.hpp"

	static const auto $$handleKeyUIEvent = OBJC_SECRET(handleKeyUIEvent:);
	static const auto $$firstResponder   = OBJC_SECRET(firstResponder   );
	static const auto $$_keyCode	     = OBJC_SECRET(_keyCode	    );
	static const auto $$_isKeyDown       = OBJC_SECRET(_isKeyDown	    );

	static Selector<id()	> $firstResponder  ($$firstResponder  );
	static Selector<void(id)> $handleKeyUIEvent($$handleKeyUIEvent);
	static Selector<long()  > $_keyCode	   ($$_keyCode	      );
	static Selector<BOOL()  > $_isKeyDown	   ($$_isKeyDown      );

	static zuint8 const keymap[0xE8] = {Z_ARRAY_CONTENT_USB_KEY_CODE_TO_Z_KEY_CODE};

	@class _RUNView;
	static Class _RUNView_class;
	static Class UIApplication_class;


	static void _RUNApplication_handleKeyUIEvent(_RUNApplication *self, SEL _cmd, id event)
		{
		_RUNView *first_responder = $firstResponder(self.keyWindow);
		
		if (first_responder && [first_responder isKindOfClass: _RUNView_class])
			{
			long key_code = $_keyCode(event);

			if (key_code < 0xE8)
				{
				if (((BOOL (*)(id, SEL))objc_msgSend)(event, $_isKeyDown))
				/*if ($_isKeyDown(event))*/
					first_responder->world->key_down(keymap[key_code]);

				else first_responder->world->key_up(keymap[key_code]);
				}
			}

		else	{
			struct objc_super super {self, UIApplication_class};
			$handleKeyUIEvent.super(&super, event);
			}
		}

#endif


Program::Program(int argc, char **argv) : argc(argc), argv(argv)
	{
	//-------------------------------------.
	// Create the global autorelease pool. |
	//-------------------------------------'
	pool = [[NSAutoreleasePool alloc] init];

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

#	ifdef RUN_USE_IOS_KEYBOARD
		_RUNView_class	    = _RUNView.class;
		UIApplication_class = UIApplication.class;
#	endif

	singleton = this;
	}


Program::~Program()
	{
#	ifdef RUN_USE_IOS_BUG_WORKAROUNDS
		NSString_original_rangeOfString_options_range_locale = class_replace_method
			(NSString.class, @selector(rangeOfString:options:range:locale:),
			 (IMP)NSString_rangeOfString_options_range_locale);
#	endif

	[pool drain];
	singleton = NULL;
	}


void Program::run()
	{UIApplicationMain(argc, argv, @"_RUNApplication", @"_RUNApplicationDelegate");}


void Program::exit()
	{
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

