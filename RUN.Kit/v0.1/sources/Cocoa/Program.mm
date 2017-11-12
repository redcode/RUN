/* RUN - Cocoa/Program.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#include <RUN/Program.hpp>
#include <Cocoa/Cocoa.h>
#include <RUN/Window.hpp>

#define APPLICATION_DELEGATE ((_RUNApplicationDelegate *)_native_context)

using namespace RUN;

static NSAutoreleasePool* pool;


@interface _RUNApplicationDelegate : NSObject <NSApplicationDelegate> {
	@public
	NSMutableArray* windows;
};
@end


@implementation _RUNApplicationDelegate

	+ (void) nop: (id) object {}


	- (id) init
		{
		if ((self = [super init]))
			{
			windows = [[NSMutableArray alloc] init];
			}

		return self;
		}


	- (void) dealloc
		{
		[windows release];
		[super dealloc];
		}


	- (void) applicationWillFinishLaunching: (id) _ {Program::singleton->will_start		  ();}
	- (void) applicationDidFinishLaunching:	 (id) _ {Program::singleton->did_start		  ();}
	- (void) applicationWillResignActive:	 (id) _ {Program::singleton->will_enter_background();}
	- (void) applicationDidResignActive:	 (id) _ {Program::singleton->did_enter_background ();}
	- (void) applicationWillBecomeActive:	 (id) _ {Program::singleton->will_enter_foreground();}
	- (void) applicationDidBecomeActive:	 (id) _ {Program::singleton->did_enter_foreground ();}
	- (void) applicationWillTerminate:	 (id) _ {Program::singleton->will_quit(); [windows release];}

	- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (id) _ {return YES;}

	- (void) applicationDidChangeScreenParameters:(id) _ {}
	- (void) applicationDidHide: (id) _ {}

@end


Program::Program(int argc, char **argv) : argc(argc), argv(argv)
	{
	//---------------------------------------------------------------.
	// Create the global autorelease pool and the Cocoa application. |
	//---------------------------------------------------------------'
	pool = [[NSAutoreleasePool alloc] init];
	[NSApplication sharedApplication];

	//----------------------------------------------.
	// Ensure Cocoa enters in multithreading state. |
	//----------------------------------------------'
	[NSThread
		detachNewThreadSelector: @selector(nop:)
		toTarget:		 _RUNApplicationDelegate.class
		withObject:		 nil];

	//-----------------------------------------------------------------------------.
	// Ensure the application can be focused at launch even without a default XIB. |
	//-----------------------------------------------------------------------------'
	[NSApp setActivationPolicy: NSApplicationActivationPolicyRegular];

	//-----------------------------.
	// Get the application's name. |
	//-----------------------------'
	auto name = @(this->name().c_str());

	//------------------------------.
	// Create the application menu. |
	//------------------------------'
	auto	    main_menu = [[NSMenu alloc] init];
	NSMenu*     menu;
	NSMenuItem* item;

	menu = [[NSMenu alloc] init];

	[menu	addItemWithTitle: [@"About " stringByAppendingString: name]
		action:		  @selector(orderFrontStandardAboutPanel:)
		keyEquivalent:	  @""];

	[menu addItem: [NSMenuItem separatorItem]];

	auto services_menu = [[NSMenu alloc] init];
	[NSApp setServicesMenu: services_menu];

	[menu	addItemWithTitle: @"Services"
		action:		  nil
		keyEquivalent:	  @""]
	.submenu = services_menu;

	[menu addItem: [NSMenuItem separatorItem]];

	[menu	addItemWithTitle: [@"Hide " stringByAppendingString: name]
		action:		  @selector(hide:)
		keyEquivalent:	  @"h"];

	[menu	addItemWithTitle: @"Hide Others"
		action:		  @selector(hideOtherApplications:)
		keyEquivalent:	  @"h"]
	.keyEquivalentModifierMask = NSAlternateKeyMask | NSCommandKeyMask;

	[menu	addItemWithTitle: @"Show All"
		action:		  @selector(unhideAllApplications:)
		keyEquivalent:	  @""];

	[menu addItem: [NSMenuItem separatorItem]];

	[menu	addItemWithTitle: [@"Quit " stringByAppendingString: name]
		action:		  @selector(terminate:)
		keyEquivalent:	  @"q"];

	[menu addItem: [NSMenuItem separatorItem]];

	(item = [[NSMenuItem alloc] init]).submenu = menu;
	[menu release];
	[main_menu addItem: item];
	[item release];
	NSApp.mainMenu = main_menu;
	[main_menu release];

	//--------------------------------------------------.
	// Dirty trick to make the application menu to work |
	// properly on Leopard and older versions of macOS. |
	//--------------------------------------------------'
#	if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_6
		[NSApp performSelector: NSSelectorFromString(@"setAppleMenu:") withObject: menu];
#	endif

	//---------------------------.
	// Create the "Window" menu. |
	//---------------------------'
	menu = [[NSMenu alloc] init];
	menu.title = @"Window";

	[menu	addItemWithTitle: @"Minimize"
		action:		  @selector(performMiniaturize:)
		keyEquivalent:	  @"m"];

	[menu	addItemWithTitle: @"Zoom"
		action:		  @selector(performZoom:)
		keyEquivalent:	  @""];

	[menu addItem: [NSMenuItem separatorItem]];

	[menu	addItemWithTitle: @"Bring All to Front"
		action:		  @selector(arrangeInFront:)
		keyEquivalent:	  @""];

	[menu addItem: [NSMenuItem separatorItem]];

	[menu	addItemWithTitle: @"Enter Full Screen"
		action:		  @selector(toggleFullScreen:)
		keyEquivalent:	  @"f"]
	.keyEquivalentModifierMask = NSControlKeyMask | NSCommandKeyMask;

	[menu addItem: [NSMenuItem separatorItem]];

	(item = [[NSMenuItem alloc] init]).submenu = menu;
	[menu release];
	[main_menu addItem: item];
	[item release];
	[NSApp setWindowsMenu: menu];

	//--------------------------------------------------------------------------.
	// Create the Cocoa application delegate needed to control the application. |
	//--------------------------------------------------------------------------'
	_native_context = [[_RUNApplicationDelegate alloc] init];
	NSApp.delegate = APPLICATION_DELEGATE;
	//[APPLICATION_DELEGATE release];

	//--------------------------------------------.
	// Set this instance as the singleton object. |
	//--------------------------------------------'
	singleton = this;
	}


Program::~Program()
	{
	NSApp.delegate = nil;
	[APPLICATION_DELEGATE release];
	[pool drain];
	}


void Program::run()
	{
	[NSApp finishLaunching];
	NSDate *distant_future = NSDate.distantFuture, *date = distant_future;
        NSEvent* event;

	loop: if ((event = [NSApp
		nextEventMatchingMask: NSAnyEventMask
		untilDate:	       date
                inMode:		       NSDefaultRunLoopMode
                dequeue:	       YES]
	))
		{
		if (event.type == NSEventTypeApplicationDefined && date)
			{
			NSLog(@"___________________________");
			date = nil;
			}

		[NSApp sendEvent: event];
		}
	NSLog(@"loop");
	goto loop;

	//[NSApp run];
	}


void Program::exit()
	{
	NSLog(@"exit()");
	[NSApp	postEvent: [NSEvent
			otherEventWithType: NSEventTypeApplicationDefined
			location:	    NSZeroPoint
			modifierFlags:	    0
			timestamp:	    0
			windowNumber:	    -1
			context:	    nil
			subtype:	    0
			data1:		    0
			data2:		    0]
		atStart: YES];
	}


Boolean Program::open_url(const String &url)
	{return [NSWorkspace.sharedWorkspace openURL: [NSURL URLWithString: @(url.c_str())]];}


// Cocoa/Program.mm EOF
