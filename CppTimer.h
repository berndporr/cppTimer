#ifndef __CPP_TIMER_H_
#define __CPP_TIMER_H_

/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * (C) 2018, Bernd Porr <mail@bernporr.me.uk>
 **/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_MONOTONIC
#define SIG SIGRTMIN

class CppTimer {

private:

	timer_t timerid;
	struct sigevent sev;
	sigset_t mask;
	struct sigaction sa;
	struct itimerspec its;
		
	static void handler(int sig, siginfo_t *si, void *uc ) {
		CppTimer* t = reinterpret_cast<CppTimer *> (si->si_value.sival_ptr);
//		if (id==timerid) {
		t->run();
//		}
	}
	
public:
	CppTimer() {
		printf("Establishing handler for signal %d\n", SIG);
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
		sigemptyset(&sa.sa_mask);
		if (sigaction(SIG, &sa, NULL) == -1)
			exit(1);
		
		/* Create the timer */
		sev.sigev_notify = SIGEV_SIGNAL;
		sev.sigev_signo = SIG;
		sev.sigev_value.sival_ptr = this;
		if (timer_create(CLOCKID, &sev, &timerid) == -1)
			exit(1);
		
		printf("timer ID is 0x%lx\n", (long) timerid);
	};
	
	virtual ~CppTimer() {
	}
	
	void start() {
		/* Start the timer */
		
		// starts instantly
		its.it_value.tv_sec = 0;
		its.it_value.tv_nsec = 1;
		
		// and fires every 500ms
		its.it_interval.tv_sec = 0;
		its.it_interval.tv_nsec = 500000000;
		
		if (timer_settime(timerid, 0, &its, NULL) == -1)
			exit(1);
	}

	// is implemented by its children
	// this is exectuted once "start" has been triggered
	virtual void run() = 0;
	
};


#endif
