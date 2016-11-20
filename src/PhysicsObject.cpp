#include "PhysicsObject.h"
#include "Consts.hpp"

namespace eng
{
	PhysicsObject::PhysicsObject(const Vec &pos, const Poly &poly, double mass) :
			pos_(pos), poly_(poly), mass_(mass), inv_mass_(1 / mass)
	{
		calcInertia();
	}

	const Poly &PhysicsObject::poly() const
	{
		return poly_;
	}

	const Vec &PhysicsObject::pos() const
	{
		return pos_;
	}

	const Vec &PhysicsObject::vel() const
	{
		return vel_;
	}

	const Vec &PhysicsObject::acc() const
	{
		return acc_;
	}

	double PhysicsObject::inv_mass() const
	{
		return inv_mass_;
	}

	double PhysicsObject::inv_inertia() const
	{
		return inv_inertia_;
	}

	double PhysicsObject::ang_vel() const
	{
		return ang_vel_;
	}


	void PhysicsObject::addVel(const Vec &vel)
	{
		vel_ += vel;
	}


	void PhysicsObject::addAngVel(double ang_vel)
	{
		ang_vel_ += ang_vel;
	}

	// https://en.wikipedia.org/wiki/List_of_moments_of_inertia#Moments_of_inertia
	void PhysicsObject::calcInertia()
	{
		const auto &vertices = poly_.vertices();
		double i_n = 0, i_d = 0;

		for (int i = 0; i < vertices.size(); ++i)
		{
			const auto &v_i = vertices[i];
			const auto &v_j = vertices[i + 1 == vertices.size() ? 0 : i + 1];
			i_n += v_j.cross2d(v_i) * (v_i.dot(v_i) + v_i.dot(v_j) + v_j.dot(v_j));
			i_d += v_j.cross2d(v_i);
		}

		inertia_ = (mass_ * i_n) / (6 * i_d);
		inv_inertia_ = 1.0 / inertia_;
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
