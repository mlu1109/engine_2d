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
					eng::Vec(250, 400),
					eng::Poly::createRectangle(100, 100),
					10
			)
	);
	world.addObject(
			eng::PhysicsObject(
					eng::Vec(300, 300),
					eng::Poly::createPerpendicular(100, 100),
					10
			)
	);

	//world.getObject(1).addAngVel(0.5);

	eng::PhysicsObject &controlled = world.getObject(0);

	while (input.running())
	{
		if (world.timeStep())
		{
			input.handleEvents(world, controlled);
			render.clear();
			render.setColor(0x00FF0000);
			render.paintObjectsWithBB(world.objects());
			render.setColor(0xFFFF0000);

			for (const auto &c : world.collisions())
			{
				render.setColor(0xFFFF0000);
				render.paintBB(c.a());
				render.paintBB(c.b());
				if (c.sat())
				{
					render.setColor(0xFF000000);
					render.paintObject(c.a());
					render.paintObject(c.b());
					render.setColor(0x00FFFF00);
					render.paintSeg(c.a().pos(), c.a().pos() + c.mtv() * 100);
				}
			}

			render.update();
		}
	}
}