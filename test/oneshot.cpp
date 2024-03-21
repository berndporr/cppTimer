#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>
#include <time.h>
#include <thread>

class DemoTimer1 : public CppTimer {

public:
    bool hasFired = false;
    void timerEvent() {
	fprintf(stdout,".");
	fflush(stdout);
	hasFired = true;
    }
};


int main( int, const char** ) {
	DemoTimer1 demoTimer1;
	demoTimer1.startns(0.5E9,ONESHOT);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	if (!demoTimer1.hasFired) {
	    char tmp[] = "nanosec Timer has not fired";
	    printf("%s\n",tmp);
	    fflush(stdout);
	    throw tmp;
	}

	demoTimer1.hasFired = false;

	demoTimer1.startms(0.5E3,ONESHOT);

	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	if (!demoTimer1.hasFired) {
	    char tmp[] = "ms timer has not fired";
	    printf("%s\n",tmp);
	    fflush(stdout);
	    throw tmp;
	}

	return 0;
}
