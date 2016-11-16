#ifndef ENGINE2D_PHYSICSOBJECT_H
#define ENGINE2D_PHYSICSOBJECT_H

#include "Poly.hpp"

namespace eng
{
	class PhysicsObject
	{
		Poly poly_;
		Vec acc_;
		Vec vel_;
		Vec pos_;
		double mass_ = 0;
		double inv_mass_ = 0;
		double ang_acc_ = 0;
		double ang_vel_ = 0;
		double restitution_ = 0;
		double friction_ = 0;
	public:
		PhysicsObject(const Vec &pos, const Poly &poly, double mass);
		const Poly &poly() const;
		const Vec &pos() const;
		void addAcc(const Vec &acc);
		void addVel(const Vec &vel);
		void addAngAcc(double ang_acc);
		void addAngVel(double ang_vel);
		void immediateStop();
		void rotate(double rad);
		void timeStep(double dt);
	};
}

#endif //ENGINE2D_PHYSICSOBJECT_H
