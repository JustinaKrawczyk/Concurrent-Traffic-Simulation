#include <iostream>
#include <random>
#include <future>
#include <stdlib.h>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

 
template <typename T>
T MessageQueue<T>::receive()
{
    std::unique_lock<std::mutex> ulock(_msgqueuemtx);
    _msgqueuecond.wait(ulock, [this]{return !_queue.empty();});

    T msg = std::move(_queue.back());
    _queue.pop_back();

    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    std::lock_guard<std::mutex> lockguard(_msgqueuemtx);
    _queue.push_back(std::move(msg));

    _msgqueuecond.notify_one();
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
    _msgqueuetrafficlightphase = std::make_shared<MessageQueue<TrafficLightPhase>>();
}

TrafficLight::~TrafficLight(){

}

void TrafficLight::waitForGreen()
{
    while(true){
       TrafficLightPhase lightphase = _msgqueuetrafficlightphase->receive();
       
       if(lightphase == TrafficLightPhase::green){
           return; 
       }
    }
    
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
   // using thread queue in base class 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this)); 
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    /*std::vector<std::future<void>> futures;*/

    // Calculate a random number between 4 to 6
    srand(time(NULL));
   
    // Initialize cycle duration
    double cycleDuration =  rand()%6000+4000; // duration of a single simulation cycle in ms
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    // Initialize lastUpdate time to now
    lastUpdate = std::chrono::system_clock::now();
    while (true)
    {
        // sleep for 1ms
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

         // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeSinceLastUpdate >= cycleDuration)
        {
            // update traffic light
            if(TrafficLightPhase::red == _currentPhase){
                _currentPhase = TrafficLightPhase::green;
            }else{
                _currentPhase = TrafficLightPhase::red;
            }

            // send an update to the message queue using move semantics 
            //futures.emplace_back(&MessageQueue<TrafficLightPhase>::send, _msgqueuetrafficlightphase, std::move(_currentPhase));
            _msgqueuetrafficlightphase->send(std::move(_currentPhase));
      
            // reset stop watch for next cycle
            lastUpdate = std::chrono::system_clock::now();
            cycleDuration =  rand()%6000+4000;
        }
    }
  
    /*std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });*/

    
}
