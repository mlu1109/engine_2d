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

	Vec Seg::min() const
	{
		return std::min(a_, b_);
	}

	Vec Seg::max() const
	{
		return std::max(a_, b_);
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


	// Assumes that segments are parallel
	bool Seg::overlapping(const Seg &s) const
	{
		Seg t_1(min(), s.max());
		Seg t_2(s.min(), max());
		double max_length = s.length() + length();

		if (max_length < t_1.length() || max_length < t_2.length())
			return false;

		return true;
	}

	bool Seg::origin() const
	{
		return a_.origin() && b_.origin();
	}

	// Assumes that segments are parallel
	Seg Seg::overlap(const Seg &s) const
	{
		if (!overlapping(s))
			return Seg(Vec(0, 0), Vec(0, 0));

		Seg o(std::max(s.min(), min()), std::min(s.max(), max()));

		return o;
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
