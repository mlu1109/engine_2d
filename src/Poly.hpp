#ifndef ENGINE2D_POLY_HPP
#define ENGINE2D_POLY_HPP

#include <vector>
#include "Vec.hpp"
#include "Line.hpp"
#include "Seg.hpp"

namespace eng
{
	class Poly
	{
		std::vector<Vec> vertices_;
		Vec min_;
		Vec max_;
		double area_;
		void updateArea();
		void adjustCentroidToOrigo();
		void updateBoundingBox();
		Vec getCentroid();
	public:
		Poly(const std::vector<Vec> &vertices);
		const std::vector<Vec> &vertices() const;
		const Vec &min() const;
		const Vec &max() const;
		std::vector<Seg> edges() const;
		std::vector<Vec> edgeNormals() const;
		std::vector<Vec> edgeNormalsNormalized() const;
		void rotate(double rad);
		static Poly createEquilateral(double w, double h);
		static Poly createPerpendicular(double w, double h);
		static Poly createRectangle(double w, double h);
		static Poly createPentagon(double w, double h);
	};
}

#endif //ENGINE2D_POLY_HPP