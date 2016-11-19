#include <gtest/gtest.h>
#include "src/Seg.hpp"

using namespace eng;

TEST(seg, project)
{
	Seg seg(Vec(2, 2), Vec(4, 4));
	Vec project_on(1, 0);
	Seg projection = seg.project(project_on);
	EXPECT_EQ(projection, Seg(Vec(2, 0), Vec(4, 0)));
}

TEST(seg, overlapping)
{
	Seg a(Vec(1, 1), Vec(3, 3));
	Seg b(Vec(2, 2), Vec(4, 4));
	EXPECT_TRUE(a.overlapping(b));
	EXPECT_TRUE(b.overlapping(a));
	Seg c(Vec(5, 5), Vec(6, 6));
	EXPECT_FALSE(a.overlapping(c));
	EXPECT_FALSE(c.overlapping(a));

	a = Seg(Vec(3, 2), Vec(1, 1));
	b = Seg(Vec(6, 5), Vec(2, 3));
	ASSERT_TRUE(a.overlapping(b));
}

TEST(seg, overlap)
{
	Seg a(Vec(2, 2), Vec(4, 4));
	Seg b(Vec(3, 3), Vec(5, 5));
	EXPECT_EQ(a.overlap(b), Seg(Vec(3, 3), Vec(4, 4)));
	EXPECT_EQ(b.overlap(a), Seg(Vec(3, 3), Vec(4, 4)));
	a = Seg(Vec(1, 1), Vec(3, 3));
	EXPECT_EQ(a.overlap(b), Seg(Vec(0, 0), Vec(0, 0)));
	a = Seg(Vec(0, 0), Vec(2, 2));
	EXPECT_EQ(a.overlap(b), Seg(Vec(0, 0), Vec(0, 0)));
}