/* RUN Kit C++ API - namespace.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2017 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_namespace_HPP__
#define __RUN_namespace_HPP__

#define Z_USE_REAL_DOUBLE

#include <Z/types/base.hpp>
#include <Z/macros/language.hpp>
#include <RUN/configuration.hpp>
#include <string>
#include <vector>
#include <functional>

namespace RUN {

	using String = std::string;
	template <class T> using Function = ::std::function<T>;
	template <class T> using Array	  = ::std::vector<T>;

	using namespace Zeta;

	template <class T> struct Matrix4x4 {
		T m[4 * 4];
	};

	template <class T> struct Color;

	class Camera;
	//struct KeyCode;
	struct Keyboard;
	struct Mouse;
	struct Joystick;
	struct Touch;
	class Layer;
	class Node;
	class ParticleSystem;
	class Program;
	class Scene;
	class Screen; // Trait in Nintendo 3DS
	class Texture;
	class TextureFrame;
	class TextureCache;
	class TileMap;
	class Video;
	class Window;
	class World;
};

#endif // __RUN_namespace_HPP__
