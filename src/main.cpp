#include "Render.hpp"
#include "World.hpp"
#include "Input.h"

using namespace eng;

int main()
{
	World world;
	Render render;
	Input input;

	world.addObject(
			PhysicsObject(
					Vec(-100, -100),
					Poly::createPentagon(50, 50),
					2
			)
	);
	world.addObject(
			PhysicsObject(
					Vec(100, 100),
					Poly::createRectangle(100, 100),
					10
			)
	);
	world.addObject(
			PhysicsObject(
					Vec(200, 200),
					Poly::createPerpendicular(100, 100),
					10
			)
	);
	world.addObject(
			PhysicsObject(
					Vec(0, 0),
					Poly::createRectangle(1000, 5),
					INFINITY
			)
	);

	world.addObject(
			PhysicsObject(
					Vec(0, 400),
					Poly::createRectangle(1000, 5),
					INFINITY
			)
	);

	auto *controlled = world.getObject(0);

	while (input.running())
	{
		if (world.timeStep())
		{
			input.handleEvents(world, controlled, render);

			render.clear();
			render.paintGrid();
			render.paintObjects(world.objects());
			render.setColor(0xFF0000);
			render.paintObject(*controlled);
			for (const auto &c : world.collisions())
			{
				render.paintDebugCollision(c);
			}

			render.update();
		}
	}
}