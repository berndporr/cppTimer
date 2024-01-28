#include "CppTimer.h"
#include <sys/timerfd.h>

/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * (C) 2020-2024, Bernd Porr <mail@bernporr.me.uk>
 * 
 * This is inspired by the timerfd_create man page.
 **/

void CppTimer::startns(long nanosecs, cppTimerType_t type)
{
	if (running) return;
	fd = timerfd_create(CLOCK_MONOTONIC, 0);
	if (fd < 0)
		throw("Could not start timer");
	switch (type)
	{
	case (PERIODIC):
		//starts after specified period of nanoseconds
		its.it_value.tv_sec = nanosecs / 1000000000;
		its.it_value.tv_nsec = nanosecs % 1000000000;
		its.it_interval.tv_sec = nanosecs / 1000000000;
		its.it_interval.tv_nsec = nanosecs % 1000000000;
		break;
	case (ONESHOT):
		//fires once after specified period of nanoseconds
		its.it_value.tv_sec = nanosecs / 1000000000;
		its.it_value.tv_nsec = nanosecs % 1000000000;
		its.it_interval.tv_sec = 0;
		its.it_interval.tv_nsec = 0;
		break;
	}
	if (timerfd_settime(fd, 0, &its, NULL) == -1)
		throw("Could not start timer");
	uthread = std::thread(&CppTimer::worker,this);
}

void CppTimer::startms(long millisecs, cppTimerType_t type)
{
	if (running) return;
	fd = timerfd_create(CLOCK_MONOTONIC, 0);
	if (fd < 0)
		throw("Could not start timer");
	switch (type)
	{
	case (PERIODIC):
		//starts after specified period of milliseconds
		its.it_value.tv_sec = millisecs / 1000;
		its.it_value.tv_nsec = (millisecs % 1000) * 1000000;
		its.it_interval.tv_sec = millisecs / 1000;
		its.it_interval.tv_nsec = (millisecs % 1000) * 1000000;
		break;
	case (ONESHOT):
		//fires once after specified period of milliseconds
		its.it_value.tv_sec = millisecs / 1000;
		its.it_value.tv_nsec = (millisecs % 1000) * 1000000;
		its.it_interval.tv_sec = 0;
		its.it_interval.tv_nsec = 0;
		break;
	}
	if (timerfd_settime(fd, 0, &its, NULL) == -1)
		throw("Could not start timer");
	uthread = std::thread(&CppTimer::worker,this);
}

void CppTimer::worker() {
	running = true;
	while (running) {
		uint64_t exp;
		const long int s = read(fd, &exp, sizeof(uint64_t));
		if (s != sizeof(uint64_t) ) {
			running = false;
			return;
		}
		timerEvent();
	}
	// disarm
	struct itimerspec itsnew;
	itsnew.it_value.tv_sec = 0;
	itsnew.it_value.tv_nsec = 0;
	itsnew.it_interval.tv_sec = 0;
	itsnew.it_interval.tv_nsec = 0;
	timerfd_settime(fd, 0, &itsnew, &its);
	close(fd);
	fd = -1;
}

void CppTimer::stop()
{
	if (!running) return;
	running = false;
	uthread.join();
}

CppTimer::~CppTimer()
{
	stop();
}
