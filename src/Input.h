#ifndef ENGINE2D_INPUT_H
#define ENGINE2D_INPUT_H

#include <SDL2/SDL.h>
#include "World.hpp"
#include "Render.hpp"

namespace eng
{
	class Input
	{
		void handleKeyEvent(const SDL_Event &event, PhysicsObject *&controlled);
		bool running_ = true;
	public:
		void handleEvents(World &world, PhysicsObject *&controlled, Render &render);
		bool running() const;
	};
}

#endif //ENGINE2D_INPUT_H