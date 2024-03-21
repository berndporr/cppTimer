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



class DemoTimer3 : public CppTimer {

	void timerEvent() {
		fprintf(stdout,"Booom!!!!!!\n");
	}
};



int main( int, const char**) {
	DemoTimer1 demoTimer1;
	demoTimer1.startms(250);
	DemoTimer2 demoTimer2;
	demoTimer2.startms(1000);
	DemoTimer3 demoTimer3;
	demoTimer3.startms(1000,ONESHOT);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	demoTimer1.stop();
	demoTimer2.stop();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	demoTimer1.startns(25000000);
	demoTimer2.startns(100000000);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	demoTimer1.stop();
	demoTimer2.stop();
	
	return 0;
}
