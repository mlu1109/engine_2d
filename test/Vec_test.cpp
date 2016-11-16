#include <gtest/gtest.h>
#include "src/Vec.hpp"
#include "src/Consts.hpp"

TEST(vec, magnitude)
{
	eng::Vec v(1, 1);
	ASSERT_EQ(v.magnitude(), std::sqrt(2));
}

TEST(vec, rotation)
{
	eng::Vec v(2, 3);
	v.rotate(consts::PI/4);

	eng::Vec r(-0.707106, 3.535533);
	ASSERT_EQ(v, r);
	eng::Vec bad_r(0.707106, 3.535533);
	ASSERT_NE(v, bad_r);
}


