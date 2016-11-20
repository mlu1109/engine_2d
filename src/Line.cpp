#include "Line.hpp"

namespace eng
{
	Line::Line(const Vec &a, const Vec &b) :
			a_(a), b_(b)
	{

	}

	Vec Line::from() const
	{
		if (horizontal())
			return a_.x() < b_.x() ? a_ : b_;
		else
			return a_.y() < b_.y() ? a_ : b_;
	}

	Vec Line::to() const
	{
		if (horizontal())
			return a_.x() < b_.x() ? b_ : a_;
		else
			return a_.y() < b_.y() ? b_ : a_;
	}

	Vec Line::vector() const
	{
		return Vec(b_ - a_);
	}

	bool Line::horizontal() const
	{
		return a_.y() == b_.y();
	}

	bool Line::vertical() const
	{
		return a_.x() == b_.x();
	}

	void Line::rotate(double rad)
	{
		a_.rotate(rad);
		b_.rotate(rad);
	}
}