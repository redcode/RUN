//
//  test.cpp
//  RUN (macOS)
//
//  Created by Manuel on 17/10/16.
//  Copyright © 2016-2018 Manuel Sainz de Baranda y Goñi.
//

#include <stdio.h>
#include <RUN/Program.hpp>
#include <RUN/Window.hpp>
#include <iostream>

using namespace RUN;


class Test : public Program {
	public:
	Test(int argc, char **argv) : Program(argc, argv) {};

	void will_start() override;
	void did_start() override;
	void will_quit() override;
};


void Test::will_start()
	{
	Window *window = new Window(Value2D<Real>(320.0, 240.0), Window::Resizable | Window::PreserveAspectRatio);
	std::cout << "will_start()\n";

	//window->set_content_aspect_ratio(Value2D<Real>(320.0, 240.0));
	//std::cout << "Test::did_start()\n";
	//std::cout << "Resources path => ";
	//std::cout << resources_path();
	//std::cout << "\nVersion => ";
	//std::cout << version();
	//std::cout << "\n";
	//open_url("http://es.wikipedia.org");
	}


void Test::did_start()
	{
	std::cout << "did_start()\n";
	//this->exit();
	}


void Test::will_quit()
	{
	std::cout << "will_quit()\n";
	}


int main(int argc, char **argv)
	{
	Test(argc, argv).run();
	return 0;
	}
