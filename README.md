# CppTimer
Generic C++ Timer for Linux

It's a wrapper around the Linux timers

## Usage
Include CppTimer.h in your program.

### Create the Timer class
```
class MyTimer : public CppTimer {

	void timerEvent() {
		// your timer event code here
	}
};
```

### Run the Timer class
```
	MyTimer myTimer;
	// every 500ms
	myTimer.start(500);
```

That's it. Enjoy!
