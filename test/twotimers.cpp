#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>
#include <time.h>
#include <thread>

class DemoTimer1 : public CppTimer {
public:
	void timerEvent() {
		counter++;
		fprintf(stdout,"1");
		fflush(stdout);
	}
	void startns(long nanosecs) {
		counter = 0;
		CppTimer::startns(nanosecs);
	}
	int getCounter() {return counter;}
private:
	int counter = 0;
};


class DemoTimer2 : public CppTimer {
public:
	DemoTimer1* demoTimer1;
	DemoTimer2(DemoTimer1* dt1) : CppTimer() {
		demoTimer1 = dt1;
	}
	void timerEvent() {
		fprintf(stdout,"2\n");
		if (0 == demoTimer1->getCounter()) {
			const char tmp[] = "BUG! Timer one hasn't fired.\n";
			fprintf(stderr,tmp);
			throw tmp;
		}
	}
};



int main( int, const char**) {
	DemoTimer1 demoTimer1;
	demoTimer1.startns(100000000);
	DemoTimer2 demoTimer2(&demoTimer1);
	demoTimer2.startns(200000000);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	demoTimer1.stop();
	demoTimer2.stop();
	
	demoTimer1.startns(25000000);
	demoTimer2.startns(100000000);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	demoTimer1.stop();
	demoTimer2.stop();
	
	return 0;
}
