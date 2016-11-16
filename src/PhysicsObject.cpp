#include "PhysicsObject.h"

namespace eng
{
	PhysicsObject::PhysicsObject(const Vec &pos, const Poly &poly, double mass) :
			pos_(pos), poly_(poly), mass_(mass)
	{

	}

	const Poly &PhysicsObject::poly() const
	{
		return poly_;
	}

	const Vec &PhysicsObject::pos() const
	{
		return pos_;
	}

	void PhysicsObject::addAcc(const Vec &acc)
	{
		acc_ += acc;
	}

	void PhysicsObject::addVel(const Vec &vel)
	{
		vel_ += vel;
	}

	void PhysicsObject::addAngAcc(double ang_acc)
	{
		ang_acc_ += ang_acc;
	}

	void PhysicsObject::addAngVel(double ang_vel)
	{
		ang_vel_ += ang_vel;
	}

	void PhysicsObject::immediateStop()
	{
		acc_ = Vec(0, 0);
		vel_ = Vec(0, 0);
		ang_acc_ = 0;
		ang_vel_ = 0;
	}

	void PhysicsObject::rotate(double rad)
	{
		poly_.rotate(rad);
	}

	void PhysicsObject::timeStep(double dt)
	{
		vel_ += acc_ * dt;
		pos_ += vel_ * dt;
		ang_vel_ += ang_acc_ * dt;
		poly_.rotate(ang_vel_ * dt);
	}

}
