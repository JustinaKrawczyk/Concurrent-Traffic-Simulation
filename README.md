# Concurrent-Traffic-Simulation

traffic_simulation is a simulation of vehicles which are moving along streets in Paris and crossing intersections according to the current traffic light phase. This traffic simulation program makes use of a suitable and thread-safe communication protocol between vehicles and intersections by using concurrent programming structures such as mutexes, locks and message queues.

This simulation has been developed as a project task in the context of [Udacity Nanodegree Program C++](https://github.com/udacity/CppND-Program-a-Concurrent-Traffic-Simulation).

## Dependencies
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Build instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./traffic_simulation`.

## More information

* [Udacity github](https://github.com/udacity/CppND-Program-a-Concurrent-Traffic-Simulation)
