/* RUN - Cocoa/World.mm
  ______ __ ______  ___
 /   - //  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#define Z_USE_NS_GEOMETRY

#import <RUN/World.hpp>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>
#import <Z/types/base.h>
#import <Z/classes/base/Status.hpp>
#import <Z/classes/mathematics/geometry/euclidean/Rectangle.hpp>

#define VIEW ((_RUNGLView *)native_context)

using namespace RUN;

#define _(CODE) Keyboard::Key::CODE

static UInt8 const keymap[128] = {
	_(ANSI_A	   ), _(ANSI_S			     ), _(ANSI_D		   ), _(ANSI_F		    ),
	_(ANSI_H	   ), _(ANSI_G			     ), _(ANSI_Z		   ), _(ANSI_X		    ),
	_(ANSI_C	   ), _(ANSI_V			     ), _(ISO_SECTION		   ), _(ANSI_B		    ),
	_(ANSI_Q	   ), _(ANSI_W			     ), _(ANSI_E		   ), _(ANSI_R		    ),
	_(ANSI_Y	   ), _(ANSI_T			     ), _(ANSI_1		   ), _(ANSI_2		    ),
	_(ANSI_3	   ), _(ANSI_4			     ), _(ANSI_6		   ), _(ANSI_5		    ),
	_(ANSI_EQUALS_SIGN ), _(ANSI_9			     ), _(ANSI_7		   ), _(ANSI_HYPHEN_MINUS   ),
	_(ANSI_8	   ), _(ANSI_0			     ), _(ANSI_RIGHT_SQUARE_BRACKET), _(ANSI_O		    ),
	_(ANSI_U	   ), _(ANSI_LEFT_SQUARE_BRACKET     ), _(ANSI_I		   ), _(ANSI_P		    ),
	_(RETURN	   ), _(ANSI_L			     ), _(ANSI_J		   ), _(ANSI_APOSTROPHE	    ),
	_(ANSI_K	   ), _(ANSI_SEMICOLON		     ), _(ANSI_REVERSE_SOLIDUS	   ), _(ANSI_COMMA	    ),
	_(ANSI_SOLIDUS	   ), _(ANSI_N			     ), _(ANSI_M		   ), _(ANSI_FULL_STOP	    ),
	_(TAB		   ), _(SPACE			     ), _(ANSI_GRAVE_ACCENT	   ), _(BACKSPACE	    ),
	_(INVALID	   ), _(ESCAPE			     ), _(RIGHT_COMMAND		   ), _(LEFT_COMMAND	    ),
	_(LEFT_SHIFT	   ), _(CAPS_LOCK		     ), _(LEFT_OPTION		   ), _(LEFT_CONTROL	    ),
	_(RIGHT_SHIFT	   ), _(RIGHT_OPTION		     ), _(RIGHT_CONTROL		   ), _(FUNCTION	    ),
	_(APPLE_F17	   ), _(ANSI_KEYPAD_DECIMAL_SEPARATOR), _(INVALID		   ), _(ANSI_KEYPAD_ASTERISK),
	_(INVALID	   ), _(ANSI_KEYPAD_PLUS_SIGN	     ), _(INVALID		   ), _(ANSI_KEYPAD_NUM_LOCK),
	_(INVALID	   ), _(INVALID			     ), _(INVALID		   ), _(ANSI_KEYPAD_SOLIDUS ),
	_(ANSI_KEYPAD_ENTER), _(INVALID			     ), _(ANSI_KEYPAD_HYPHEN_MINUS ), _(APPLE_F18	    ),
	_(APPLE_F19	   ), _(APPLE_ANSI_KEYPAD_EQUALS_SIGN), _(ANSI_KEYPAD_0		   ), _(ANSI_KEYPAD_1	    ),
	_(ANSI_KEYPAD_2	   ), _(ANSI_KEYPAD_3		     ), _(ANSI_KEYPAD_4		   ), _(ANSI_KEYPAD_5	    ),
	_(ANSI_KEYPAD_6	   ), _(ANSI_KEYPAD_7		     ), _(APPLE_F20		   ), _(ANSI_KEYPAD_8	    ),
	_(ANSI_KEYPAD_9	   ), _(JIS_YEN_SIGN		     ), _(JIS_LOW_LINE		   ), _(JIS_KEYPAD_COMMA    ),
	_(F5		   ), _(F6			     ), _(F7			   ), _(F3		    ),
	_(F8		   ), _(F9			     ), _(JIS_EISU		   ), _(F11		    ),
	_(JIS_KANA	   ), _(PRINT_SCREEN		     ), _(APPLE_F16		   ), _(SCROLL_LOCK	    ),
	_(INVALID	   ), _(F10			     ), _(APPLICATION		   ), _(F12		    ),
	_(INVALID	   ), _(PAUSE			     ), _(INSERT		   ), _(HOME		    ),
	_(PAGE_UP	   ), _(DELETE			     ), _(F4			   ), _(END		    ),
	_(F2		   ), _(PAGE_DOWN		     ), _(F1			   ), _(LEFT		    ),
	_(RIGHT		   ), _(DOWN			     ), _(UP			   ), _(INVALID		    )
};


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


	- (void) setFrameSize: (Value2D<Real>) size
		{
		super.frameSize = size;
		world->size = size * _ppp;
		world->update_geometry();
		}


	- (void) setFrame: (Rectangle<Real>) frame
		{
		Value2D<Real> old_size = self.frame.size;
		super.frame = frame;

		if (old_size != (frame.size *= _ppp))
			{
			world->size = frame.size;
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


	- (void) keyDown: (NSEvent *) event
		{
		if (!event.isARepeat)
			{
			Keyboard::Key key(keymap[event.keyCode & 0x7F]);

			if (key.is_valid()) world->keyboard_down(key);
			}
		}


	- (void) keyUp: (NSEvent *) event
		{
		if (!event.isARepeat)
			{
			Keyboard::Key key(keymap[event.keyCode & 0x7F]);

			if (key.is_valid()) world->keyboard_up(key);
			}
		}


	- (void) flagsChanged: (NSEvent *) event
		{
		UInt32 keys = UInt32(event.modifierFlags);
		UInt32 changed = _modifier_keys ^ keys;

		enum {	CAPS_LOCK     = 0x010000,
			/*SHIFT	      = 0x020000,
			CONTROL	      = 0x040000,
			OPTION	      = 0x080000,
			COMMAND	      = 0x100000,*/
			LEFT_SHIFT    = 0x000002,
			RIGHT_SHIFT   = 0x000004,
			LEFT_CONTROL  = 0x000001,
			RIGHT_CONTROL = 0x002000,
			LEFT_OPTION   = 0x000020,
			RIGHT_OPTION  = 0x000040,
			LEFT_COMMAND  = 0x000008,
			RIGHT_COMMAND = 0x000010
		};

#		define HANDLE_KEY(KEY) if (changed & KEY)			  \
			{							  \
			if (keys & KEY) world->keyboard_down(Keyboard::Key::KEY); \
			else		world->keyboard_up  (Keyboard::Key::KEY); \
			}

		HANDLE_KEY(CAPS_LOCK	)
		HANDLE_KEY(LEFT_SHIFT	)
		HANDLE_KEY(LEFT_CONTROL	)
		HANDLE_KEY(LEFT_OPTION	)
		HANDLE_KEY(LEFT_COMMAND	)
		HANDLE_KEY(RIGHT_SHIFT	)
		HANDLE_KEY(RIGHT_CONTROL)
		HANDLE_KEY(RIGHT_OPTION	)
		HANDLE_KEY(RIGHT_COMMAND)

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
