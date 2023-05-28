#include "HorizontalSpinner.h"

namespace Pinball::HSpin
{
HorizontalSpinner::HorizontalSpinner(int motorPin)
{
    this->motorPin = motorPin;
}

void HorizontalSpinner::init()
{
    pinMode(motorPin, OUTPUT);
    prevCurrTime = 0;
}

void HorizontalSpinner::update(unsigned long currTime)
{
    if(currTime > prevCurrTime)
    {
        analogWrite(motorPin, Constants::SPIN_SPEED);
    }
    else
    {
        analogWrite(motorPin, 0);
    }
    prevCurrTime = currTime;
}

}
