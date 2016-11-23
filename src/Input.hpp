#ifndef ENGINE2D_INPUT_H
#define ENGINE2D_INPUT_H

#include <SDL2/SDL.h>
#include "World.hpp"
#include "Render.hpp"

namespace eng
{
	class Input
	{
		bool running_ = true;
		PhysicsObject *controlled_ = nullptr;
		Vec mouseScreenPos();
		void mouseSetControlled(World &world, Render &render);
		void mouseMoveControlled(const SDL_Event &event, World &world, Render &render);
		void mouseCameraZoom(const SDL_Event &event, Render &render);
		void mouseCameraMove(const SDL_Event &event, Render &render);
		void keyboardMoveControlled(const SDL_Event &event);
		void handleKeyEvent(const SDL_Event &event);
		void handleMouseEvent(const SDL_Event &event, World &world, Render &render);
	public:
		bool running() const;
		const PhysicsObject *controlled() const;
		void handleEvents(World &world, Render &render);
	};
}

#endif //ENGINE2D_INPUT_H