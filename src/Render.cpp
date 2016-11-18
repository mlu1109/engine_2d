#include <iostream>
#include "Render.hpp"

namespace eng
{
	Render::Render()
	{
		if (SDL_Init(SDL_INIT_VIDEO) == 0)
			std::cout << SDL_GetError() << '\n';

		gWindow_ = SDL_CreateWindow(
				"engine_2d",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				800, 600,
				SDL_WINDOW_SHOWN
		);

		if (gWindow_ == nullptr)
			std::cout << "Could not create window: " << SDL_GetError() << '\n';

		gRenderer_ = SDL_CreateRenderer(gWindow_, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer_ == nullptr)
			std::cout << "Could not create renderer: " << SDL_GetError() << '\n';
	}

	Render::~Render()
	{
		SDL_DestroyRenderer(gRenderer_);
		SDL_DestroyWindow(gWindow_);
		gWindow_ = NULL;
		gRenderer_ = NULL;
		SDL_Quit();
	}

	void Render::setColor(uint32_t rgba)
	{
		SDL_SetRenderDrawColor(
				gRenderer_,
				(uint8_t) (rgba >> 24),
				(uint8_t) (rgba >> 16),
				(uint8_t) (rgba >> 8),
				(uint8_t) rgba
		);
	}

	void Render::clear()
	{
		setColor(bg_color);
		SDL_RenderClear(gRenderer_);
	}

	void Render::update()
	{
		SDL_RenderPresent(gRenderer_);
	}

	void Render::paintSeg(const eng::Vec &o, const Vec &v)
	{
		SDL_RenderDrawLine(gRenderer_, (int) o.x(), (int) o.y(), (int) v.x(), (int) v.y());
	}

	void Render::paintSeg(const Seg &s)
	{
		paintSeg(s.a(), s.b());
	}

	void Render::paintVec(const Vec &v)
	{
		paintSeg(Vec(0, 0), v);
	}

	void Render::paintPoly(const Poly &p, const Vec& o)
	{
		const auto &vertices = p.vertices();

		for (auto i = 1; i < vertices.size(); ++i)
			paintSeg(vertices[i - 1] + o, vertices[i] + o);

		paintSeg(vertices.back() + o, vertices.front() + o);
	}

	void Render::paintObject(const PhysicsObject &o)
	{
		paintPoly(o.poly(), o.pos());
	}

	void Render::paintBox(const Vec &min, const Vec &max)
	{
		int x = (int) min.x();
		int y = (int) min.y();
		int w = (int) (max.x() - min.x());
		int h = (int) (max.y() - min.y());
		SDL_Rect box{x, y, w, h};
		SDL_RenderDrawRect(gRenderer_, &box);
	}

	void Render::paintObjects(const std::vector<PhysicsObject> &v)
	{
		for (const auto &o : v)
			paintObject(o);
	}
}

