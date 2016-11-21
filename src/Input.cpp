#include "Input.hpp"
#include "Consts.hpp"

namespace eng
{

	bool Input::running() const
	{
		return running_;
	}

	Vec Input::mouseScreenPos()
	{
		int screen_x, screen_y;
		SDL_GetMouseState(&screen_x, &screen_y);
		return Vec(screen_x, screen_y);
	}

	void Input::mouseSetControlled(PhysicsObject *&controlled, World &world, Render &render)
	{
		Vec m_pos = mouseScreenPos();
		render.convertScreenToWorldCoords(m_pos);
		PhysicsObject *clicked = world.getObjectAtPos(m_pos);

		if (clicked != nullptr)
			controlled = clicked;
	}

	void Input::mouseMoveShape(const SDL_Event &event, PhysicsObject *&controlled, World &world, Render &render)
	{
		Vec m_pos = mouseScreenPos();
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

	void Input::mouseCameraMove(const SDL_Event &event, Render &render)
	{
		render.addCamPosRelZoom(Vec(-event.motion.xrel, -event.motion.yrel));
	}

	void Input::mouseCameraZoom(const SDL_Event &event, Render &render)
	{
		render.addZoomRelPos(event.wheel.y < 0 ? consts::SCROLL_RATE : -consts::SCROLL_RATE, mouseScreenPos());
	}

	void Input::handleKeyEvent(const SDL_Event &event, PhysicsObject *&controlled)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.scancode)
			{
				case SDL_SCANCODE_UP:
				case SDL_SCANCODE_W:
					controlled->addVel(consts::UP_VEL_MOD);
					break;
				case SDL_SCANCODE_LEFT:
				case SDL_SCANCODE_A:
					controlled->addVel(consts::LEFT_VEL_MOD);
					break;
				case SDL_SCANCODE_DOWN:
				case SDL_SCANCODE_S:
					controlled->addVel(consts::DOWN_VEL_MOD);
					break;
				case SDL_SCANCODE_RIGHT:
				case SDL_SCANCODE_D:
					controlled->addVel(consts::RIGHT_VEL_MOD);
					break;
				case SDL_SCANCODE_Q:
					controlled->addAngVel(-consts::ANG_VEC_MOD);
					break;
				case SDL_SCANCODE_E:
					controlled->addAngVel(consts::ANG_VEC_MOD);
					break;
				case SDL_SCANCODE_SPACE:
					controlled->immediateStop();
					break;
				case SDL_SCANCODE_ESCAPE:
					running_ = false;
					break;
				default:
					break;
			}
		}
	}

	void Input::handleMouseEvent(const SDL_Event &event, PhysicsObject *&controlled, World &world, Render &render)
	{
		switch (event.type)
		{
			case SDL_MOUSEWHEEL:
				mouseCameraZoom(event, render);
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.state == SDL_BUTTON_RMASK)
					mouseCameraMove(event, render);
				else if (event.motion.state == SDL_BUTTON_LMASK)
					mouseMoveShape(event, controlled, world, render);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.state == SDL_BUTTON_LMASK)
					mouseSetControlled(controlled, world, render);
				break;
			default:
				break;
		}
	}

	void Input::handleEvents(World &world, PhysicsObject *&controlled, Render &render)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					running_ = false;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					handleKeyEvent(event, controlled);
					break;
				case SDL_MOUSEWHEEL:
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONDOWN:
					handleMouseEvent(event, controlled, world, render);
					break;
				default:
					break;
			}
		}
	}
}