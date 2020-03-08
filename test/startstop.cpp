#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>
#include <time.h>
#include <thread>

class DemoTimer1 : public CppTimer {

	void timerEvent() {
		fprintf(stdout,".");
		fflush(stdout);
	}
};


int main( int argc, const char* argv[] ) {
	DemoTimer1 demoTimer1;
	demoTimer1.start(250000000);

	// do nothing and keep sleeping
	// we need the loop because the sleep
	// will be interrupted by the timers

	std::this_thread::sleep_for(std::chrono::seconds(2));

	demoTimer1.stop();
	
	demoTimer1.start(25000000);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	demoTimer1.stop();
	
	fprintf(stdout,"\n");

	return 0;
}
