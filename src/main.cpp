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
					Vec(-300, -300),
					Poly::createRectangle(5, 1000),
					INFINITY
			)
	);

	//world.getObject(1).addAngVel(0.1);

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
			/*for (const auto &c : world.collisions())
			{
				render.paintDebugCollision(c);
			}*/

			render.update();
		}
	}
}