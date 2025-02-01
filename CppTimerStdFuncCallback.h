#ifndef __CPP_TIMER_CALLBACK
#define __CPP_TIMER_CALLBACK
#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>
#include <functional>

class CppTimerCallback : public CppTimer {

public:

    using CallbackFunction = std::function<void(void)>;

    void registerEventCallback(CallbackFunction cf) {
	callbackFunction = cf;
    }
    
    void timerEvent() {
	if (!(callbackFunction == nullptr)) {
	    callbackFunction();
	}
    }

private:
    CallbackFunction callbackFunction;
};


#endif
