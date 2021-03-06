/* RUN Kit - UIKit/Window.mm
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

	view = new View();
	view->create_view(size);
	root_view_controller.view = (UIView *)world->view;
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
