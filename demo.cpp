#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>


class DemoTimer1 : public CppTimer {

	void timerEvent() {
		printf("Buh!\n");
	}
};


class DemoTimer2 : public CppTimer {

	void timerEvent() {
		printf("Bah!\n");
	}
};


main( int argc, const char* argv[] ) {
	DemoTimer1 demoTimer1;
	demoTimer1.start(500);
	DemoTimer2 demoTimer2;
	demoTimer2.start(250);
	do {
		sleep(1);
	} while (1);
}
