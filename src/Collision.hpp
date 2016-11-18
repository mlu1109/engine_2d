#ifndef ENGINE2D_COLLISION_HPP
#define ENGINE2D_COLLISION_HPP

#include <cfloat>
#include "Collision.hpp"
#include "PhysicsObject.h"

namespace eng
{
	class Collision
	{
		PhysicsObject &a_;
		PhysicsObject &b_;
		Vec mtv_;
		bool sat_ = false;
	public:
		Collision(PhysicsObject &a, PhysicsObject &b);
		const PhysicsObject &a() const;
		const PhysicsObject &b() const;
		const Vec &mtv() const;
		bool sat() const;
		bool SATCollisionCalcMTV();
		static bool AABBCollision(const PhysicsObject &a, const PhysicsObject &b);
		static bool SATCollision(const PhysicsObject &a, const PhysicsObject &b);
	};
};


#endif //ENGINE2D_COLLISION_HPP
