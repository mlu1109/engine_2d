#include "Input.hpp"
#include "Consts.hpp"

namespace eng
{

	bool Input::running() const
	{
		return running_;
	}

	const PhysicsObject *Input::controlled() const
	{
		return controlled_;
	}

	Vec Input::mouseScreenPos()
	{
		int screen_x, screen_y;
		SDL_GetMouseState(&screen_x, &screen_y);
		return Vec(screen_x, screen_y);
	}

	void Input::mouseSetControlled(World &world, Render &render)
	{
		Vec m_pos = mouseScreenPos();
		render.transformScreenToWorldPos(m_pos);
		PhysicsObject *clicked = world.getObjectAtPos(m_pos);
		controlled_ = clicked;
	}

	void Input::mouseMoveControlled(const SDL_Event &event, World &world, Render &render)
	{
		if (!controlled_)
			return;

		Vec motion(event.motion.xrel, event.motion.yrel);
		render.transformScreenPosRelZoom(motion);
		controlled_->addPos(motion);
		controlled_->immediateStop();
	}

	void Input::mouseCameraMove(const SDL_Event &event, Render &render)
	{
		render.cameraMoveRelZoom(Vec(-event.motion.xrel, -event.motion.yrel));
	}

	void Input::mouseCameraZoom(const SDL_Event &event, Render &render)
	{
		render.cameraZoomRelPos(event.wheel.y < 0 ? consts::SCROLL_RATE : -consts::SCROLL_RATE, mouseScreenPos());
	}

	void Input::keyboardMoveControlled(const SDL_Event &event)
	{
		if (!controlled_)
			return;

		switch (event.key.keysym.scancode)
		{
			case SDL_SCANCODE_UP:
			case SDL_SCANCODE_W:
				controlled_->addVel(consts::UP_VEL_MOD);
				break;
			case SDL_SCANCODE_LEFT:
			case SDL_SCANCODE_A:
				controlled_->addVel(consts::LEFT_VEL_MOD);
				break;
			case SDL_SCANCODE_DOWN:
			case SDL_SCANCODE_S:
				controlled_->addVel(consts::DOWN_VEL_MOD);
				break;
			case SDL_SCANCODE_RIGHT:
			case SDL_SCANCODE_D:
				controlled_->addVel(consts::RIGHT_VEL_MOD);
				break;
			case SDL_SCANCODE_Q:
				controlled_->addAngVel(-consts::ANG_VEC_MOD);
				break;
			case SDL_SCANCODE_E:
				controlled_->addAngVel(consts::ANG_VEC_MOD);
				break;
			case SDL_SCANCODE_SPACE:
				controlled_->immediateStop();
				break;
			default:
				break;
		}
	}

	void Input::handleKeyEvent(const SDL_Event &event)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.scancode)
			{
				case SDL_SCANCODE_UP:
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_LEFT:
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_DOWN:
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_RIGHT:
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_Q:
				case SDL_SCANCODE_E:
				case SDL_SCANCODE_SPACE:
					keyboardMoveControlled(event);
					break;
				case SDL_SCANCODE_ESCAPE:
					running_ = false;
					break;
				default:
					break;
			}
		}
	}

	void Input::handleMouseEvent(const SDL_Event &event, World &world, Render &render)
	{
		switch (event.type)
		{
			case SDL_MOUSEWHEEL:
				mouseCameraZoom(event, render);
				break;
			case SDL_MOUSEMOTION:
				if (event.button.button == SDL_BUTTON_LMASK)
					mouseMoveControlled(event, world, render);
				if (event.button.button == SDL_BUTTON_RMASK)
					mouseCameraMove(event, render);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LMASK)
					mouseSetControlled(world, render);
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			default:
				break;
		}
	}

	void Input::handleEvents(World &world, Render &render)
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
					handleKeyEvent(event);
					break;
				case SDL_MOUSEWHEEL:
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					handleMouseEvent(event, world, render);
					break;
				default:
					break;
			}
		}
	}
}