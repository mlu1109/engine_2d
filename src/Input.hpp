#ifndef ENGINE2D_INPUT_H
#define ENGINE2D_INPUT_H

#include <SDL2/SDL.h>
#include "World.hpp"
#include "Render.hpp"

namespace eng
{
	class Input
	{
		Vec mouseScreenPos();
		void mouseSetControlled(PhysicsObject *&controlled, World &world, Render &render);
		void mouseMoveShape(const SDL_Event &event, PhysicsObject *&controlled, World &world, Render &render);
		void mouseCameraZoom(const SDL_Event &event, Render &render);
		void mouseCameraMove(const SDL_Event &event, Render &render);
		void handleKeyEvent(const SDL_Event &event, PhysicsObject *&controlled);
		void handleMouseEvent(const SDL_Event &event, PhysicsObject *&controlled, World &world, Render &render);
		bool running_ = true;
	public:
		void handleEvents(World &world, PhysicsObject *&controlled, Render &render);
		bool running() const;
	};
}

#endif //ENGINE2D_INPUT_H