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

	void Render::paintPoint(const Vec &p)
	{
		int width = 4;
		int height = 4;
		SDL_Rect point = {(int) (p.x() - width / 2 - cam_pos_.x()), (int) (p.y() - height / 2 - cam_pos_.y()),
						  width / 2, height / 2};
		SDL_RenderFillRect(gRenderer_, &point);
	}

	void Render::paintSeg(const eng::Vec &o, const Vec &v)
	{
		SDL_RenderDrawLine(gRenderer_, (int) (o.x() - cam_pos_.x()), (int) (o.y() - cam_pos_.y()),
						   (int) (v.x() - cam_pos_.x()), (int) (v.y() - cam_pos_.y()));
	}

	void Render::paintSeg(const Seg &s)
	{
		paintSeg(s.a(), s.b());
	}

	void Render::paintVec(const Vec &v)
	{
		paintSeg(Vec(0, 0), v);
	}

	void Render::paintPoly(const Poly &p, const Vec &o)
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

	void Render::paintObjectWithBB(const PhysicsObject &o)
	{
		setColor(0x00FF0000);
		paintObject(o);
		setColor(0x00770000);
		paintBox(o.poly().min() + o.pos(), o.poly().max() + o.pos());
	}

	void Render::paintBox(const Vec &min, const Vec &max)
	{
		int x = (int) (min.x() - cam_pos_.x());
		int y = (int) (min.y() - cam_pos_.y());
		int w = (int) (max.x() - min.x());
		int h = (int) (max.y() - min.y());
		SDL_Rect box{x, y, w, h};
		SDL_RenderDrawRect(gRenderer_, &box);
	}

	void Render::paintBB(const PhysicsObject &o)
	{
		paintBox(
				o.poly().min() + o.pos(),
				o.poly().max() + o.pos()
		);
	}

	void Render::paintObjects(const std::vector<PhysicsObject> &v)
	{
		for (const auto &o : v)
			paintObject(o);
	}

	void Render::paintObjectsWithBB(const std::vector<PhysicsObject> &v)
	{
		for (const auto &o : v)
			paintObjectWithBB(o);
	}

	void Render::paintDebugCollision(const Collision &c)
	{
		const auto &a = c.a();
		const auto &b = c.b();

		setColor(0xFFFF0000);
		paintBB(a);
		paintBB(b);

		if (c.sat())
		{
			setColor(0xFF000000);
			paintObject(a);
			paintObject(b);
			setColor(0x00FFFF00);
			paintSeg(a.pos(), a.pos() + c.mtv() * 100);
		}

		std::vector<Vec> axes[2];
		axes[0] = a.poly().edgeNormals();
		axes[1] = b.poly().edgeNormals();

		for (int i = 0; i < 2; ++i)
		{
			for (const auto &axis : axes[i])
			{
				setColor(0x77777700);
				Seg a_proj = a.project(axis);
				Seg b_proj = b.project(axis);
				Seg overlap = a_proj.overlap(b_proj);
				paintSeg(a_proj);
				paintSeg(b_proj);
				setColor(0xFF000000);
				paintSeg(overlap);
			}
		}

	}
}

