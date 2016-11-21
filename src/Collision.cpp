#include <cmath>
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

	const std::vector<Vec> &Collision::pois() const
	{
		return pois_;
	}

	bool Collision::sat() const
	{
		return sat_;
	}

	// http://www.dyn4j.org/2010/01/sat/
	bool Collision::SATCollisionCalcMTV()
	{
		std::vector<Vec> axes[2];
		axes[0] = a_.poly().edgeNormalsNormalized();
		axes[1] = b_.poly().edgeNormalsNormalized();
		auto mtv = Seg::longestSeg();

		for (int i = 0; i < 2; ++i)
		{
			for (const auto &axis : axes[i])
			{
				auto a_proj = a_.project(axis);
				auto b_proj = b_.project(axis);
				auto overlap = a_proj.overlap(b_proj);

				if (overlap.origin())
					return false;

				mtv = overlap.length() < mtv.length() ? overlap : mtv;
			}
		}

		sat_ = true;
		mtv_ = mtv.vector();
		mtv_ = mtv_.dot(a_.pos() - b_.pos()) > 0 ? mtv_ : -1 * mtv_;
		return true;
	}

	void Collision::calcPointsOfIntersection()
	{
		auto a_edges = a_.edges();
		auto b_edges = b_.edges();
		pois_.clear();

		for (const auto &a_e : a_edges)
		{
			for (const auto &b_e : b_edges)
			{
				auto poi = a_e.intersection(b_e);
				if (a_.bbContains(poi) && b_.bbContains(poi))
					pois_.push_back(poi);
			}
		}
	}

	bool Collision::AABBCollision(const PhysicsObject &a, const PhysicsObject &b)
	{
		return !(a.max().x() < b.min().x() || a.max().y() < b.min().y() ||
				 b.max().x() < a.min().x() || b.max().y() < a.min().y());
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
				auto a_proj = a.project(axis);
				auto b_proj = b.project(axis);

				if (!a_proj.overlapping(b_proj))
					return false;
			}
		}

		return true;
	}

	void Collision::separateObjects()
	{
		double a_speed = a_.vel().magnitude();
		double b_speed = b_.vel().magnitude();

		if (a_speed + b_speed == 0)
			return;

		double a_ratio = a_speed / (a_speed + b_.vel().magnitude());
		double b_ratio = 1 - a_ratio;
		a_.addPos(mtv_ * a_ratio);
		b_.addPos(mtv_ * -b_ratio);
	}

	// http://www.myphysicslab.com/engine2D/collision/collision-en.html
	void Collision::impulseBasedResolution()
	{
		double e = 1; // For the time being
		const auto &p = pois_[0];
		const auto &n = mtv_.unitVector();
		auto r_ap = p - a_.pos();
		auto r_bp = p - b_.pos();
		// Pre-collision velocities
		auto v_ap1 = a_.vel() + Vec::cross(a_.ang_vel(), r_ap);
		auto v_bp1 = b_.vel() + Vec::cross(b_.ang_vel(), r_bp);
		auto v_ab1 = v_ap1 - v_bp1;

		separateObjects();
		// Impulse parameter
		const double j = (-(1 + e) * v_ab1.dot(n)) /
						 (a_.inv_mass() + b_.inv_mass() +
						  std::pow(r_ap.cross2d(n), 2) * a_.inv_inertia() +
						  std::pow(r_bp.cross2d(n), 2) * b_.inv_inertia());
		// Apply impulse
		a_.addVel(j * n * a_.inv_mass());
		b_.addVel(-j * n * b_.inv_mass());
		a_.addAngVel(r_ap.cross2d(j * n) * a_.inv_inertia());
		b_.addAngVel(-r_bp.cross2d(j * n) * b_.inv_inertia());
	}

	void Collision::resolveCollision()
	{
		if (pois_.empty())
			separateObjects();
		else
			impulseBasedResolution();
	}
}