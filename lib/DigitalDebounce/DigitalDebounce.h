#pragma once

#include "Arduino.h"
#include "constants.h"
#include "ScoringElement.h"
#include "ScoringElement.h"

namespace Pinball::DigDB
{

namespace Constants
{

}

class DigitalDebounce : public Pinball::ScoringElement
{
    private:
        int sensePin;
        int dbTime;
        bool triggedFlag;
        bool waitForRelease;
        bool pullUp;

        bool filtState;
        unsigned long trigTime;

        bool getInputRaw();

    public:
        DigitalDebounce(int sensePin, int dbTime, bool pullUp);
        void init();
        bool update(unsigned long currTime);

        bool getFiltState();
};
    
}
