/* RUN Kit API - Scene.hpp
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

#ifndef _RUN_Scene_HPP_
#define _RUN_Scene_HPP_

#include <RUN/Node.hpp>

class RUN_API RUN::Scene : public Node {

	public:

	struct Transition {
		typedef Function<void(Scene *from, Scene *to)>			  Begin;
		typedef Function<void(Scene *from, Scene *to, Real t)>		  Update;
		typedef Function<void(Scene *from, Scene *to, Boolean cancelled)> End;

		Begin	begin;
		Update	update;
		End	end;
		Real	duration;
		Boolean cancel;

		Z_INLINE Transition(Real duration, Begin begin, Update update, End end)
		: duration(duration), begin(begin), update(update), end(end), cancel(false) {}

		Z_INLINE Transition(Real duration, Update update)
		: Transition(duration, NULL, update, NULL) {}
	};

	//Shared<Scene> next_scene;

	virtual ~Scene();

	virtual void initialize();

	void update(Real t);
};


#endif // _RUN_Scene_HPP_
