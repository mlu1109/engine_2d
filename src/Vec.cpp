#include "Vec.hpp"
#include "Consts.hpp"
#include <cmath>

namespace eng
{
	Vec::Vec() :
			x_(0), y_(0)
	{

	}

	Vec::Vec(double x, double y) :
			x_(x), y_(y)
	{

	}

	double Vec::x() const
	{
		return x_;
	}

	double Vec::y() const
	{
		return y_;
	}

	double Vec::magnitude() const
	{
		return std::sqrt(x_ * x_ + y_ * y_);
	}

	double Vec::cross2d(const Vec &rhs) const
	{
		return x_ * rhs.y_ - y_ * rhs.x_;
	}

	double Vec::dot(const Vec &rhs) const
	{
		return x_ * rhs.x_ + y_ * rhs.y_;
	}

	bool Vec::equals(const Vec &to) const
	{
		return consts::EPSILON > std::abs(x_ - to.x_) && consts::EPSILON > std::abs(y_ - to.y_);
	}

	bool Vec::origin() const
	{
		return x_ == 0 && y_ == 0;
	}

	Vec Vec::project(const Vec &on) const
	{
		return dot(on) / on.dot(on) * on;
	}

	Vec Vec::unitVector() const
	{
		return *this / magnitude();
	}

	void Vec::rotate(double rad)
	{
		double x = x_;
		x_ = std::cos(rad) * x_ - std::sin(rad) * y_;
		y_ = std::sin(rad) * x + std::cos(rad) * y_;
	}

	const Vec &Vec::operator-=(const Vec &rhs)
	{
		x_ -= rhs.x_;
		y_ -= rhs.y_;
		return *this;
	}

	const Vec &Vec::operator+=(const Vec &rhs)
	{
		x_ += rhs.x_;
		y_ += rhs.y_;
		return *this;
	}

	const Vec &Vec::operator*=(const double rhs)
	{
		x_ *= rhs;
		y_ *= rhs;
		return *this;
	}

	const Vec &Vec::operator/=(const double rhs)
	{
		x_ /= rhs;
		y_ /= rhs;
		return *this;
	}

	Vec operator+(const Vec &lhs, const Vec &rhs)
	{
		return Vec(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
	}

	Vec operator-(const Vec &lhs, const Vec &rhs)
	{
		return Vec(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
	}

	Vec operator*(const Vec &lhs, double rhs)
	{
		return Vec(lhs.x_ * rhs, lhs.y_ * rhs);
	}

	Vec operator*(double lhs, const Vec &rhs)
	{
		return Vec(lhs * rhs.x_, lhs * rhs.y_);
	}

	Vec operator/(const Vec &lhs, double rhs)
	{
		return Vec(lhs.x_ / rhs, lhs.y_ / rhs);
	}

	bool operator==(const Vec &lhs, const Vec &rhs)
	{
		return lhs.equals(rhs);
	}

	bool operator!=(const Vec &lhs, const Vec &rhs)
	{
		return !lhs.equals(rhs);
	}

	bool operator<(const Vec &lhs, const Vec &rhs)
	{
		return lhs.magnitude() < rhs.magnitude();
	}

	std::ostream &operator<<(std::ostream &os, const Vec &v)
	{
		os << "Vec(" << v.x_ << ", " << v.y_ << ")";
		return os;
	}

	Vec Vec::cross(double lhs, const Vec &rhs)
	{
		return Vec(-lhs * rhs.y(), rhs.x() * lhs);
	}
}
