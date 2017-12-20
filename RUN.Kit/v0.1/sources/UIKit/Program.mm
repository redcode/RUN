/* RUN - UIKit/Program.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#import <RUN/Program.hpp>
#import "_RUNView.h"

using namespace RUN;

static NSAutoreleasePool *pool;


@interface _RUNApplication : UIApplication @end
@implementation _RUNApplication @end


@interface _RUNApplicationDelegate : UIResponder <UIApplicationDelegate> {
	UIWindow* _window;
}
@end


@implementation _RUNApplicationDelegate


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

#	import <objc/runtime.h>

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

	//------------------------------------------------------------------.
	// Selectors belonging to private APIs. Their names are enciphered  |
	// at compile-time to prevent Apple from rejecting the application. |
	//------------------------------------------------------------------'
#	import "ObjCSecret.hpp"

	static const auto $$handleKeyUIEvent = OBJC_SECRET(handleKeyUIEvent:);
	static const auto $$firstResponder   = OBJC_SECRET(firstResponder   );
	static const auto $$_keyCode	     = OBJC_SECRET(_keyCode	    );
	static const auto $$_isKeyDown       = OBJC_SECRET(_isKeyDown	    );
	static const auto $$sendEvent	     = OBJC_SECRET(sendEvent:	    );
	static const auto $$_gsEvent	     = OBJC_SECRET(_gsEvent	    );

	//----------------------------------------------------------------------.
	// Once in run-time, they are deciphered and transformed into functors. |
	//----------------------------------------------------------------------'
#	import "Selector.hpp"

	static Selector<void(id)       > $handleKeyUIEvent($$handleKeyUIEvent);
	static Selector<id()	       > $firstResponder  ($$firstResponder  );
	static Selector<long()	       > $_keyCode	  ($$_keyCode	     );
	static Selector<BOOL()	       > $_isKeyDown	  ($$_isKeyDown      );
	static Selector<void(UIEvent *)> $sendEvent	  ($$sendEvent	     );
	static Selector<Long *()       > $_gsEvent	  ($$_gsEvent	     );

	//----------------------------------------------------------------.
	// In the absence of more detailed research, the iOS keyboard map |
	// appears to be the one specified in the USB standard.		  |
	//----------------------------------------------------------------'
#	import <Z/hardware/BUS/USB.h>
#	import <Z/formats/keymap/Z.h>

	static zuint8 const keymap[0xE8] = {Z_ARRAY_CONTENT_USB_KEY_CODE_TO_Z_KEY_CODE};


	//-------------------------------.
	// iOS >= v7.0 keyboard handler. |
	//-------------------------------'
	static void _RUNApplication_handleKeyUIEvent(_RUNApplication *self, SEL _cmd, id event)
		{
		_RUNView *first_responder = $firstResponder(self.keyWindow);
		
		if (first_responder && [first_responder isKindOfClass: _RUNView.class])
			{
			long key_code = $_keyCode(event);

			if (key_code < 0xE8)
				{
				if ($_isKeyDown(event))
					first_responder->world->key_down(keymap[key_code]);

				else first_responder->world->key_up(keymap[key_code]);
				}
			}

		else $handleKeyUIEvent.super({self, UIApplication.class}, event);
		}


	//------------------------------.
	// iOS < v7.0 keyboard handler. |
	//------------------------------'
#	define GS_EVENT_OFFSET_TYPE 2

#	if Z_LONG_SIZE == 4
#		define GS_EVENT_OFFSET_KEY_CODE 15
#	elif Z_LONG_SIZE == 8
#		define GS_EVENT_OFFSET_KEY_CODE 13
#	endif

#	define GS_EVENT_FLAGS			   12
#	define GS_EVENT_TYPE_KEY_DOWN		   10
#	define GS_EVENT_TYPE_KEY_UP		   11
#	define GS_EVENT_TYPE_MODIFIER_KEYS_CHANGED 12

	static void _RUNApplication_sendEvent(_RUNApplication *self, SEL _cmd, UIEvent *event)
		{
		$sendEvent.super({self, UIApplication.class}, event);

		Long *event_memory;
		_RUNView *first_responder;

		if (	[event respondsToSelector: $_gsEvent]		    &&
			(event_memory = $_gsEvent(event))		    &&
			(first_responder = $firstResponder(self.keyWindow)) &&
			[first_responder isKindOfClass: _RUNView.class]
		)
			{
			UniChar key_code;

			switch (event_memory[GS_EVENT_OFFSET_TYPE])
				{
				case GS_EVENT_TYPE_KEY_DOWN:
				if ((key_code = UniChar(event_memory[GS_EVENT_OFFSET_KEY_CODE])) < 0xE8)
					first_responder->world->key_down(keymap[key_code]);
				break;

				case GS_EVENT_TYPE_KEY_UP:
				if ((key_code = UniChar(event_memory[GS_EVENT_OFFSET_KEY_CODE])) < 0xE8)
					first_responder->world->key_up(keymap[key_code]);
				break;

				case GS_EVENT_TYPE_MODIFIER_KEYS_CHANGED:
				// TODO

				default: break;
				}
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
		//--------------------------------------------------------------------------.
		// There is a bug in some versions of iOS that causes the program to crash  |
		// when using bluetooth keyboards and certain key combinations are pressed. |
		// This affects to any app (but some Apple ones seem to be unaffected).     |
		// A NSInvalidArgumentException is triggered with the following reason:     |
		//									    |
		// '*** -[__NSCFString rangeOfString:options:range:locale:]: nil argument'  |
		//									    |
		// To fix this, we replace the original method that triggers the exception  |
		// with a more permissive one.						    |
		//--------------------------------------------------------------------------'
		NSString_original_rangeOfString_options_range_locale = class_replace_method
			(NSString.class, @selector(rangeOfString:options:range:locale:),
			 (IMP)NSString_rangeOfString_options_range_locale);
#	endif

#	ifdef RUN_USE_IOS_KEYBOARD
		//--------------------------------------------------------------------.
		// In order to avoid the detection of private APIs usage, we override |
		// the method where the keyboard events are captured at run-time.     |
		//--------------------------------------------------------------------'
		Class UIApplicaation_class = UIApplication.class, _RUNApplication_class = _RUNApplication.class;
		Method handleKeyUIEvent = class_getInstanceMethod(UIApplicaation_class, $handleKeyUIEvent);

		if (handleKeyUIEvent) class_addMethod
			(_RUNApplication_class, $handleKeyUIEvent, (IMP)_RUNApplication_handleKeyUIEvent,
			 method_getDescription(handleKeyUIEvent)->types);

		else class_addMethod
			(_RUNApplication_class, $handleKeyUIEvent, (IMP)_RUNApplication_sendEvent,
			 method_getDescription(class_getInstanceMethod(UIApplicaation_class, $sendEvent))->types);
#	endif

	singleton = this;
	}


Program::~Program()
	{
#	ifdef RUN_USE_IOS_BUG_WORKAROUNDS
		class_replace_method
			(NSString.class, @selector(rangeOfString:options:range:locale:),
			 (IMP)NSString_original_rangeOfString_options_range_locale);
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


Zeta::Boolean Program::open_url(const String &url)
	{
	auto application = UIApplication.sharedApplication;
	auto u = [NSURL URLWithString: @(url.c_str())];

	if ([application respondsToSelector: @selector(openURL:)])
		return [application openURL: u];

	[application openURL: u options: @{} completionHandler: nil];
	return true;
	}


// UIKit/Program.mm

