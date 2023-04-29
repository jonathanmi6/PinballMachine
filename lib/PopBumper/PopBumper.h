#pragma once

#include "ScoringElement.h"

namespace Pinball::PopBump
{    
namespace Constants
{
    const unsigned long DELAY_TIME = 50;
    const unsigned long POP_TIME = 100;
    const unsigned long HOLD_TIME = 200;
    const int POP_PERCENT = 255;
    const int HOLD_PERCENT = 100;
    const int OFF_PERCENT = 0;
}
class PopBumper: public Pinball::ScoringElement
{
    private:
        int solenoidPin;
        int sensePin;

        unsigned long timeTriggered;

        bool triggeredFlag;
        bool dropping;

    public:
        PopBumper(int solenoidPin, int sensePin);
        void init();
        void update(unsigned long currTime);
        bool isTriggered();
};
    
} // namespace Pinball

