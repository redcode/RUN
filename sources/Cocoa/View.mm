/* RUN Kit - Cocoa/View.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
-------------------------------------------------------------------------------
This library is  free software: you can redistribute it  and/or modify it under
the terms  of the GNU  Lesser General Public License  as published by  the Free
Software Foundation, either  version 3 of the License, or  (at your option) any
later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received  a copy of the GNU Lesser General Public License along
with this library. If not, see <http://www.gnu.org/licenses/>.
---------------------------------------------------------------------------- */

#define Z_USE_NS_GEOMETRY
#import <RUN/View.hpp>
#import <Z/classes/base/Status.hpp>
#import <Z/classes/mathematics/geometry/euclidean/Rectangle.hpp>
#import <Z/formats/keymap/Mac OS.h>
#import <Z/formats/keymap/Z.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>

using namespace RUN;

@interface _RUNView : NSView {
	@public
	View*  _owner;
	UInt32 _modifier_keys;
	Real   _ppp;
};
@end


@implementation _RUNView


	- (void) viewDidChangeBackingProperties
		{
		auto window = self.window;
		_ppp = window ? window.backingScaleFactor : 1.0;
		_owner->update_geometry();
		}


	- (BOOL) acceptsFirstResponder {return YES;}
	- (BOOL) canBecomeKeyView      {return YES;}
	- (BOOL) isOpaque	       {return YES;}


	- (void) setFrameSize: (NSSize) size
		{
		super.frameSize = size;
		_owner->size = Value2D<Real>(Real(size.width) * _ppp, Real(size.height) * _ppp);
		_owner->update_geometry();
		}


	- (void) setFrame: (NSRect) frame
		{
		Value2D<Real> size(Real(frame.size.width) * _ppp, Real(frame.size.height) * _ppp);

		super.frame = frame;

		if (_owner->size != size)
			{
			_owner->size = size;
			_owner->update_geometry();
			}
		}


#	define EVENT_POINT Value2D<Real>([self convertPoint: event.locationInWindow fromView: nil]) * _ppp

	- (void) mouseEntered:	    (NSEvent *) event {_owner->mouse_entered(EVENT_POINT);}
	- (void) mouseExited:	    (NSEvent *) event {_owner->mouse_exited (EVENT_POINT);}
	- (void) mouseDown:	    (NSEvent *) event {_owner->mouse_down   (EVENT_POINT, event.buttonNumber);}
	- (void) rightMouseDown:    (NSEvent *) event {_owner->mouse_down   (EVENT_POINT, event.buttonNumber);}
	- (void) otherMouseDown:    (NSEvent *) event {_owner->mouse_down   (EVENT_POINT, event.buttonNumber);}
	- (void) mouseUp:	    (NSEvent *) event {_owner->mouse_up     (EVENT_POINT, event.buttonNumber);}
	- (void) rightMouseUp:	    (NSEvent *) event {_owner->mouse_up     (EVENT_POINT, event.buttonNumber);}
	- (void) otherMouseUp:	    (NSEvent *) event {_owner->mouse_up     (EVENT_POINT, event.buttonNumber);}
	- (void) mouseMoved:	    (NSEvent *) event {_owner->mouse_moved  (EVENT_POINT);}
	- (void) mouseDragged:	    (NSEvent *) event {_owner->mouse_moved  (EVENT_POINT);}
	- (void) rightMouseDragged: (NSEvent *) event {_owner->mouse_moved  (EVENT_POINT);}
	- (void) otherMouseDragged: (NSEvent *) event {_owner->mouse_moved  (EVENT_POINT);}

#	undef EVENT_POINT


	static zuint8 const keymap[128] = {Z_ARRAY_CONTENT_MAC_OS_KEY_CODE_TO_Z_KEY_CODE};


	- (void) keyDown: (NSEvent *) event
		{
		if (!event.isARepeat)
			{
			Keyboard::Key key(keymap[event.keyCode & 0x7F]);

			if (key.is_valid()) _owner->key_down(key);
			}
		}


	- (void) keyUp: (NSEvent *) event
		{
		if (!event.isARepeat)
			{
			Keyboard::Key key(keymap[event.keyCode & 0x7F]);

			if (key.is_valid()) _owner->key_up(key);
			}
		}


	- (void) flagsChanged: (NSEvent *) event
		{
		UInt32 keys = UInt32(event.modifierFlags);
		UInt32 changed = _modifier_keys ^ keys;

#		define HANDLE_KEY(mask, key)								   \
			if (changed & Z_MAC_OS_KEY_MASK_##mask)						   \
				{									   \
				if (keys & Z_MAC_OS_KEY_MASK_##mask) _owner->key_down(Keyboard::Key::key); \
				else _owner->key_up(Keyboard::Key::key);				   \
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


void View::create_native_view(const Value2D<Real> &size, Backend backend)
	{
	((_RUNGLView *)(native = [[_RUNGLView alloc] initWithFrame: size]))->_owner = this;
	}


void View::destroy_view()
	{
	[(_RUNGLView *)native release];
	native = NULL;
	}


// Cocoa/View.mm EOF
