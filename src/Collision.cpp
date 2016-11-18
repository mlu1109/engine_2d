#include "Collision.hpp"

namespace eng
{
	Collision::Collision(PhysicsObject &a, PhysicsObject &b) :
			a_(a), b_(b)
	{

	}

	const PhysicsObject &Collision::a() const
	{
		return a_;
	}

	const PhysicsObject &Collision::b() const
	{
		return b_;
	}

	const Vec &Collision::mtv() const
	{
		return mtv_;
	}

	bool Collision::sat() const
	{
		return sat_;
	}

	bool Collision::SATCollisionCalcMTV()
	{
		mtv_ = Vec(DBL_MAX, DBL_MAX);
		std::vector<Vec> axes[2];
		axes[0] = a_.poly().edgeNormalsNormalized();
		axes[1] = b_.poly().edgeNormalsNormalized();
		Seg mtv = Seg::longestSeg();

		for (int i = 0; i < 2; ++i)
		{
			for (const auto &axis : axes[i])
			{
				Seg a_proj = a_.poly().project(axis, a_.pos());
				Seg b_proj = b_.poly().project(axis, b_.pos());
				Seg overlap = a_proj.overlap(b_proj);

				if (overlap.origin())
					return false;

				mtv = overlap.length() < mtv.length() ? overlap : mtv;
			}
		}

		sat_ = true;
		mtv_ = mtv.vector().unitVector();
		return true;
	}

	bool Collision::AABBCollision(const PhysicsObject &a, const PhysicsObject &b)
	{
		Vec a_min = a.poly().min() + a.pos();
		Vec a_max = a.poly().max() + a.pos();
		Vec b_min = b.poly().min() + b.pos();
		Vec b_max = b.poly().max() + b.pos();
		return !(a_max.x() < b_min.x() || a_max.y() < b_min.y() || b_max.x() < a_min.x() || b_max.y() < a_min.y());
	}

	// http://www.dyn4j.org/2010/01/sat/
	bool Collision::SATCollision(const PhysicsObject &a, const PhysicsObject &b)
	{
		std::vector<Vec> axes[2];
		axes[0] = a.poly().edgeNormals();
		axes[1] = b.poly().edgeNormals();

		for (int i = 0; i < 2; ++i)
		{
			for (const auto &axis : axes[i])
			{
				Seg a_proj = a.poly().project(axis, a.pos());
				Seg b_proj = b.poly().project(axis, b.pos());

				if (!a_proj.overlapping(b_proj))
					return false;
			}
		}

		return true;
	}
}