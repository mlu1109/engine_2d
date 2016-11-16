#ifndef ENGINE2D_TIME_H
#define ENGINE2D_TIME_H

#include <chrono>

namespace eng
{
	class Time
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> now_;
		std::chrono::time_point<std::chrono::high_resolution_clock> last_;
		double acc_dt_ = 0;
	public:
		Time();
		void update();
		void reset();
		double dt() const;
	};
}

#endif //ENGINE2D_TIME_H
