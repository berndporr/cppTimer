# CppTimer
Generic C++ Timer for Linux

It's a wrapper around the Linux timers. There are two ways of using
the timer: by overloading the `timerEvent()` method in the `CppTimer` class
itself (fastest) or by registering a callback class called `Runnable`
with an overloaded `run()` method.

## Installation
```
cmake .
make
sudo make install
```

## Usage (overloading the timer event)
Include CppTimer.h in your program and link the static library `libcpptimer.a`
to your project:

```
TARGET_LINK_LIBRARIES(your_project_title cpptimer rt)
```

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

## Callback version

Instead of overloading the `run()` method in the timer class you can
overload the `run()` method in the `Runnable` class and then register
this class with the timer class.  Check out `demo_runnable` which
demonstrates how to use this method.

## Unit tests

Run:

```
ctest
```


That's it. Enjoy!
