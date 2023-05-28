#include "Arduino.h"
#include "Servo.h"
#include "DropTarget.h"

namespace Pinball::DropTGT
{   
DropTarget::DropTarget(int servoPin, int switchPin)
{
    this->servoPin = servoPin;
    this->switchPin = switchPin;
    droppedFlag = false;
    resetting = false;
    setScore(0);
}

void DropTarget::init()
{    
    pinMode(switchPin, INPUT_PULLUP);
    TargetServo.attach(servoPin);
    TargetServo.write(Constants::DOWN_POSITION);
}

void DropTarget::update(unsigned long currTime)
{
    if(isDropped() && !droppedFlag) //one time trigger for when target first drops to initiate reset sequence
    {
        // Serial.println("Target dropped");
        timeDropped = millis(); //get time at which target was dropped
        droppedFlag = true;
        addScore();
    }
    else if(droppedFlag && !resetting) //bring the target up
    {
        if(currTime > timeDropped + Constants::DROP_TIME) //check if target down time has been reached
        {
            // Serial.println("Bringing target up");
            TargetServo.write(Constants::UP_POSITION);
            resetting = true;
        }
    }
    else if(droppedFlag && resetting) //reset servo arm
    {
        if(currTime > timeDropped + Constants::DROP_TIME + Constants::RESET_TIME) //bring arm back down when target reset, or when timeout reached 
        {
            // Serial.println("Bringing servo arm back down");
            TargetServo.write(Constants::DOWN_POSITION);
            droppedFlag = false;
            resetting = false;
        }
    }
}

bool DropTarget::isDropped()
{
    return !digitalRead(switchPin);
}

bool DropTarget::isResetting()
{
    return resetting;
}

}