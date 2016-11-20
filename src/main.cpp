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
					Vec(250, 400),
					Poly::createRectangle(100, 100),
					10
			)
	);
	world.addObject(
			PhysicsObject(
					Vec(300, 300),
					Poly::createPerpendicular(100, 100),
					10
			)
	);
	world.addObject(
			PhysicsObject(
					Vec(100, 100),
					Poly::createRectangle(150, 150),
					10
			)
	);

	//world.getObject(1).addAngVel(0.1);

	auto &controlled = world.getObject(0);

	while (input.running())
	{
		if (world.timeStep())
		{
			input.handleEvents(world, controlled, render);

			render.clear();
			render.paintGrid();
			render.paintObjects(world.objects());
			/*for (const auto &c : world.collisions())
			{
				render.paintDebugCollision(c);
			}*/

			render.update();
		}
	}
}