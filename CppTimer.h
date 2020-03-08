#ifndef __CPP_TIMER_H_
#define __CPP_TIMER_H_

/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * (C) 2020, Bernd Porr <mail@bernporr.me.uk>
 * 
 * This is inspired by the timer_create man page.
 **/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_MONOTONIC
#define SIG SIGRTMIN


/**
 * Enumeration of CppTimer types
 **/	
typedef enum cppTimerType_t{
	PERIODIC,
	ONESHOT
}cppTimerType_t;

/**
 * Timer class which repeatedly fires. It's wrapper around the
 * POSIX per-process timer.
 **/
class CppTimer {

public:
	/**
	 * Creates an instance of the timer and connects the
	 * signal handler to the timer.
	 **/
	CppTimer();

	/**
	 * Starts the timer. The timer fires first after
	 * the specified time in nanoseconds and then at
	 * that interval in PERIODIC mode. In ONESHOT mode
	 * the timer fires once after the specified time in
	 * nanoseconds.
	 **/
	virtual void start(long nanosecs, cppTimerType_t type = PERIODIC); 

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
		
	static void handler(int sig, siginfo_t *si, void *uc ) {
		(reinterpret_cast<CppTimer *> (si->si_value.sival_ptr))->timerEvent();
	}
};


#endif
