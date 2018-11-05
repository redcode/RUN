/* RUN - UIKit/View.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#define Z_USE_CG_GEOMETRY

#import "_RUNView.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#define VIEW ((_RUNGLView *)view)

using namespace RUN;


@implementation _RUNView


	- (BOOL) canBecomeFirstResponder {return YES;}


	- (void) touchesBegan: (NSSet	*) touches
		 withEvent:    (UIEvent *) event
		{
		NSLog(@"touchesBegan");
		view->touches_down();
		}


	- (void) touchesMoved: (NSSet	*) touches
		 withEvent:    (UIEvent *) event
		{
		NSLog(@"touchesBegan");
		view->touches_moved();
		}


	- (void) touchesEnded: (NSSet	*) touches
		 withEvent:    (UIEvent *) event
		{
		NSLog(@"touchesEnded");
		view->touches_up();
		}


	- (void) touchesCancelled: (NSSet   *) touches
		 withEvent:	   (UIEvent *) event
		{
		NSLog(@"touchesCancelled");
		view->touches_cancelled();
		}


	/*- (void) drawRect:(CGRect)rect
		{
		[[UIColor blueColor] setFill];
		UIBezierPath *path = [UIBezierPath bezierPathWithOvalInRect: self.bounds];
		[path fill];
		}*/

@end


@interface _RUNGLView : _RUNView {
	CAEAGLLayer* _eagl_layer;
	EAGLContext* _gl_context;
	GLuint	     _render_buffer;
}
@end


@implementation _RUNGLView


	+ (Class) layerClass {return [CAEAGLLayer class];}


	- (id) initWithFrame: (CGRect) frame
		{
		if ((self = [super initWithFrame: frame]))
			{
			(_eagl_layer = (CAEAGLLayer *) self.layer).opaque = YES;

			_eagl_layer.drawableProperties = @{
				kEAGLDrawablePropertyRetainedBacking: @(NO),
				kEAGLDrawablePropertyColorFormat:     kEAGLColorFormatRGBA8
			};

			if (!(_gl_context = [[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES2]))
				{
				NSLog(@"Failed to initialize OpenGLES 2.0 context");
				exit(1);
				}

			if (![EAGLContext setCurrentContext: _gl_context])
				{
				NSLog(@"Failed to set current OpenGL context");
				exit(1);
				}

			glGenRenderbuffers(1, &_render_buffer);
			glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer);
			[_gl_context renderbufferStorage: GL_RENDERBUFFER fromDrawable: _eagl_layer];

			GLuint framebuffer;
			glGenFramebuffers(1, &framebuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _render_buffer);

			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			[_gl_context presentRenderbuffer: GL_RENDERBUFFER];

			[EAGLContext setCurrentContext: nil];
			}

		return self;
		}


	- (void) dealloc
		{
		[_gl_context release];
		[super dealloc];
		}


	/*- (void) drawRect: (CGRect) rect
		{
		NSLog(@"drawRect:");
		[EAGLContext setCurrentContext: _gl_context];
		glClearColor(1.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		[_gl_context presentRenderbuffer: GL_RENDERBUFFER];
		[EAGLContext setCurrentContext: nil];
		}*/


@end


void View::create_view(const Value2D<Real> &size, Backend backend)
	{
	view = [[_RUNGLView alloc] initWithFrame: size];
	VIEW->view = this;
	}


void View::destroy_view()
	{
	[VIEW release];
	view = NULL;
	}


// UIKit/View.mm
