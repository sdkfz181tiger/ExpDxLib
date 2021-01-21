#ifndef _TIMERCPP_H_
#define _TIMERCPP_H_

#include <iostream>
#include <thread>
#include <chrono>

class TimerCpp {
	bool clear = false;

public:
	void setTimeout(std::function<void()> func, int delay);

	void setInterval(std::function<void()> func, int interval);

	void stop();
};

#endif // _TIMERCPP_H_