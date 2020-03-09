#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>
#include <time.h>
#include <thread>

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



int main( int argc, const char* argv[] ) {
	DemoTimer1 demoTimer1;
	demoTimer1.start(250000000);
	DemoTimer2 demoTimer2;
	demoTimer2.start(1000000000);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	demoTimer1.stop();
	demoTimer2.stop();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	demoTimer1.start(25000000);
	demoTimer2.start(100000000);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	demoTimer1.stop();
	demoTimer2.stop();
	
	return 0;
}
