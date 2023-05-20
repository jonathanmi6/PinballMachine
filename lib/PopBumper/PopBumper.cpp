#include "Arduino.h"
#include "ScoringElement.h"
#include "PopBumper.h"

namespace Pinball::PopBump
{   

PopBumper::PopBumper(int solenoidPin, int sensePin)
{
    this->solenoidPin = solenoidPin;
    this->sensePin = sensePin;
    setScore(0);
    triggeredFlag = false;
}

void PopBumper::init()
{
    pinMode(solenoidPin, OUTPUT);
    pinMode(sensePin, INPUT_PULLUP);
    setScore(0);
}

void PopBumper::update(unsigned long currTime)
{
    if(isTriggered() && !triggeredFlag)
    {
        // Serial.println("Pop Bumper Triggered");
        timeTriggered = currTime;
        triggeredFlag = true;
        addScore();
    }
    else if(triggeredFlag && currTime > timeTriggered + Constants::DELAY_TIME && currTime < timeTriggered + Constants::DELAY_TIME + Constants::POP_TIME) //pop bumper with full power after a delay
    {
        // Serial.println("Pop Bumper Popping with full power");
        analogWrite(solenoidPin, Constants::POP_PERCENT);
    }
    else if(triggeredFlag && currTime > timeTriggered + Constants::DELAY_TIME + Constants::POP_TIME && currTime < timeTriggered + Constants::DELAY_TIME + Constants::POP_TIME + Constants::HOLD_TIME) //switch to low duty cycle to hold solenoid to prevent overheat
    {
        // Serial.println("Pop bumper holding with low current");
        analogWrite(solenoidPin, Constants::HOLD_PERCENT);
    }
    else if(triggeredFlag && currTime > timeTriggered + Constants::DELAY_TIME + Constants::POP_TIME + Constants::HOLD_TIME) //release pop bumper
    {
        // Serial.println("Releasing pop bumper");
        analogWrite(solenoidPin, Constants::OFF_PERCENT);
        triggeredFlag = false;
    }
}

bool PopBumper::isTriggered()
{
    return !digitalRead(sensePin);
}

}