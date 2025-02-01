#ifndef __CPP_TIMER_CALLBACK
#define __CPP_TIMER_CALLBACK
#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>

// Demo which creates a callback interface as the abstract class "Runnable".
// This then allows to register a callback.

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
