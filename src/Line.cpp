#include "Line.hpp"

namespace eng
{
	Line::Line(const Vec &a, const Vec &b) :
			a_(a), b_(b)
	{

	}

	void Line::rotate(double rad)
	{
		a_.rotate(rad);
		b_.rotate(rad);
	}
}