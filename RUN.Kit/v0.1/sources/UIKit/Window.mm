/* RUN - UIKit/Window.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright © 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#define Z_USE_CG_GEOMETRY

#include <RUN/Window.hpp>
#include <RUN/Program.hpp>
#include <UIKit/UIKit.h>
#include <Z/classes/mathematics/geometry/euclidean/Rectangle.hpp>

#define WINDOW ((UIWindow *)native_context)

using namespace RUN;


Window::Window(const Value2D<Real> &size, Mode mode)
	{
	native_context = [[UIWindow alloc] initWithFrame: UIScreen.mainScreen.bounds];
	auto root_view_controller = [[UIViewController alloc] init];

	world = new World();
	world->create_view(size);
	root_view_controller.view = (UIView *)world->native_context;
	//WINDOW.backgroundColor = [UIColor greenColor];
	WINDOW.rootViewController = root_view_controller;
	[root_view_controller release];
	[WINDOW makeKeyAndVisible];
	}


Window::~Window()
	{
	[WINDOW release];
	}


Value2D<Real> Window::content_size() const
	{return WINDOW.frame.size;}


// UIKit/Window.mm EOF
