#ifndef ENGINE2D_ENGINE_HPP
#define ENGINE2D_ENGINE_HPP

#include "PhysicsObject.h"
#include "Time.h"
#include "Collision.hpp"

namespace eng
{
	class World
	{
		std::vector<PhysicsObject> objects_;
		std::vector<Collision> collisions_;
		Time time_;
	public:
		World();
		World(const std::vector<PhysicsObject> &objects_);
		const std::vector<PhysicsObject> &objects() const;
		const std::vector<Collision> &collisions() const;
		void addObject(const PhysicsObject &o);
		PhysicsObject *getObject(int i);
		PhysicsObject *getObjectAtPos(const Vec& v);
		void findCollisions();
		void handleCollisions();
		bool timeStep();
	};
}

#endif //ENGINE2D_ENGINE_HPP
