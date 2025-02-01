#ifndef __CPP_TIMER_CALLBACK
#define __CPP_TIMER_CALLBACK
#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>
#include <functional>

// This is a demo how to create a callback with std::function which allows
// calling methods in other classes by registering a lambda function!

class CppTimerCallback : public CppTimer {

public:

    using CallbackFunction = std::function<void(void)>;

    void registerEventCallback(CallbackFunction cf) {
	callbackFunction = cf;
    }
    
    void timerEvent() {
	if (nullptr != callbackFunction) {
	    callbackFunction();
	}
    }

private:
    CallbackFunction callbackFunction = nullptr;
};


#endif
