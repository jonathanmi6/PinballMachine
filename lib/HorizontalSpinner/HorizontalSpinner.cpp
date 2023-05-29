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

void HorizontalSpinner::run()
{
    analogWrite(motorPin, Constants::SPIN_SPEED);
}
void HorizontalSpinner::stop()
{
    analogWrite(motorPin, 0);
}
}
