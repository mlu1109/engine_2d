#ifndef ENGINE2D_CONSTS_HPP
#define ENGINE2D_CONSTS_HPP

#include "Vec.hpp"

namespace consts
{
	const double PI = 3.1415926535897;
	const double EPSILON = 0.000001;
	const double TICK_RATE = 1.0 / 60.0;
	// Input speed modifiers -- should be handled elsewhere
	const double SCROLL_RATE = 0.05;
	const double ANG_VEC_MOD = 0.3;
	const eng::Vec UP_VEL_MOD(0, -10);
	const eng::Vec LEFT_VEL_MOD(-10, 0);
	const eng::Vec DOWN_VEL_MOD(0, 10);
	const eng::Vec RIGHT_VEL_MOD(10, 0);

}

#endif //ENGINE2D_CONSTS_HPP
