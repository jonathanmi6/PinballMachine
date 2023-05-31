#include "Arduino.h"
#include "DigitalDebounce.h"
#include "constants.h"


namespace Pinball::DigDB
{
DigitalDebounce::DigitalDebounce(int sensePin, int dbTime, bool pullUp, bool activeLow)
{
    this->sensePin = sensePin;
    this->dbTime = dbTime;
    this->pullUp = pullUp;
    this->activeLow = activeLow;
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
    filtState = false;
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
        // Serial.println("sensor trig flag");
    }
    else if(getInputRaw() && triggedFlag && !waitForRelease && currTime > trigTime + dbTime) //check if debounce time has elapsed and sensor still trigged
    {
        waitForRelease = true;
        addScore(); //need to only add score ONCE
        // Serial.println("Debounced time reached");
        filtState = true;
        return true;
    }
    else if(getInputRaw() && triggedFlag && waitForRelease) //continue to return true while sensor is pressed
    {
        // Serial.println("Active");
        filtState = true;
        return true;
    }
    else if(!getInputRaw() && triggedFlag) //when released (after being pressed) reset flags, does not matter if db was reached or not
    {
        //sensor is released
        triggedFlag = false;
        waitForRelease = false; //reset flags
        // Serial.println("Released");
        filtState = false;
        return false;
    }

    filtState = false;
    return false; 
}

bool DigitalDebounce::getFiltState()
{
    return filtState;
}

bool DigitalDebounce::getInputRaw()
{
    if(activeLow)
    {
        return !digitalRead(sensePin); //active LOW
    }
    else
    {
        return digitalRead(sensePin); //active HIGH
    }
}

}
