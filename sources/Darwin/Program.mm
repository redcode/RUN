/* RUN - Darwin/Program.mm
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

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

	for (UInt i = sizeof(name_keys) / sizeof(NSString *); i;) if (
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
