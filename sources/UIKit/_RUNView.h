/* RUN - UIKit/_RUNView.h
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#import <RUN/View.hpp>
#import <UIKit/UIKit.h>

@interface _RUNView : UIView {
	@public
	RUN::View* view;
}
@end
