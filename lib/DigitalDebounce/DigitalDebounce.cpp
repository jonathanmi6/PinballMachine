#include "Arduino.h"
#include "DigitalDebounce.h"
#include "constants.h"


namespace Pinball::DigDB
{
DigitalDebounce::DigitalDebounce(int sensePin, int dbTime, bool pullUp)
{
    this->sensePin = sensePin;
    this->dbTime = dbTime;
    this->pullUp = pullUp;
}

void DigitalDebounce::init()
{
    if(pullUp)
    {
        pinMode(sensePin, INPUT_PULLUP);
    }
    else
    {
        pinMode(sensePin, INPUT);
    }
    triggedFlag == false;
    waitForRelease == false;
    setScore(0);
}

bool DigitalDebounce::update(unsigned long currTime)
{
    if(getInputRaw() && triggedFlag == false) //sensor goes high, set flag to monitor
    {
        triggedFlag = true;
        trigTime = currTime;
    }
    else if(getInputRaw() && triggedFlag == true && waitForRelease == false && currTime > trigTime + dbTime) 
    {
        waitForRelease == true;
        addScore(); //need to only add score ONCE
        return true;
    }
    else if(getInputRaw() && triggedFlag == true && waitForRelease == true) //so that update continues to return true while sensor is triggered
    {
        return true;
    }
    else if(!getInputRaw() && triggedFlag == true && waitForRelease == true)
    {
        //sensor is released
        triggedFlag = false;
        waitForRelease = false; //reset flags
        return false;
    }

    return false; 
}

bool DigitalDebounce::getInputRaw()
{
    if(pullUp)
    {
        return !digitalRead(sensePin); //active LOW
    }
    else
    {
        return digitalRead(sensePin); //active HIGH
    }
}

}
