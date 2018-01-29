#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>


class DemoTimer : public CppTimer {

	void run() {
		printf("Buh!\n");
	}
};


main( int argc, const char* argv[] ) {
	DemoTimer demoTimer;
	demoTimer.start();
	do {
		sleep(1);
	} while (1);
}
