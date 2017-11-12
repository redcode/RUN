/* RUN - Cocoa/Window.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#define Z_USE_NS_GEOMETRY

#include <RUN/Window.hpp>
#include <RUN/Program.hpp>
#include <Cocoa/Cocoa.h>
#include <Z/classes/mathematics/geometry/euclidean/Rectangle.hpp>

#define WINDOW	     ((_RUNNativeWindow *)native_context)
#define WINDOW_STYLE NSClosableWindowMask | NSMiniaturizableWindowMask | NSTitledWindowMask

using namespace RUN;


@interface _RUNNativeWindow : NSWindow <NSWindowDelegate> {
	@public
	Window *window;
} @end


@implementation _RUNNativeWindow
	- (BOOL) canBecomeKeyWindow {return YES;};


	- (void) windowDidBecomeKey:(id) _ {}
	- (void) windowDidResignKey:(id) _ {}
	- (void) windowDidResize: (id) _ {}
	- (void) windowDidMove: (id) _ {}
	- (void) windowDidMiniaturize:(id) _ {}
	- (void) windowDidDeminiaturize:(id) _ {}
	- (BOOL) windowShouldClose: (id) _ {return YES;}
@end



static NSScreen *suitable_screen_for_size(NSScreen *current_screen, const Value2D<Real> &size)
	{
	Rectangle<Real> screen_frame = current_screen.visibleFrame;

	if (!screen_frame.size.contains(size)) for (NSScreen *screen in NSScreen.screens)
		if (size <= screen.visibleFrame.size) return screen;

	return current_screen;
	}


Window::Window(const Value2D<Real> &size, Mode mode)
	{
	native_context = [[_RUNNativeWindow alloc]
		initWithContentRect: size
		styleMask:	     (mode & Mode::RESIZABLE) ? WINDOW_STYLE | NSResizableWindowMask : WINDOW_STYLE
		backing:	     NSBackingStoreBuffered
		defer:		     NO];

	WINDOW.title		       = @(Program::singleton->name().c_str());
	WINDOW.restorable	       = NO;
	WINDOW.acceptsMouseMovedEvents = YES;
	WINDOW->window		       = this;

	Value2D<Real> window_size = WINDOW.frame.size;
	Rectangle<Real> screen_frame = suitable_screen_for_size(NSScreen.mainScreen, window_size).visibleFrame;

	if (!screen_frame.size.contains(window_size))
		{
		auto window_border = window_size - ((NSView *)WINDOW.contentView).bounds.size;

		window_size = window_border + (window_size - window_border).fit(screen_frame.size - window_border);
		if (window_size.y == screen_frame.size.y) window_size.x = floor(window_size.x);
		else window_size.y = floor(window_size.y);
		}

	[WINDOW setFrame: Rectangle<Real>
			(screen_frame.point.x + round(screen_frame.size.x - window_size.x) / 2.0,
			 screen_frame.point.y + floor((screen_frame.size.y - window_size.y) * 2.0 / 3.0),
			 window_size)
		display: YES];

	world = new World();
	world->create_view([WINDOW.contentView frame].size);
	NSView *view = (NSView *)world->native_context;

	//view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
	//[WINDOW.contentView addSubview: view];

	WINDOW.contentView = view;
	[WINDOW makeFirstResponder: view];
	//[WINDOW.contentView addSubview: system_view];
	if (mode & Mode::PRESERVE_ASPECT_RATIO) WINDOW.contentAspectRatio = size;
	WINDOW.delegate = WINDOW;
	[WINDOW makeKeyAndOrderFront: nil];
	}


Window::~Window()
	{
	[WINDOW performClose: nil];
	WINDOW.delegate = nil;
	[WINDOW release];
	}


Value2D<Real> Window::content_size() const
	{return WINDOW.frame.size;}


void Window::set_content_size(const Value2D<Real> &size)
	{
	Rectangle<Real> screen_frame = WINDOW.screen.visibleFrame;
	Rectangle<Real> window_frame = WINDOW.frame;
	auto window_top_center = window_frame.top_center();
	auto window_border = window_frame.size - ((NSView *)WINDOW.contentView).bounds.size;

	if (!screen_frame.size.contains(window_border + size))
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

	[WINDOW setFrame: window_frame display: YES];
	}


Value2D<Real> Window::content_aspect_ratio() const
	{return WINDOW.contentAspectRatio;}


void Window::set_content_aspect_ratio(const Value2D<Real> &aspect_ratio)
	{WINDOW.contentAspectRatio = aspect_ratio;}


String Window::title() const
	{return WINDOW.title.UTF8String;}


void Window::set_title(const String &title)
	{WINDOW.title = @(title.c_str());}


Boolean Window::full_screen() const
	{return ((WINDOW.styleMask & NSFullScreenWindowMask) == NSFullScreenWindowMask);}


void Window::set_full_screen(Boolean value)
	{
	}


Boolean Window::is_focused  () {return WINDOW.isKeyWindow;}
Boolean Window::is_maximized() {return WINDOW.isZoomed;}
Boolean Window::is_minimized() {return WINDOW.isMiniaturized;}
Boolean Window::is_visible  () {return WINDOW.isVisible;}


// Cocoa/Window.mm EOF
