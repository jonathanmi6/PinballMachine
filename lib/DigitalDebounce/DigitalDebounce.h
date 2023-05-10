#pragma once

#include "Arduino.h"
#include "constants.h"
#include "ScoringElement.h"

namespace Pinball::DigDB
{

namespace Constants
{

}

class DigitalDebounce: ScoringElement
{
    private:
        int sensePin;
        int dbTime;
        bool triggedFlag;
        bool pullUp;
        unsigned long trigTime;

        bool getSensorRaw();

    public:
        DigitalDebounce(int sensePin, int dbTime, bool pullUp);
        void init();
        bool update(unsigned long currTime);
};
    
}
