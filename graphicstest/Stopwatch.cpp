#include "Arduino.h"
class Stopwatch
{
private:
    unsigned long startTime;
    unsigned long stopTime;
    bool stopped;
    
public:
    Stopwatch() 
    {
        stopped = true;
        startTime = 0;
        stopTime = 0;
    }

    void Start()
    {
        if (stopped)
        {
            stopped = false;
            startTime = millis();
        }
    }

    void Stop()
    {
        stopped = true;
        stopTime = millis();
    }

    void Restart()
    {
        startTime = millis();
        stopTime = 0;
        stopped = false;
    }

    unsigned long Elapsed()
    {
        return (stopped) ? (stopTime - startTime) : (millis() - startTime);
    }

    bool IsRunning()
    {
        return !stopped;
    }
};




