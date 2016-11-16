#include <iostream>
#include "Render.hpp"
#include "World.hpp"
#include "Input.h"

int main()
{
	eng::World world;
	eng::Render render;
	eng::Input input;

	world.addObject(
			eng::PhysicsObject(
					eng::Vec(100, 100),
					eng::Poly::createRectangle(100, 100),
					10
			)
	);
	world.addObject(
			eng::PhysicsObject(
					eng::Vec(300, 300),
					eng::Poly::createPerpendicular(50, 50),
					10
			)
	);

	eng::PhysicsObject &controlled = world.getObject(0);

	while (input.running())
	{
		if (world.timeStep())
		{
			input.handleEvents(world, controlled);
			render.clear();
			render.setColor(0x00FF0000);
			render.paintObjects(world.objects());
			render.setColor(0xFFFF0000);

			for (const auto &c : world.collisions())
			{
				render.paintObject(c.a());
				render.paintObject(c.b());
			}

			render.update();
		}
	}
}