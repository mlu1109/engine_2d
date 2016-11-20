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

TEST(seg, intersection)
{
	Seg a(Vec(0, 0), Vec(2, 2));
	Seg b(Vec(0, 2), Vec(2, 0));
	EXPECT_EQ(a.intersection(b), Vec(1, 1));
	EXPECT_EQ(b.intersection(a), Vec(1, 1));
	a = Seg(Vec(2, 2), Vec(0, 0));
	b = Seg(Vec(2, 0), Vec(0, 2));
	EXPECT_EQ(a.intersection(b), Vec(1, 1));
	a = Seg(1, 0, 1, 1);
	b = Seg(-1, 1, 2, 1);
	EXPECT_EQ(a.intersection(b), Vec(1, 1));
	EXPECT_EQ(b.intersection(a), Vec(1, 1));
	a = Seg(-1, 1, 2, 1);
	b = Seg(1, 0, 1, 1);
	EXPECT_EQ(a.intersection(b), Vec(1, 1));
	EXPECT_EQ(b.intersection(a), Vec(1, 1));
	a = Seg(1, 0, 1, 1);
	b = Seg(0, 1, 1, 2);
	EXPECT_EQ(a.intersection(b), Vec(1, 2));
	EXPECT_EQ(b.intersection(a), Vec(1, 2));
	a = Seg(0, 1, 3, 1);
	b = Seg(0, -3, 3, 0);
	EXPECT_EQ(a.intersection(b), Vec(4, 1));
	EXPECT_EQ(b.intersection(a), Vec(4, 1));
}