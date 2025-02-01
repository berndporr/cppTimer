#ifndef __CPP_TIMER_CALLBACK
#define __CPP_TIMER_CALLBACK
#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>
#include <vector>

// Demo which creates a callback interface as the abstract class "Runnable".
// This then allows to register a callback.

class CppTimerCallback : public CppTimer {
    
public:
    class Runnable {
    public:
	virtual void run() = 0;
    };
    
    void registerEventRunnable(Runnable &h) {
	cppTimerEventRunnables.push_back(&h);
    }
    
    void timerEvent() {
	for(auto & r : cppTimerEventRunnables) {
	    r->run();
	}
    }

private:
    std::vector<Runnable*> cppTimerEventRunnables;
};


#endif
