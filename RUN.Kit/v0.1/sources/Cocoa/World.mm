/* RUN - Cocoa/World.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#define Z_USE_NS_GEOMETRY
#import <RUN/World.hpp>
#import <Z/types/base.h>
#import <Z/classes/base/Status.hpp>
#import <Z/classes/mathematics/geometry/euclidean/Rectangle.hpp>
#import <Z/formats/keymap/Mac OS.h>
#import <Z/formats/keymap/Z.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>

#define VIEW ((_RUNGLView *)native_context)

using namespace RUN;


@interface _RUNView : NSView {
	@public
	World* world;
	UInt32 _modifier_keys;
	Real   _ppp;
};
@end


@implementation _RUNView


	- (void) viewDidChangeBackingProperties
		{
		auto window = self.window;
		_ppp = window ? window.backingScaleFactor : 1.0;
		world->update_geometry();
		}

	- (BOOL) acceptsFirstResponder {return YES;}
	- (BOOL) canBecomeKeyView      {return YES;}
	- (BOOL) isOpaque	       {return YES;}


	- (void) setFrameSize: (NSSize) size
		{
		super.frameSize = size;
		world->size = Value2D<Real>(Real(size.width) * _ppp, Real(size.height) * _ppp);
		world->update_geometry();
		}


	- (void) setFrame: (NSRect) frame
		{
		Value2D<Real> size(Real(frame.size.width) * _ppp, Real(frame.size.height) * _ppp);

		super.frame = frame;

		if (world->size != size)
			{
			world->size = size;
			world->update_geometry();
			}
		}


#	define EVENT_POINT Value2D<Real>([self convertPoint: event.locationInWindow fromView: nil]) * _ppp

	- (void) mouseEntered: (NSEvent *) event {world->mouse_entered(EVENT_POINT);}
	- (void) mouseExited:  (NSEvent *) event {world->mouse_exited (EVENT_POINT);}

	- (void) mouseDown:	 (NSEvent *) event {world->mouse_down(EVENT_POINT, event.buttonNumber);}
	- (void) rightMouseDown: (NSEvent *) event {world->mouse_down(EVENT_POINT, event.buttonNumber);}
	- (void) otherMouseDown: (NSEvent *) event {world->mouse_down(EVENT_POINT, event.buttonNumber);}

	- (void) mouseUp:      (NSEvent *) event {world->mouse_up(EVENT_POINT, event.buttonNumber);}
	- (void) rightMouseUp: (NSEvent *) event {world->mouse_up(EVENT_POINT, event.buttonNumber);}
	- (void) otherMouseUp: (NSEvent *) event {world->mouse_up(EVENT_POINT, event.buttonNumber);}

	- (void) mouseMoved:	    (NSEvent *) event {world->mouse_moved(EVENT_POINT);}
	- (void) mouseDragged:	    (NSEvent *) event {world->mouse_moved(EVENT_POINT);}
	- (void) rightMouseDragged: (NSEvent *) event {world->mouse_moved(EVENT_POINT);}
	- (void) otherMouseDragged: (NSEvent *) event {world->mouse_moved(EVENT_POINT);}

#	undef EVENT_POINT


	static zuint8 const keymap[128] = {Z_ARRAY_CONTENT_MAC_OS_KEY_CODE_TO_Z_KEY_CODE};


	- (void) keyDown: (NSEvent *) event
		{
		if (!event.isARepeat)
			{
			Keyboard::Key key(keymap[event.keyCode & 0x7F]);

			if (key.is_valid()) world->key_down(key);
			}
		}


	- (void) keyUp: (NSEvent *) event
		{
		if (!event.isARepeat)
			{
			Keyboard::Key key(keymap[event.keyCode & 0x7F]);

			if (key.is_valid()) world->key_up(key);
			}
		}


	- (void) flagsChanged: (NSEvent *) event
		{
		UInt32 keys = UInt32(event.modifierFlags);
		UInt32 changed = _modifier_keys ^ keys;

#		define HANDLE_KEY(mask, key)								  \
			if (changed & Z_MAC_OS_KEY_MASK_##mask)						  \
				{									  \
				if (keys & Z_MAC_OS_KEY_MASK_##mask) world->key_down(Keyboard::Key::key); \
				else world->key_up(Keyboard::Key::key);					  \
				}

		HANDLE_KEY(CAPS_LOCK,	  CapsLock    )
		HANDLE_KEY(LEFT_SHIFT,	  LeftShift   )
		HANDLE_KEY(LEFT_CONTROL,  LeftControl )
		HANDLE_KEY(LEFT_OPTION,	  LeftOption  )
		HANDLE_KEY(LEFT_COMMAND,  LeftCommand )
		HANDLE_KEY(RIGHT_SHIFT,	  RightShift  )
		HANDLE_KEY(RIGHT_CONTROL, RightControl)
		HANDLE_KEY(RIGHT_OPTION,  RightOption )
		HANDLE_KEY(RIGHT_COMMAND, RightCommand)

#		undef HANDLE_KEY

		_modifier_keys = keys;
		}


	- (void) scrollWheel: (NSEvent *) event {}


@end


@interface _RUNGLView : _RUNView {
	@public
	NSOpenGLContext*     _gl_context;
	CGLContextObj	     _cgl_context;
	NSOpenGLPixelFormat* _pixel_format;
};
@end


@implementation _RUNGLView


	- (id) initWithFrame: (NSRect) frame
		{
		if ((self = [super initWithFrame: frame]))
			{
			_ppp = 1.0;

			if ([self respondsToSelector: @selector(setWantsBestResolutionOpenGLSurface:)])
				[self setWantsBestResolutionOpenGLSurface: YES];

			NSOpenGLPixelFormatAttribute attributes[] = {
				//NSOpenGLPFAWindow,
				//NSOpenGLPFADoubleBuffer,
				//NSOpenGLProfileVersion3_2Core,
				//NSOpenGLPFADepthSize, 32,
				// Must specify the 3.2 Core Profile to use OpenGL 3.2
				0
			};

			_pixel_format = [[NSOpenGLPixelFormat alloc] initWithAttributes: attributes];
			_gl_context   = [[NSOpenGLContext alloc] initWithFormat: _pixel_format shareContext: nil];

			GLint swap_interval = 1;

			[_gl_context setValues: &swap_interval forParameter: NSOpenGLCPSwapInterval];
			_gl_context.view = self;
			_cgl_context = _gl_context.CGLContextObj;
			}

		return self;
		}


	- (void) dealloc
		{
		[_pixel_format release];
		[_gl_context release];
		[super dealloc];
		}


	- (void) viewDidMoveToWindow
		{
		[super viewDidMoveToWindow];

		auto window = self.window;
		if (!window) [_gl_context clearDrawable];
		else _ppp = window.backingScaleFactor;
		}


	- (void) lockFocus
		{
		[super lockFocus];
		if (_gl_context.view != self) _gl_context.view = self;
		CGLSetCurrentContext(_cgl_context);
		}


	- (void) drawRect: (NSRect) frame
		{
		//NSLog(@"drawRect:");
		CGLSetCurrentContext(_cgl_context);
		//[_GLContext update];
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		}

@end


@interface _RUNMetalView : _RUNView
@end


@implementation _RUNMetalView
@end


void World::create_view(const Value2D<Real> &size, Backend backend)
	{
	native_context = [[_RUNGLView alloc] initWithFrame: size];
	VIEW->world = this;
	}


void World::destroy_view()
	{
	[VIEW release];
	native_context = NULL;
	}


// Cocoa/World.mm EOF
