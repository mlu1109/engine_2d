#include <stdlib.h>
#include "Render.hpp"
#include "World.hpp"
#include "Input.hpp"

using namespace eng;


Poly getRandomPoly(double width, double height)
{
	switch(rand() % 4)
	{
		case 0:
			return Poly::createPerpendicular(width, height);
		case 1:
			return Poly::createEquilateral(width, height);
		case 2:
			return Poly::createRectangle(width, height);
		case 3:
		default:
			return Poly::createPentagon(width, height);
	}
}

int main()
{
	World world;
	Render render;
	Input input;

	srand((unsigned) std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

	for (int i = 0; i < 500; ++i)
	{
		int s = rand() % 4;
		int x = rand() % 2000;
		int y = rand() % 2000;
		int width = rand() % 200;
		int height = rand() % 200;
		int mass = rand() % 200;

		world.addObject(
				PhysicsObject(
						Vec(x - x/2, y - y/2 ),
						getRandomPoly(width, height),
						mass
				)
		);
	}

	while (input.running())
	{
		if (world.timeStep())
		{
			input.handleEvents(world, render);

			render.clear();
			render.paintGrid();
			render.paintObjects(world.objects());
			render.setColor(0xFF0000);
			if (input.controlled())
				render.paintObject(*input.controlled());
			/*for (const auto &c : worleeeeeeeeeeeeed.collisions())
			{
				render.paintDebugCollision(c);
			}*/

			render.update();
		}
	}
}