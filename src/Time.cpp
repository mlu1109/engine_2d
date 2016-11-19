#include <iostream>
#include "Time.h"
#include "Consts.hpp"

namespace eng
{
	Time::Time() :
			now_(std::chrono::high_resolution_clock::now()), last_(now_)
	{

	}

	void Time::update()
	{
		now_ = std::chrono::high_resolution_clock::now();
		auto dt = std::chrono::duration<double, std::ratio<1>>(now_ - last_);
		last_ = now_;
		acc_dt_ += dt.count();
	}

	void Time::reset()
	{
		acc_dt_ = 0;
	}

	double Time::handleDt()
	{
		update();
		double r = acc_dt_;
		if (acc_dt_ >= consts::TICK_RATE)
			reset();

		return r;
	}
}