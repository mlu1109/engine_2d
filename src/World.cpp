#include <iostream>
#include <cmath>
#include "World.hpp"
#include "Consts.hpp"

namespace eng
{
	World::World()
	{

	}

	World::World(const std::vector<PhysicsObject> &objects) :
			objects_(objects)
	{

	}

	const std::vector<PhysicsObject> &World::objects() const
	{
		return objects_;
	}

	const std::vector<Collision> &World::collisions() const
	{
		return collisions_;
	}

	void World::addObject(const eng::PhysicsObject &obj)
	{
		objects_.push_back(obj);
	}

	PhysicsObject &World::getObject(int i)
	{
		return objects_[i];
	}

	void World::findCollisions()
	{
		collisions_.clear();
		for (auto i = 0; i < objects_.size() - 1; ++i)
		{
			for (auto j = i + 1; j < objects_.size(); ++j)
			{
				if (Collision::AABBCollision(objects_[i], objects_[j]))
					collisions_.push_back(Collision(objects_[i], objects_[j]));
			}
		}
	}

	void World::handleCollisions()
	{
		for (auto &c : collisions_)
		{
			c.SATCollisionCalcMTV();
			if (c.sat())
				c.calcPointOfIntersection();
		}
	}

	bool World::timeStep()
	{
		double dt = time_.handleDt();

		if (dt >= consts::TICK_RATE)
		{
			for (auto &obj : objects_)
				obj.timeStep(dt);

			findCollisions();
			handleCollisions();
			return true;
		}

		return false;
	}

}