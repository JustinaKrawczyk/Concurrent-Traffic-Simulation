#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <queue>
#include <algorithm>

#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

enum class TrafficLightPhase{red, green}; 

template <class T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);

private:
    std::deque<T> _queue;

    std::condition_variable _msgqueuecond;
    std::mutex _msgqueuemtx;
    
};
 

class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight();
    ~TrafficLight();

    // getters / setters
    TrafficLightPhase getCurrentPhase();

    // typical behaviour methods
    void waitForGreen();
    void simulate();

private:
    // typical behaviour methods
    void cycleThroughPhases();

    std::shared_ptr<MessageQueue<TrafficLightPhase>> _msgqueuetrafficlightphase;
    TrafficLightPhase _currentPhase;
    

    std::condition_variable _condition;
    std::mutex _mutex; 
};

#endif