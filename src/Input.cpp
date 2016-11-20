#include "Input.h"
#include "Render.hpp"

namespace eng
{

	bool Input::running() const
	{
		return running_;
	}

	void Input::handleKeyEvent(const SDL_Event &event, PhysicsObject *&controlled)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.scancode)
			{
				case SDL_SCANCODE_UP:
				case SDL_SCANCODE_W:
					controlled->addVel(Vec(0, -10));
					break;
				case SDL_SCANCODE_LEFT:
				case SDL_SCANCODE_A:
					controlled->addVel(Vec(-10, 0));
					break;
				case SDL_SCANCODE_DOWN:
				case SDL_SCANCODE_S:
					controlled->addVel(Vec(0, 10));
					break;
				case SDL_SCANCODE_RIGHT:
				case SDL_SCANCODE_D:
					controlled->addVel(Vec(10, 0));
					break;
				case SDL_SCANCODE_Q:
					controlled->addAngVel(-0.3);
					break;
				case SDL_SCANCODE_E:
					controlled->addAngVel(0.3);
					break;
				case SDL_SCANCODE_SPACE:
					controlled->immediateStop();
					break;
				default:
					break;
			}
		}
	}

	void Input::handleEvents(World &world, PhysicsObject *&controlled, Render &render)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				running_ = false;
			else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
				handleKeyEvent(event, controlled);
			else if (event.type == SDL_MOUSEWHEEL)
			{
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				render.addZoomRelPos(event.wheel.y < 0 ? 0.05 : -0.05, Vec(mouse_x, mouse_y));
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				if (event.motion.state == SDL_BUTTON_RMASK)
					render.addCamPosRelZoom(Vec(-event.motion.xrel, -event.motion.yrel));
				else if (event.motion.state == SDL_BUTTON_LMASK)
				{
					Vec m_pos(event.motion.x, event.motion.y);
					render.convertScreenToWorldCoords(m_pos);
					PhysicsObject *clicked = world.getObjectAtPos(m_pos);
					if (clicked != nullptr)
					{
						Vec rel_motion(event.motion.xrel, event.motion.yrel);
						render.convertScreenCoordsRelZoom(rel_motion);
						clicked->addPos(rel_motion);
						controlled = clicked;
						controlled->immediateStop();
					}
				}
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_BUTTON_LMASK)
			{
				Vec m_pos(event.motion.x, event.motion.y);
				render.convertScreenToWorldCoords(m_pos);
				PhysicsObject *clicked = world.getObjectAtPos(m_pos);
				if (clicked != nullptr)
					controlled = clicked;
			}
		}
	}
}