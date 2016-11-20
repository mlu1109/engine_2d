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
		Vec from() const;
		Vec to() const;
		Vec vector() const;
		void rotate(double rad);
		bool horizontal() const;
		bool vertical() const;
	};
}

#endif //ENGINE2D_LINE_HPP
