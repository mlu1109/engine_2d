#ifndef ENGINE2D_RENDER_HPP
#define ENGINE2D_RENDER_HPP

#include <SDL2/SDL.h>
#include "Vec.hpp"
#include "Poly.hpp"
#include "PhysicsObject.h"
#include "Collision.hpp"

namespace eng
{
	struct Camera
	{
		Vec pos = Vec(-150, -150);
		double zoom = 1;
	};

	class Render
	{
		SDL_Window *gWindow_ = NULL;
		SDL_Renderer *gRenderer_ = NULL;
		uint32_t bg_color = 0x00000000;
		Camera camera;
	public:
		Render();
		~Render();
		void addZoomRelPos(double a, const Vec &m_pos);
		void addCamPosRelZoom(const Vec &pos);
		void setColor(uint32_t rgba);
		void convertWorldToCamCoords(Vec &v);
		void convertScreenToWorldCoords(Vec &v);
		void convertScreenCoordsRelZoom(Vec &v);
		void clear();
		void update();
		void paintPoint(Vec p);
		void paintVec(const Vec &v);
		void paintSeg(Vec f, Vec t);
		void paintSeg(const Seg &s);
		void paintPoly(const Poly &p, const Vec &o);
		void paintObject(const PhysicsObject &o);
		void paintObjectWithBB(const PhysicsObject &o);
		void paintObjects(const std::vector<PhysicsObject> &v);
		void paintObjectsWithBB(const std::vector<PhysicsObject> &v);
		void paintBox(Vec min, Vec max);
		void paintBB(const PhysicsObject &o);
		void paintDebugCollision(const Collision &c);
		void paintGrid();
	};
}

#endif //ENGINE2D_RENDER_HPP
