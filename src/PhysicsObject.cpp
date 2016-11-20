#include "PhysicsObject.h"
#include "Consts.hpp"

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

	std::vector<Vec> PhysicsObject::vertices() const
	{
		std::vector<Vec> vertices = poly_.vertices();

		for (auto &v : vertices)
			v += pos_;

		return vertices;
	}

	std::vector<Seg> PhysicsObject::edges() const
	{
		std::vector<Seg> edges = poly_.edges();

		for (auto &e : edges)
			e += pos_;

		return edges;
	}

	std::vector<Vec> PhysicsObject::edgeNormals() const
	{
		std::vector<Vec> edge_normals = poly_.edgeNormals();

		for (auto &v : edge_normals)
			v += pos_;

		return edge_normals;
	}

	std::vector<Vec> PhysicsObject::edgeNormalsNormalized() const
	{
		std::vector<Vec> edge_normals_normalized = poly_.edgeNormalsNormalized();

		for (auto &v : edge_normals_normalized)
			v += pos_;

		return edge_normals_normalized;
	}

	Vec PhysicsObject::min() const
	{
		return poly_.min() + pos_;
	}

	Vec PhysicsObject::max() const
	{
		return poly_.max() + pos_;
	}

	Seg PhysicsObject::project(const Vec &v) const
	{
		auto verts = vertices();
		double min = v.dot(verts[0]);
		double max = min;
		auto mini = (verts[0]).project(v);
		auto maxi = mini;

		for (const auto &iv : verts)
		{
			double p = v.dot(iv);
			if (p < min)
			{
				min = p;
				mini = iv.project(v);
			}
			else if (p > max)
			{
				max = p;
				maxi = iv.project(v);
			}
		}

		return Seg(mini, maxi);
	}

	bool PhysicsObject::bbContains(const Vec &p) const
	{
		double x_min = p.x() - min().x();
		double x_max = p.x() - max().x();
		double y_min = p.y() - min().y();
		double y_max = p.y() - max().y();

		return x_min > -consts::EPSILON && x_max < consts::EPSILON &&
			   y_min > -consts::EPSILON && y_max < consts::EPSILON;
	}

}
