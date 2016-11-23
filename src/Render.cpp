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

		if (!gWindow_)
			std::cout << "Could not create window: " << SDL_GetError() << '\n';

		gRenderer_ = SDL_CreateRenderer(gWindow_, -1, SDL_RENDERER_ACCELERATED);

		if (!gRenderer_)
			std::cout << "Could not create renderer: " << SDL_GetError() << '\n';
	}

	Render::~Render()
	{
		SDL_DestroyRenderer(gRenderer_);
		SDL_DestroyWindow(gWindow_);
		gWindow_ = nullptr;
		gRenderer_ = nullptr;
		SDL_Quit();
	}

	void Render::cameraZoomRelPos(double f, const Vec &m_pos)
	{
		auto before = camera.pos + m_pos / camera.zoom;
		camera.zoom += f * camera.zoom;
		auto after = camera.pos + m_pos / camera.zoom;
		camera.pos += before - after;
	}

	void Render::cameraMoveRelZoom(const Vec &pos)
	{
		camera.pos += pos / camera.zoom;
	}

	void Render::transformWorldToCamPos(Vec &v)
	{
		v -= camera.pos;
		v *= camera.zoom;
	}

	void Render::transformScreenToWorldPos(Vec &v)
	{
		v /= camera.zoom;
		v += camera.pos;
	}

	void Render::transformScreenPosRelZoom(Vec &v)
	{
		v /= camera.zoom;
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

	void Render::paintPoint(Vec p)
	{
		transformWorldToCamPos(p);
		int width = 4;
		int height = 4;
		SDL_Rect point = {(int) (p.x() - width / 2), (int) (p.y() - height / 2),
						  width / 2, height / 2};
		SDL_RenderFillRect(gRenderer_, &point);
	}

	void Render::paintSeg(Vec o, Vec v)
	{
		transformWorldToCamPos(o);
		transformWorldToCamPos(v);
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
		setColor(0xFFFFFF00);
		paintObject(o);
		setColor(0x33333300);
		paintBox(o.poly().min() + o.pos(), o.poly().max() + o.pos());
	}

	void Render::paintBox(Vec min, Vec max)
	{
		transformWorldToCamPos(min);
		transformWorldToCamPos(max);
		int x = (int) min.x();
		int y = (int) min.y();
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
		setColor(0xFFFFFF00);
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
			paintSeg(a.pos(), a.pos() + c.mtv());
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

		setColor(0xFF69B400);
		for (const auto &v : c.pois())
		{
			paintPoint(v);
		}
	}

	void Render::paintGrid()
	{
		int screen_w, screen_h;
		SDL_GetWindowSize(gWindow_, &screen_w, &screen_h);
		screen_w /= camera.zoom;
		screen_h /= camera.zoom;
		// Paint grid
		setColor(0x11111100);
		int x_dist = 50, y_dist = 50;
		if (camera.zoom < 0.08)
			SDL_RenderClear(gRenderer_);
		else
		{
			for (auto r = 0; r < screen_h / y_dist; ++r)
			{
				paintSeg(Seg(camera.pos.x(),
							 camera.pos.y() + y_dist * r,
							 camera.pos.x() + screen_w,
							 camera.pos.y() + y_dist * r)
				);
				for (auto c = 0; c < screen_w / x_dist; ++c)
					paintSeg(Seg(camera.pos.x() + x_dist * c,
								 camera.pos.y(),
								 camera.pos.x() + x_dist * c,
								 camera.pos.y() + screen_h)
					);
			}
		}
		// Paint axes
		setColor(0x88888800);
		paintSeg(Seg(camera.pos.x(), 0, camera.pos.x() + screen_w, 0));
		paintSeg(Seg(0, camera.pos.y(), 0, camera.pos.y() + screen_h));
	}
}

