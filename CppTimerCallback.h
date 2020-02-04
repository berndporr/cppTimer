#ifndef __CPP_TIMER_CALLBACK
#define __CPP_TIMER_CALLBACK
#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>


class CppTimerCallback : public CppTimer {

public:
	class Runnable {
	public:
		virtual void run() = 0;
	};

	void registerEventRunnable(Runnable &h) {
		cppTimerEventRunnable = &h;
	}

	void unregisterEventRunnable() {
		cppTimerEventRunnable = NULL;
	}
	
        void timerEvent() {
		if (cppTimerEventRunnable) {
			cppTimerEventRunnable->run();
		}
	}

private:
	Runnable* cppTimerEventRunnable = NULL;

};


#endif
