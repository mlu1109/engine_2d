#ifndef ENGINE2D_LINE_HPP
#define ENGINE2D_LINE_HPP

#include "Vec.hpp"

namespace eng
{
	class Line
	{
	protected:
		Vec a_;
		Vec b_;
	public:
		Line(const Vec &a, const Vec &b);
		void rotate(double rad);
	};
}

#endif //ENGINE2D_LINE_HPP
