#include <stdio.h>
#include "CppTimerCallback.h"
#include <unistd.h>
#include <thread>

class Callback1 : public CppTimerCallback::Runnable {
	void run() {
		fprintf(stdout,"Bah! ");
		fflush(stdout);
	}
};


class Callback2 : public CppTimerCallback::Runnable {
	void run() {
		fprintf(stdout,"Buh! \n");
		fflush(stdout);
	}
};


int main( int, const char**) {
	CppTimerCallback demoTimer1;
	Callback1 callback1;
	demoTimer1.registerEventRunnable(callback1);
	demoTimer1.start(2500000);
	CppTimerCallback demoTimer2;
	Callback2 callback2;
	demoTimer2.registerEventRunnable(callback2);
	demoTimer2.start(10000000);

	// do nothing and keep sleeping for 2 secs
	std::this_thread::sleep_for(std::chrono::seconds(2));
	
	demoTimer1.unregisterEventRunnable();
        demoTimer1.stop();
	
	demoTimer2.unregisterEventRunnable();
        demoTimer2.stop();
	
	printf("\n");

}
