#include <stdio.h>
#include "CppTimerCallback.h"
#include <unistd.h>


class Callback1 : public CppTimerCallback::Runnable {
	void run() {
		fprintf(stdout,"Bah! ");
		fflush(stdout);
	}
};


class Callback2 : public CppTimerCallback::Runnable {
	void run() {
		fprintf(stdout,"Buh! ");
		fflush(stdout);
	}
};


main( int argc, const char* argv[] ) {
	CppTimerCallback demoTimer1;
	Callback1 callback1;
	demoTimer1.registerEventRunnable(callback1);
	demoTimer1.start(2500000);
	CppTimerCallback demoTimer2;
	Callback2 callback2;
	demoTimer2.registerEventRunnable(callback2);
	demoTimer2.start(10000000);

	// do nothing and keep sleeping
	// we need the loop because the sleep
	// will be interrupted by the timers
	do {
		sleep(1);
	} while (1);
}
