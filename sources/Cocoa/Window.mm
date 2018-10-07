/* RUN - Cocoa/Window.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#define Z_USE_NS_GEOMETRY
#include <RUN/Window.hpp>
#include <RUN/Program.hpp>
#include <Z/classes/mathematics/geometry/euclidean/Rectangle.hpp>
#include <Cocoa/Cocoa.h>

#define NATIVE_WINDOW ((_RUNWindow *)native)
#define WINDOW_STYLE NSClosableWindowMask | NSMiniaturizableWindowMask | NSTitledWindowMask

using namespace RUN;
using Zeta::Rectangle;


@interface _RUNWindow : NSWindow <NSWindowDelegate> {
	@public
	Window *window;
} @end


@implementation _RUNWindow
	- (BOOL) canBecomeKeyWindow {return YES;};


	- (void) windowDidBecomeKey:(id) _ {}
	- (void) windowDidResignKey:(id) _ {}
	- (void) windowDidResize: (id) _ {NSLog(@"[NSWindow windowDidResize");}
	- (void) windowDidMove: (id) _ {}
	- (void) windowDidMiniaturize:(id) _ {}
	- (void) windowDidDeminiaturize:(id) _ {}
	- (BOOL) windowShouldClose: (id) _ {return YES;}
@end



static NSScreen *suitable_screen_for_size(NSScreen *current_screen, const Value2D<Real> &size)
	{
	Rectangle<Real> screen_frame = current_screen.visibleFrame;

	if (screen_frame.size < size) for (NSScreen *screen in NSScreen.screens)
		if (size <= screen.visibleFrame.size) return screen;

	return current_screen;
	}


Window::Window(const Value2D<Real> &size, Mode mode)
	{
	native = [[_RUNWindow alloc]
		initWithContentRect: size
		styleMask:	     (mode & Resizable) ? WINDOW_STYLE | NSResizableWindowMask : WINDOW_STYLE
		backing:	     NSBackingStoreBuffered
		defer:		     NO];

	NATIVE_WINDOW.title		      = @(Program::singleton->name().c_str());
	NATIVE_WINDOW.restorable	      = NO;
	NATIVE_WINDOW.acceptsMouseMovedEvents = YES;
	NATIVE_WINDOW->window		      = this;

	Value2D<Real> window_size = NATIVE_WINDOW.frame.size;
	Rectangle<Real> screen_frame = suitable_screen_for_size(NSScreen.mainScreen, window_size).visibleFrame;

	if (screen_frame.size < window_size)
		{
		auto window_border = window_size - ((NSView *)NATIVE_WINDOW.contentView).bounds.size;

		window_size = window_border + (window_size - window_border).fit(screen_frame.size - window_border);
		if (window_size.y == screen_frame.size.y) window_size.x = floor(window_size.x);
		else window_size.y = floor(window_size.y);
		}

	[NATIVE_WINDOW
		setFrame: Rectangle<Real>
			(screen_frame.point.x + round(screen_frame.size.x  - window_size.x) / 2.0,
			 screen_frame.point.y + floor((screen_frame.size.y - window_size.y) * 2.0 / 3.0),
			 window_size)
		display: YES];

	view = new View();
	view->create_view([NATIVE_WINDOW.contentView frame].size);

	//view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
	//[WINDOW.contentView addSubview: (NSView *)view->native];

	NATIVE_WINDOW.contentView = (NSView *)view->native;
	[NATIVE_WINDOW makeFirstResponder: (NSView *)view->native];
	//[WINDOW.contentView addSubview: system_view];
	if (mode & PreserveAspectRatio) NATIVE_WINDOW.contentAspectRatio = size;
	NATIVE_WINDOW.delegate = NATIVE_WINDOW;
	[NATIVE_WINDOW makeKeyAndOrderFront: nil];
	}


Window::~Window()
	{
	[NATIVE_WINDOW performClose: nil];
	NATIVE_WINDOW.delegate = nil;
	[NATIVE_WINDOW release];
	}


Value2D<Real> Window::content_size() const
	{return NATIVE_WINDOW.frame.size;}


void Window::set_content_size(const Value2D<Real> &size)
	{
	Rectangle<Real> screen_frame = NATIVE_WINDOW.screen.visibleFrame;
	Rectangle<Real> window_frame = NATIVE_WINDOW.frame;
	auto window_top_center = window_frame.top_center();
	auto window_border = window_frame.size - ((NSView *)NATIVE_WINDOW.contentView).bounds.size;

	if (screen_frame.size < (window_border + size))
		{
		window_frame.size = window_border + size.fit(screen_frame.size - window_border);
		if (window_frame.size.y == screen_frame.size.y) window_frame.size.x = floor(window_frame.size.x);
		else window_frame.size.y = floor(window_frame.size.y);
		}

	else window_frame.size = window_border + size;

	window_frame.point.x = (window_top_center.x - window_frame.size.x / 2.0);

	window_frame.point.y = window_top_center.y - window_frame.size.y < screen_frame.point.y
		? screen_frame.point.y
		: window_top_center.y - window_frame.size.y;

	[NATIVE_WINDOW setFrame: window_frame display: YES];
	}


Value2D<Real> Window::content_aspect_ratio() const
	{return NATIVE_WINDOW.contentAspectRatio;}


void Window::set_content_aspect_ratio(const Value2D<Real> &aspect_ratio)
	{NATIVE_WINDOW.contentAspectRatio = aspect_ratio;}


String Window::title() const
	{return NATIVE_WINDOW.title.UTF8String;}


void Window::set_title(const String &title)
	{NATIVE_WINDOW.title = @(title.c_str());}


Zeta::Boolean Window::full_screen() const
	{return ((NATIVE_WINDOW.styleMask & NSFullScreenWindowMask) == NSFullScreenWindowMask);}


void Window::set_full_screen(Zeta::Boolean value)
	{
	}


Zeta::Boolean Window::is_focused  () {return NATIVE_WINDOW.isKeyWindow;}
Zeta::Boolean Window::is_maximized() {return NATIVE_WINDOW.isZoomed;}
Zeta::Boolean Window::is_minimized() {return NATIVE_WINDOW.isMiniaturized;}
Zeta::Boolean Window::is_visible  () {return NATIVE_WINDOW.isVisible;}


// Cocoa/Window.mm EOF
