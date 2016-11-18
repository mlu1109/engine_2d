#ifndef ENGINE2D_RENDER_HPP
#define ENGINE2D_RENDER_HPP

#include <SDL2/SDL.h>
#include "Vec.hpp"
#include "Poly.hpp"
#include "PhysicsObject.h"

namespace eng
{
	class Render
	{
		SDL_Window *gWindow_ = NULL;
		SDL_Renderer *gRenderer_ = NULL;
		uint32_t bg_color = 0x00000000;
	public:
		Render();
		~Render();
		void setColor(uint32_t rgba);
		void clear();
		void update();
		void paintVec(const Vec &v);
		void paintSeg(const Vec &o, const Vec &v);
		void paintSeg(const Seg &s);
		void paintPoly(const Poly &p, const Vec& o);
		void paintObject(const PhysicsObject &o);
		void paintObjects(const std::vector<PhysicsObject> &v);
		void paintBox(const Vec &min, const Vec &max);
	};
}

#endif //ENGINE2D_RENDER_HPP
