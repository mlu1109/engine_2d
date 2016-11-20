#ifndef ENGINE2D_VEC_HPP
#define ENGINE2D_VEC_HPP

#include <iostream>

namespace eng
{
	class Vec
	{
		double x_;
		double y_;
	public:
		Vec();
		Vec(double x, double y);
		double x() const;
		double y() const;
		double x_sqrd() const;
		double y_sqrd() const;
		double magnitude() const;
		double distance(const Vec &to) const;
		double cross2d(const Vec &rhs) const;
		double dot(const Vec &rhs) const;
		double angle(const Vec &rhs) const;
		bool equals(const Vec &to) const;
		bool origin() const;
		Vec cross3d(double z) const;
		Vec project(const Vec &on) const;
		Vec unitVector() const;
		void add(const Vec &rhs);
		void sub(const Vec &rhs);
		void mul(double rhs);
		void div(double rhs);
		void rotate(double rad);
		const Vec &operator-=(const Vec &rhs);
		const Vec &operator+=(const Vec &rhs);
		const Vec &operator*=(const double rhs);
		friend Vec operator+(const Vec &lhs, const Vec &rhs);
		friend Vec operator-(const Vec &lhs, const Vec &rhs);
		friend Vec operator*(const Vec &lhs, double rhs);
		friend Vec operator*(double lhs, const Vec &rhs);
		friend Vec operator/(const Vec &lhs, double rhs);
		friend bool operator==(const Vec &lhs, const Vec &rhs);
		friend bool operator!=(const Vec &lhs, const Vec &rhs);
		friend bool operator<(const Vec &lhs, const Vec &rhs);
		friend std::ostream &operator<<(std::ostream &os, const Vec &v);
		static Vec cross(double lhs, const Vec &rhs);
	};
}

#endif //ENGINE2D_VEC_HPP
