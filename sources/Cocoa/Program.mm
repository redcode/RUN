/* RUN - Cocoa/Program.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#import <RUN/Program.hpp>
#import <RUN/Window.hpp>
#import <Cocoa/Cocoa.h>

using namespace RUN;

static NSAutoreleasePool *pool;


@interface _RUNApplicationDelegate : NSObject <NSApplicationDelegate> {
	@public NSMutableArray* windows;
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

	//------------------------------------------.
	// Ensure Cocoa enters multithreading mode. |
	//------------------------------------------'
	[NSThread
		detachNewThreadSelector: @selector(nop:)
		toTarget:		 _RUNApplicationDelegate.class
		withObject:		 nil];

	if (![NSThread isMultiThreaded])
		{
		NSLog(@"ERROR: Cocoa failed to enter multithreading mode.");
		[pool drain];
		return;
		}

	//-----------------------------------------------------------------------------.
	// Ensure the application can be focused at launch even without a default XIB. |
	//-----------------------------------------------------------------------------'
	[NSApp setActivationPolicy: NSApplicationActivationPolicyRegular];

	//-----------------------------.
	// Get the application's name. |
	//-----------------------------'
	auto name = this->name().c_str();

	//------------------------------.
	// Create the application menu. |
	//------------------------------'
	auto	    main_menu = [[NSMenu alloc] init];
	NSMenu*     menu;
	NSMenuItem* item;

	menu = [[NSMenu alloc] init];

	[menu	addItemWithTitle: [NSString stringWithFormat: @"About %s", name]
		action:		  @selector(orderFrontStandardAboutPanel:)
		keyEquivalent:	  @""];

	[menu addItem: [NSMenuItem separatorItem]];

	auto services_menu = [[NSMenu alloc] init];
	NSApp.servicesMenu = services_menu;

	[menu	addItemWithTitle: @"Services"
		action:		  nil
		keyEquivalent:	  @""]
			.submenu = services_menu;

	[menu addItem: [NSMenuItem separatorItem]];

	[menu	addItemWithTitle: [NSString stringWithFormat: @"Hide %s", name]
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

	[menu	addItemWithTitle: [NSString stringWithFormat: @"Quit %s", name]
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
	NSApp.windowsMenu = menu;

	//----------------------------------------------------------------------------.
	// Create the Cocoa application's delegate needed to control the application. |
	//----------------------------------------------------------------------------'
	NSApp.delegate = [[_RUNApplicationDelegate alloc] init];

	//--------------------------------------------.
	// Set this instance as the singleton object. |
	//--------------------------------------------'
	singleton = this;
	}


Program::~Program()
	{
	id application_delegate = NSApp.delegate;
	NSApp.delegate = nil;
	[application_delegate release];
	[pool drain];
	singleton = NULL;
	}


Z_NO_RETURN void Program::run()
	{
	[NSApp finishLaunching];
	NSDate *distant_future = NSDate.distantFuture;

	loop: [NSApp sendEvent: [NSApp
		nextEventMatchingMask: NSAnyEventMask
		untilDate:	       distant_future
                inMode:		       NSDefaultRunLoopMode
                dequeue:	       YES]];

	goto loop;
	}


void Program::quit()
	{[NSApp terminate: NSApp.delegate];}


Zeta::Boolean Program::open_url(const String &url)
	{return [NSWorkspace.sharedWorkspace openURL: [NSURL URLWithString: @(url.c_str())]];}


// Cocoa/Program.mm EOF
