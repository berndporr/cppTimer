#include <stdio.h>
#include "CppTimerStdFuncCallback.h"
#include <unistd.h>
#include <thread>

// Demo which shows how to register a callback via a lambda function.
// The method run() in the receiving classes below is called from the class CppTimerCallback.

class ReceiverClass1 {
public:
    void run() {
	fprintf(stdout,"Bah! ");
	fflush(stdout);
    }
};


class ReceiverClass2 {
public:
    void run() {
	fprintf(stdout,"BUH! \n");
	fflush(stdout);
    }
};


int main( int, const char**) {
	CppTimerCallback demoTimer1;
	ReceiverClass1 receiverClass1;
	demoTimer1.registerEventCallback([&receiverClass1](){receiverClass1.run();});
	demoTimer1.startns(77000000);

	CppTimerCallback demoTimer2;
	ReceiverClass2 receiverClass2;
	demoTimer2.registerEventCallback([&receiverClass2](){receiverClass2.run();});
	demoTimer2.startns(250000000);

	// do nothing and keep sleeping for 2 secs
	std::this_thread::sleep_for(std::chrono::seconds(2));

        demoTimer1.stop();
        demoTimer2.stop();

	printf("\n");

}
