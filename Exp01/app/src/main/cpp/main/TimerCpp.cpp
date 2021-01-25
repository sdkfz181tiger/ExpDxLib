#include "TimerCpp.h"

void TimerCpp::setTimeout(std::function<void()> func, int delay) {
	this->clear = false;
	std::thread t([=]() {
		if (this->clear) return;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		if (this->clear) return;
		func();
	});
	t.join();
}

void TimerCpp::setInterval(std::function<void()> func, int interval) {
	this->clear = false;
	std::thread t([=]() {
		while (true) {
			if (this->clear) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			if (this->clear) return;
			func();
		}
	});
	t.join();
}

void TimerCpp::stop() {
	this->clear = true;
}