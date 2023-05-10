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
}

bool DigitalDebounce::update(unsigned long currTime)
{
    if(getSensorRaw() && triggedFlag == false) //sensor goes high, set flag to monitor
    {
        triggedFlag = true;
        trigTime = currTime;
    }
    else if(getSensorRaw() && triggedFlag == true && currTime > trigTime + dbTime) 
    {
        //sensor must read high for debounce time before confirmed
        addScore();
        triggedFlag = false; //reset flag
        return true;
    }

    return false;
}

bool DigitalDebounce::getSensorRaw()
{
    if(pullUp)
    {
        return !digitalRead(sensePin);
    }
    else
    {
        return digitalRead(sensePin);
    }
}

}
