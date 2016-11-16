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

	}
}