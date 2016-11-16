#ifndef ENGINE2D_SEG_HPP
#define ENGINE2D_SEG_HPP

#include "Vec.hpp"
#include "Line.hpp"

namespace eng
{
	class Seg : public Line
	{
	public:
		Seg(const Vec &a, const Vec &b);
	};
}

#endif //ENGINE2D_SEG_HPP
