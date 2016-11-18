#include <gtest/gtest.h>
#include "src/Vec.hpp"
#include "src/Consts.hpp"

using namespace eng;

TEST(vec, dot)
{
	Vec a(2, 3);
	Vec b(-2, 2);
	EXPECT_EQ(a.dot(b), 2.0);
	EXPECT_EQ(a.dot(a), 13.0);
	EXPECT_EQ(b.dot(b), 8.0);
}

TEST(vec, op_mul)
{
	Vec a(2, 3);
	double b = 2.5;
	Vec r(5, 7.5);
	EXPECT_EQ(a * b, r);
	EXPECT_EQ(b * a, r);
}

TEST(vec, magnitude)
{
	Vec v(1, 1);
	ASSERT_EQ(v.magnitude(), std::sqrt(2));
}

TEST(vec, rotation)
{
	Vec v(2, 3);
	v.rotate(consts::PI/4);
	Vec r(-0.707106, 3.535533);
	ASSERT_EQ(v, r);
	Vec bad_r(0.707106, 3.535533);
	ASSERT_NE(v, bad_r);
}

TEST(vec, projection)
{
	Vec v(0, 2);
	Vec project_on(1, 1);
	Vec r(1, 1);
	EXPECT_EQ(v.project(project_on), r);
}