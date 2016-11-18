#include "Input.h"

namespace eng
{

	bool Input::running() const
	{
		return running_;
	}

	void Input::handleKeyEvent(const SDL_Event &event, PhysicsObject &controlled)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.scancode)
			{
				case SDL_SCANCODE_UP:
				case SDL_SCANCODE_W:
					controlled.addVel(Vec(0, -5));
					break;
				case SDL_SCANCODE_LEFT:
				case SDL_SCANCODE_A:
					controlled.addVel(Vec(-5, 0));
					break;
				case SDL_SCANCODE_DOWN:
				case SDL_SCANCODE_S:
					controlled.addVel(Vec(0, 5));
					break;
				case SDL_SCANCODE_RIGHT:
				case SDL_SCANCODE_D:
					controlled.addVel(Vec(5, 0));
					break;
				case SDL_SCANCODE_Q:
					controlled.addAngVel(-0.3);
					break;
				case SDL_SCANCODE_E:
					controlled.addAngVel(0.3);
					break;
				case SDL_SCANCODE_SPACE:
					controlled.immediateStop();
					break;
				default:
					break;
			}
		}
	}

	void Input::handleEvents(World &world, PhysicsObject &controlled)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				running_ = false;
			else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
				handleKeyEvent(event, controlled);
		}
	}
}