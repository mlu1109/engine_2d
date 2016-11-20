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
		double inertia_ = 0;
		double inv_inertia_ = 0;
		double ang_acc_ = 0;
		double ang_vel_ = 0;
	public:
		PhysicsObject(const Vec &pos, const Poly &poly, double mass);
		const Poly &poly() const;
		const Vec &pos() const;
		const Vec &vel() const;
		const Vec &acc() const;
		double inv_mass() const;
		double inv_inertia() const;
		double ang_vel() const;
		void addVel(const Vec &vel);
		void addAngVel(double ang_vel);
		void calcInertia();
		void immediateStop();
		void rotate(double rad);
		void timeStep(double dt);
		std::vector<Vec> vertices() const;
		std::vector<Seg> edges() const;
		std::vector<Vec> edgeNormals() const;
		std::vector<Vec> edgeNormalsNormalized() const;
		Vec min() const;
		Vec max() const;
		Seg project(const Vec &v) const;
		bool bbContains(const Vec &p) const;
	};
}

#endif //ENGINE2D_PHYSICSOBJECT_H
