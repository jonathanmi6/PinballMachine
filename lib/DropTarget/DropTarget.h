#pragma once

#include "Servo.h"
#include "ScoringElement.h"

namespace Pinball::DropTGT
{   
namespace Constants
{
    const unsigned long RESET_TIME = 300;
    const unsigned long DROP_TIME = 2000;
    const int UP_POSITION = 100;
    const int DOWN_POSITION = 0;
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
        // void addScore();
        // int getScore();
        bool isDropped();
        bool isResetting();
};
}