/* RUN Kit - Darwin/Program.mm
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

#import <RUN/Program.hpp>
#import <Foundation/Foundation.h>

using namespace RUN;
using namespace Zeta;

static NSString *const name_keys[] = {
	@"CFBundleExecutable",
	@"CFBundleName",
	@"CFBundleDisplayName"
};


String Program::name()
	{
	auto bundle = NSBundle.mainBundle;
	NSString *name;
	auto string_class = NSString.class;

	for (UInt i = sizeof(name_keys) / sizeof(name_keys[0]); i;) if (
		(name = [bundle objectForInfoDictionaryKey: name_keys[--i]])
		&& [name isKindOfClass: string_class]
		&& name.length
	)
		return name.UTF8String;

	return NSProcessInfo.processInfo.processName.UTF8String;
	}


String Program::version()
	{
	NSString *version = [NSBundle.mainBundle objectForInfoDictionaryKey: @"CFBundleShortVersionString"];

	return version ? version.UTF8String : "";
	}


String Program::locale_language()
	{return NSLocale.currentLocale.languageCode.UTF8String;}


String Program::resources_path()
	{return NSBundle.mainBundle.resourcePath.UTF8String;}


// Darwin/Program.mm EOF
