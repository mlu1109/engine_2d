#include <algorithm>
#include "Seg.hpp"
#include <cfloat>

namespace eng
{
	Seg::Seg(const Vec &a, const Vec &b) :
			Line(a, b)
	{

	}

	const Vec &Seg::a() const
	{
		return a_;
	}

	const Vec &Seg::b() const
	{
		return b_;
	}

	double Seg::length() const
	{
		return std::sqrt(
				std::pow(a_.x() - b_.x(), 2) +
				std::pow(a_.y() - b_.y(), 2)
		);
	}

	Seg Seg::project(const Vec &on) const
	{
		return Seg(a_.project(on), b_.project(on));
	}


	// Assumes that segments are collinear
	bool Seg::overlapping(const Seg &s) const
	{
		if (a().x() != b().x())
		{
			const Vec& a = a_.x() < b_.x() ? a_ : b_;
			const Vec& b = a == a_ ? b_ : a_;
			const Vec& c = s.a().x() < s.b().x() ? s.a() : s.b();
			const Vec& d = c == s.a() ? s.b() : s.a();
			if ((a.x() < c.x() && c.x() < b.x()) || (c.x() < a.x() && a.x() < d.x()))
				return true;
		}
		else
		{
			const Vec& a = a_.y() < b_.y() ? a_ : b_;
			const Vec& b = a == a_ ? b_ : a_;
			const Vec& c = s.a().y() < s.b().y() ? s.a() : s.b();
			const Vec& d = c == s.a() ? s.b() : s.a();
			if ((a.y() < c.y() && c.y() < b.y()) || (c.y() < a.y() && a.y() < d.y()))
				return true;
		}

		return false;
	}

	bool Seg::origin() const
	{
		return a_.origin() && b_.origin();
	}

	// Assumes that segments are collinear, if no overlap is found an "empty" segment is returned
	Seg Seg::overlap(const Seg &s) const
	{
		if (a().x() != b().x())
		{
			const Vec& a = a_.x() < b_.x() ? a_ : b_;
			const Vec& b = a == a_ ? b_ : a_;
			const Vec& c = s.a().x() < s.b().x() ? s.a() : s.b();
			const Vec& d = c == s.a() ? s.b() : s.a();
			if ((a.x() < c.x() && c.x() < b.x()))
				return Seg(c, b);
			else if (c.x() < a.x() && a.x() < d.x())
				return Seg(a, d);
		}
		else
		{
			const Vec& a = a_.y() < b_.y() ? a_ : b_;
			const Vec& b = a == a_ ? b_ : a_;
			const Vec& c = s.a().y() < s.b().y() ? s.a() : s.b();
			const Vec& d = c == s.a() ? s.b() : s.a();
			if ((a.y() < c.y() && c.y() < b.y()))
				return Seg(c, b);
			else if (c.y() < a.y() && a.y() < d.y())
				return Seg(a, d);
		}

		return Seg(Vec(0, 0), Vec(0, 0));
	}

	Vec Seg::vector() const
	{
		return Vec(b_ - a_);
	}

	void Seg::operator+=(const Vec &rhs)
	{
		a_ += rhs;
		b_ += rhs;
	}

	bool operator==(const Seg &lhs, const Seg &rhs)
	{
		return lhs.a_ == rhs.a_ && lhs.b_ == rhs.b_;
	}

	bool operator!=(const Seg &lhs, const Seg &rhs)
	{
		return !(lhs == rhs);
	}

	bool Seg::operator<(const Seg &rhs) const
	{
		return length() < rhs.length();
	}

	Seg operator+(const Seg &lhs, const Vec &rhs)
	{
		return Seg(lhs.a_ + rhs, lhs.b_ + rhs);
	}

	std::ostream &operator<<(std::ostream &os, const Seg &s)
	{
		os << "Seg(" << s.a_ << ", " << s.b_ << ")";
		return os;
	}

	Seg Seg::longestSeg()
	{
		return Seg(Vec(DBL_MIN, DBL_MIN), Vec(DBL_MAX, DBL_MAX));
	}
}
