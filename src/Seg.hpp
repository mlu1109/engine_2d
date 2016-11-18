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
		const Vec &a() const;
		const Vec &b() const;
		Vec min() const;
		Vec max() const;
		double length() const;
		Seg project(const Vec &on) const;
		Seg overlap(const Seg &other) const;
		Vec vector() const;
		bool overlapping(const Seg &other) const;
		bool origin() const;
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
