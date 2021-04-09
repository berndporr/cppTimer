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


int main( int, const char** ) {
	DemoTimer1 demoTimer1;
	demoTimer1.startms(500);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	demoTimer1.stop();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	demoTimer1.startms(1500);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	demoTimer1.stop();
	
	fprintf(stdout,"\n");

	return 0;
}
