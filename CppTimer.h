#ifndef __CPP_TIMER_H_
#define __CPP_TIMER_H_

/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * (C) 2020-2024, Bernd Porr <mail@bernporr.me.uk>
 * 
 * This is inspired by the timer_create man page.
 **/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <sys/timerfd.h>

/**
 * Enumeration of CppTimer types
 **/
enum cppTimerType_t
{
    PERIODIC,
    ONESHOT
};

/**
 * Timer class which repeatedly fires. It's wrapper around the
 * POSIX per-process timer.
 **/
class CppTimer
{

public:
    /**
     * Starts the timer. The timer fires first after
     * the specified time in nanoseconds and then at
     * that interval in PERIODIC mode. In ONESHOT mode
     * the timer fires once after the specified time in
     * nanoseconds.
     * @param nanosecs Time in nanoseconds
     * @param type Either PERIODIC or ONESHOT
     **/
    virtual void startns(long nanosecs, cppTimerType_t t = PERIODIC) {
	if (uthread.joinable()) uthread.join();
	if (running) return;
	timerType = t;
	if (fd < 0)
	    throw("Could not start timer");
	switch (timerType)
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

    /**
     * Starts the timer. The timer fires first after
     * the specified time in milliseconds and then at
     * that interval in PERIODIC mode. In ONESHOT mode
     * the timer fires once after the specified time in
     * milliseconds.
     * @param millisecs Time in milliseconds
     * @param type Either PERIODIC or ONESHOT
     **/
    virtual void startms(long millisecs, cppTimerType_t t = PERIODIC) {
	if (uthread.joinable()) uthread.join();
	if (running) return;
	timerType = t;
	if (fd < 0)
	    throw("Could not start timer");
	switch (timerType)
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

    /**
     * Stops the timer by disarming it. It can be re-started
     * with start().
     **/
    virtual void stop() {
	running = false;
	if (uthread.joinable()) uthread.join();
    }

    /**
     * Destructor disarms the timer, deletes it and
     * disconnect the signal handler.
     **/
    virtual ~CppTimer() {
	stop();
	close(fd);
    }

protected:
    /**
     * Abstract function which needs to be implemented by the children.
     * This is called every time the timer fires.
     **/
    virtual void timerEvent() = 0;

private:
    cppTimerType_t timerType;
    const int fd = timerfd_create(CLOCK_MONOTONIC, 0);
    struct itimerspec its;
    bool running = false;
    std::thread uthread;
    void worker() {
	running = true;
	while (running) {
	    uint64_t exp;
	    const long int s = read(fd, &exp, sizeof(uint64_t));
	    if (s != sizeof(uint64_t) ) {
		throw "Timer didn't work.";
	    }
	    timerEvent();
	    if (ONESHOT == timerType) running = false;
	}
	// disarm
	struct itimerspec itsnew;
	itsnew.it_value.tv_sec = 0;
	itsnew.it_value.tv_nsec = 0;
	itsnew.it_interval.tv_sec = 0;
	itsnew.it_interval.tv_nsec = 0;
	timerfd_settime(fd, 0, &itsnew, &its);
    }
};

#endif
