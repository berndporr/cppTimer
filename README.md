# CppThread
Generic C++ Thread for Linux and Windows

It's a wrapper aroung pthreads and Windows threads.

## Usage
Include CppThread.h in your program.

### Create the Thread class
```
class MyThread : public CppThread {

public:
	// override the constructor and add your init stuff
	MyThread(myArgs) {	    
	    // Your init code here!
	}

private:
	// implement run which is doing all the work
	void run() {
	     // Your magic worker here!
	}
	
private:
	// Your private data
};
```

### Run the Thread class
```
	MyThread myThread;
	myThread.start();
	myThread.join();
```

That's it. Enjoy!
