#ifndef ENGINE2D_SEG_HPP
#define ENGINE2D_SEG_HPP

#include <iostream>
#include "Vec.hpp"
#include "Line.hpp"

namespace eng
{
	class Seg : public Line
	{
	public:
		Seg(const Vec &a, const Vec &b);
		Seg(double x_1, double y_1, double x_2, double y_2);
		const Vec &a() const;
		const Vec &b() const;
		Seg project(const Vec &on) const;
		Seg overlap(const Seg &s) const;
		double length() const;
		bool overlapping(const Seg &s) const;
		bool origin() const;
		bool parallel(const Seg &s) const;
		Vec intersection(const Seg &s) const;
		void operator+=(const Vec &rhs);
		bool operator<(const Seg &rhs) const;
		friend bool operator==(const Seg &lhs, const Seg &rhs);
		friend bool operator!=(const Seg &lhs, const Seg &rhs);
		friend Seg operator+(const Seg &lhs, const Vec &rhs);
		friend std::ostream &operator<<(std::ostream &os, const Seg &s);
		static Seg longestSeg();
	};
}

#endif //ENGINE2D_SEG_HPP
