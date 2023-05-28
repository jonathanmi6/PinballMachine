#pragma once

#include "Arduino.h"
#include "ScoringElement.h"
#include "constants.h"

namespace Pinball::HSpin
{
namespace Constants
{
    const int SPIN_SPEED = 255;
}

class HorizontalSpinner : public Pinball::ScoringElement
{
    private:
        int motorPin;
        unsigned long prevCurrTime;

    public:
        HorizontalSpinner(int motorPin);
        void init();
        void update(unsigned long currTime);
};

    
}


