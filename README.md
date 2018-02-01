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
where you override `timerEvent` with your function.

### Run the Timer class
The timer is programmed in nanoseconds.
```
	MyTimer myTimer;
	// every 500000ns
	myTimer.start(500000);
```
As soon as start returns the timer fires instantly and
then at the specified interval.

### Demo program

To run `demo.cpp` just do `cmake .`, `make` and then `./demo`.



That's it. Enjoy!
