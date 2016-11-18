#include <algorithm>
#include "Seg.hpp"

namespace eng
{
	Seg::Seg(const Vec &a, const Vec &b) :
			Line(a, b)
	{

	}

	const Vec &Seg::a() const
	{
		return Line::a_;
	}

	const Vec &Seg::b() const
	{
		return Line::b_;
	}

	Vec Seg::min() const
	{
		return std::min(Line::a_, Line::b_);
	}

	Vec Seg::max() const
	{
		return std::max(Line::a_, Line::b_);
	}

	double Seg::length() const
	{
		return std::sqrt(
				std::pow(Line::a_.x() - Line::b_.x(), 2) +
				std::pow(Line::a_.y() - Line::b_.y(), 2)
		);
	}

	Seg Seg::project(const Vec &on) const
	{
		return Seg(Line::a_.project(on), Line::b_.project(on));
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

	// Assumes that segments are parallel
	Seg Seg::overlap(const Seg &s) const
	{
		if (!overlapping(s))
			return Seg(Vec(0, 0), Vec(0, 0));

		Seg o(std::max(s.min(), min()), std::min(s.max(), max()));

		return o;
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
}
