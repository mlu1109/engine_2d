#include <algorithm>
#include "Seg.hpp"
#include "Consts.hpp"
#include <cfloat>

namespace eng
{
	Seg::Seg(const Vec &a, const Vec &b) :
			Line(a, b)
	{

	}

	Seg::Seg(double x_1, double y_1, double x_2, double y_2) :
			Line(Vec(x_1, y_1), Vec(x_2, y_2))
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
		const auto &a = from();
		const auto &b = to();
		const auto &c = s.from();
		const auto &d = s.to();

		return (
				(!horizontal() && (a.x() < c.x() && c.x() < b.x()) || (c.x() < a.x() && a.x() < d.x())) ||
				(a.y() < c.y() && c.y() < b.y()) ||	(c.y() < a.y() && a.y() < d.y())
		);
	}

	bool Seg::origin() const
	{
		return a_.origin() && b_.origin();
	}

	bool Seg::parallel(const Seg &s) const
	{
		return std::abs(s.vector().cross2d(vector())) < consts::EPSILON;
	}

	// Assumes that segments are collinear, if no overlap is found an "empty" segment is returned
	Seg Seg::overlap(const Seg &s) const
	{
		const Vec &a = from();
		const Vec &b = to();
		const Vec &c = s.from();
		const Vec &d = s.to();

		if (horizontal())
		{
			if ((a.x() < c.x() && c.x() < b.x()))
				return Seg(c, b);
			else if (c.x() < a.x() && a.x() < d.x())
				return Seg(a, d);
		}
		else
		{
			if ((a.y() < c.y() && c.y() < b.y()))
				return Seg(c, b);
			else if (c.y() < a.y() && a.y() < d.y())
				return Seg(a, d);
		}

		return Seg(Vec(0, 0), Vec(0, 0));
	}

	Vec Seg::intersection(const Seg &s) const
	{
		if (s.vertical() && horizontal() || s.horizontal() && vertical())
		{
			if (s.vertical())
				return Vec(s.a_.x(), a_.y());

			return Vec(a_.x(), s.a_.y());
		}

		const auto &a = from();
		const auto &b = to();
		const auto &c = s.from();
		const auto &d = s.to();

		double k_1 = (b.y() - a.y()) / (b.x() - a.x());
		double k_2 = (d.y() - c.y()) / (d.x() - c.x()); // s
		double m_1 = (a.y() - k_1 * a.x());
		double m_2 = (c.y() - k_2 * c.x()); // s
		double x, y;

		if (s.vertical() || vertical())
		{
			x = s.vertical() ? s.a().x() : a_.x();
			y = s.vertical() ? k_1 * x + m_1 : k_2 * x + m_2;
		}
		else if (s.horizontal() || horizontal())
		{
			y = s.horizontal() ? s.a().y() : a_.y();
			x = s.horizontal() ? (y - m_1) / k_1 : (y - m_2) / k_2;
		}
		else
		{
			x = (m_2 - m_1) / (k_1 - k_2);
			y = k_1 * x + m_1;
		}

		return Vec(x, y);
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
