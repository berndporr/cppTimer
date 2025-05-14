# CppTimer
Generic C++ Timer for Linux

It's a wrapper around the Linux timers. The timer used is timerfd
which is a file descriptor which blocks till a certain time has
elapsed. This means it puts a thread to sleep till it unblocks
which is the general approach for Linux events.
There are three ways of using
the timer: 
 1. by overloading the `timerEvent()` method in the `CppTimer` class itself (fastest)
 2. by registering a callback class called `Runnable` with an overloaded `run()` method.
 3. by registering a lambda function

## Installation
```
cmake .
make
sudo make install
```

## Usage (overloading the timer event)
The doxygen generated online docs are here: https://berndporr.github.io/cppTimer/

Include `CppTimer.h` in your program. That's it.
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
The timer is programmed in nanoseconds:
```
	MyTimer myTimer;
	// every 500000ns
	myTimer.startns(500000);
```
or milliseconds:
```
	// every 200ms
	myTimer.startms(200);
```
As soon as start returns the timer fires instantly and
then at the specified interval.

### Demo program

To run `demo.cpp` just do `cmake .`, `make` and then `./demo`.

## Callback interface version

Instead of overloading the `run()` method in the timer class you can
overload the `run()` method in the `Runnable` class and then register
this class with the timer class.  Check out `demo_runnable` which
demonstrates how to use this method.

## Callback via lambda function

Here, the callback is established with the help of a lambda function
instead of a callback interface. This allows direct registering
of a method of the receiving class but one needs to get used to the
lambda function syntax. It also allows more flexibility in doing
some work inside of the lambda function and it's entirely pointer-free.

## Unit tests

Run:

```
ctest
```


That's it. Enjoy!
