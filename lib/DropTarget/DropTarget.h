#pragma once

#include "Servo.h"
#include "ScoringElement.h"

namespace Pinball::DropTGT
{   
namespace Constants
{
    const unsigned long RESET_TIME = 400;
    const unsigned long DROP_TIME = 5000;
    const int UP_POSITION = 115;
    const int DOWN_POSITION = 5;
}

class DropTarget: public ScoringElement
{
    private:
        int servoPin;
        int switchPin;
        
        unsigned long timeDropped;

        bool droppedFlag;
        bool resetting;

        Servo TargetServo;

    public:
        DropTarget(int servoPin, int switchPin);
        void init();
        void update(unsigned long currTime);
        bool isDropped();
        bool isResetting();
        void stop();

        void resetBlocking(bool forceReset);
};
}