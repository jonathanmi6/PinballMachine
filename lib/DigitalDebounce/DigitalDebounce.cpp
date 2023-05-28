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
    triggedFlag = false;
    waitForRelease = false;
    setScore(0);
}

bool DigitalDebounce::update(unsigned long currTime) //TODO: after flag is set high, it doesn't get cleared if input was just a bounce
{
    if(getInputRaw() && !triggedFlag) //sensor goes high, set flag to monitor
    {
        triggedFlag = true;
        trigTime = currTime;
    }
    else if(getInputRaw() && triggedFlag && !waitForRelease && currTime > trigTime + dbTime) //check if debounce time has elapsed and sensor still trigged
    {
        waitForRelease = true;
        addScore(); //need to only add score ONCE
        return true;
    }
    else if(getInputRaw() && triggedFlag && waitForRelease) //continue to return true while sensor is pressed
    {
        return true;
    }
    else if(!getInputRaw() && triggedFlag) //when released (after being pressed) reset flags, does not matter if db was reached or not
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
