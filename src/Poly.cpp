#include <iostream>
#include <algorithm>
#include "Poly.hpp"

namespace eng
{
	Poly::Poly(const std::vector<Vec> &vertices) :
			vertices_(vertices)
	{
		updateArea();
		adjustCentroidToOrigin();
		updateBoundingBox();
	}

	void Poly::updateBoundingBox()
	{
		double min_x = 0;
		double min_y = 0;
		double max_x = 0;
		double max_y = 0;

		for (const auto &v : vertices_)
		{
			if (v.x() < min_x)
				min_x = v.x();
			else if (v.x() > max_x)
				max_x = v.x();
			if (v.y() < min_y)
				min_y = v.y();
			else if (v.y() > max_y)
				max_y = v.y();
		}

		min_ = Vec(min_x, min_y);
		max_ = Vec(max_x, max_y);
	}

	// https://en.wikipedia.org/wiki/Centroid#Centroid_of_polygon
	void Poly::updateArea()
	{
		double a = 0;

		for (auto i = 0; i < vertices_.size(); ++i)
		{
			const auto &v_i = vertices_[i];
			const auto &v_j = vertices_[i + 1 == vertices_.size() ? 0 : i + 1];
			a += v_i.x() * v_j.y() - v_j.x() * v_i.y();
		}

		area_ = a / 2;
	}

	// https://en.wikipedia.org/wiki/Centroid#Centroid_of_polygon
	Vec Poly::getCentroid()
	{
		double x = 0, y = 0;

		for (auto i = 0; i < vertices_.size(); ++i)
		{
			const auto &v_i = vertices_[i];
			const auto &v_j = vertices_[i + 1 == vertices_.size() ? 0 : i + 1];
			x += (v_i.x() + v_j.x()) * (v_i.x() * v_j.y() - v_j.x() * v_i.y());
			y += (v_i.y() + v_j.y()) * (v_i.x() * v_j.y() - v_j.x() * v_i.y());
		}

		x *= 1 / (6 * area_);
		y *= 1 / (6 * area_);
		return Vec(x, y);
	}

	void Poly::adjustCentroidToOrigin()
	{
		Vec c = getCentroid();

		for (auto &v : vertices_)
			v -= c;
	}

	const std::vector<Vec> &Poly::vertices() const
	{
		return vertices_;
	}

	std::vector<Seg> Poly::edges() const
	{
		std::vector<Seg> edges;

		for (auto i = 0; i < vertices_.size(); ++i)
			edges.push_back(Seg(vertices_[i], vertices_[i + 1 == vertices_.size() ? 0 : i + 1]));

		return edges;
	}

	std::vector<Vec> Poly::edgeNormals() const
	{
		std::vector<Vec> edge_normals;

		for (auto i = 0; i < vertices_.size(); ++i)
		{
			const auto &v_i = vertices_[i];
			const auto &v_j = vertices_[i + 1 == vertices_.size() ? 0 : i + 1];
			double x = v_i.x() - v_j.x();
			double y = v_i.y() - v_j.y();
			edge_normals.push_back(Vec(y, -x));
		}

		return edge_normals;
	}

	std::vector<Vec> Poly::edgeNormalsNormalized() const
	{
		auto edge_normals = edgeNormals();

		for (auto &v : edge_normals)
			v = v.unitVector();

		return edge_normals;
	}

	const Vec &Poly::min() const
	{
		return min_;
	}

	const Vec &Poly::max() const
	{
		return max_;
	}

	void Poly::rotate(double rad)
	{
		for (auto &v : vertices_)
			v.rotate(rad);

		updateBoundingBox();
	}

	Poly Poly::createEquilateral(double w, double h)
	{
		std::vector<Vec> vertices;
		Vec tmp(0, 0);
		vertices.push_back(tmp);
		tmp += Vec(w / 2.0, -h);
		vertices.push_back(tmp);
		tmp += Vec(w / 2.0, h);
		vertices.push_back(tmp);
		return Poly(vertices);
	}

	Poly Poly::createPerpendicular(double w, double h)
	{
		std::vector<Vec> vertices;
		Vec tmp(0, 0);
		vertices.push_back(tmp);
		tmp += Vec(w, 0);
		vertices.push_back(tmp);
		tmp += Vec(0, h);
		vertices.push_back(tmp);
		return Poly(vertices);
	}

	Poly Poly::createRectangle(double w, double h)
	{
		std::vector<Vec> vertices;
		Vec tmp(0, 0);
		vertices.push_back(tmp);
		tmp += Vec(w, 0);
		vertices.push_back(tmp);
		tmp += Vec(0, h);
		vertices.push_back(tmp);
		tmp += Vec(-w, 0);
		vertices.push_back(tmp);
		return Poly(vertices);
	}

	Poly Poly::createPentagon(double w, double h)
	{
		std::vector<Vec> vertices;
		Vec tmp(0, 0);
		vertices.push_back(tmp);
		tmp += Vec(w / 2.0, -h / 2.0);
		vertices.push_back(tmp);
		tmp += Vec(w / 2.0, h / 2.0);
		vertices.push_back(tmp);
		tmp += Vec(-w / 3.0, h / 2.0);
		vertices.push_back(tmp);
		tmp += Vec(-w / 3.0, 0.0);
		vertices.push_back(tmp);
		return Poly(vertices);
	}
}
