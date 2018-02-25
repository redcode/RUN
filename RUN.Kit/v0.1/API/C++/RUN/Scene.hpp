/* RUN Kit C++ API - Scene.hpp
  _____  __ ______  ___
 /   - )/  /  /   \/  /
/__/\__/_____/__/\___/ Kit
Copyright (C) 2016-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __RUN_Scene_HPP__
#define __RUN_Scene_HPP__

#include <RUN/Node.hpp>


namespace RUN {class RUN_API Scene : public Node {

	public:

	struct Transition {
		typedef Function<void(Scene *from, Scene *to, Real t)> Update;
		typedef Function<void(Scene *from, Scene *to, Boolean cancelled)> End;

		Update	update;
		End	end;
		Real	duration;
		Boolean cancel;

		Z_INLINE_MEMBER Transition(Real duration, Update update, End end)
		: duration(duration), update(update), end(end), cancel(false) {}

		Z_INLINE_MEMBER Transition(Real duration, Update update)
		: Transition(duration, update, NULL) {}
	};

	virtual ~Scene();

	virtual void initialize();

	void update(Real t);
};}


#endif // __RUN_Scene_HPP__
