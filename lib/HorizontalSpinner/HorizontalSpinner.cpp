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
}

void HorizontalSpinner::update(unsigned long currTime)
{
    analogWrite(motorPin, Constants::SPIN_SPEED);
}

}
