#ifndef __CPP_TIMER_H_
#define __CPP_TIMER_H_

/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * (C) 2020-2021, Bernd Porr <mail@bernporr.me.uk>
 * 
 * This is inspired by the timer_create man page.
 **/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_MONOTONIC

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
	 * Creates an instance of the timer and connects the
	 * signal handler to the timer. The default signal which
	 * is being used is SIGRTMIN but can be changed to other
	 * signals if other processes / threads use them.
	 * @param signo The signal used by the timer.
	 **/
	CppTimer(const int signo = SIGRTMIN);

	/**
	 * Starts the timer. The timer fires first after
	 * the specified time in nanoseconds and then at
	 * that interval in PERIODIC mode. In ONESHOT mode
	 * the timer fires once after the specified time in
	 * nanoseconds.
	 * @param nanosecs Time in nanoseconds
	 * @param type Either PERIODIC or ONESHOT
	 **/
	virtual void startns(long nanosecs, cppTimerType_t type = PERIODIC);

	/**
	 * Starts the timer. The timer fires first after
	 * the specified time in milliseconds and then at
	 * that interval in PERIODIC mode. In ONESHOT mode
	 * the timer fires once after the specified time in
	 * milliseconds.
	 * @param millisecs Time in milliseconds
	 * @param type Either PERIODIC or ONESHOT
	 **/
	virtual void startms(long millisecs, cppTimerType_t type = PERIODIC);

	/**
	* Stops the timer by disarming it. It can be re-started
	* with start().
	**/
	virtual void stop();

	/**
	 * Destructor disarms the timer, deletes it and
	 * disconnect the signal handler.
	 **/
	virtual ~CppTimer();

protected:
	/**
	 * Abstract function which needs to be implemented by the children.
	 * This is called every time the timer fires.
	 **/
	virtual void timerEvent() = 0;

private:
	timer_t timerid = 0;
	struct sigevent sev;
	struct sigaction sa;
	struct itimerspec its;

	inline static void handler(int, siginfo_t *si, void *)
	{
		(reinterpret_cast<CppTimer *>(si->si_value.sival_ptr))->timerEvent();
	}
};

#endif
