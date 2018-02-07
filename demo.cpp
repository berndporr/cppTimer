#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>


class DemoTimer1 : public CppTimer {

	void timerEvent() {
		fprintf(stdout,"Buh! ");
		fflush(stdout);
	}
};


class DemoTimer2 : public CppTimer {

	void timerEvent() {
		fprintf(stdout,"Bah!!!!!!\n");
	}
};


main( int argc, const char* argv[] ) {
	DemoTimer1 demoTimer1;
	demoTimer1.start(250000000);
	DemoTimer2 demoTimer2;
	demoTimer2.start(1000000000);

	// do nothing and keep sleeping
	// we need the loop because the sleep
	// will be interrupted by the timers
	do {
		sleep(1);
	} while (1);
}
