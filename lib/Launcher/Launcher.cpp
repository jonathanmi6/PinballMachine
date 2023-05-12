#include "Arduino.h"
#include "Launcher.h"
#include "constants.h"

namespace Pinball::Launch
{

Launcher::Launcher(int fak)
{
    launchFlag = false;
    resetCount = 0;
}

void Launcher::init()
{
    pinMode(Pinball::Constants::LAUNCH_SOLND_PIN, OUTPUT);
    pinMode(Pinball::Constants::LAUNCH_BTN_PIN, INPUT_PULLUP);
}

void Launcher::update(unsigned long currTime)
{
    if(getLaunchButton() && launchFlag == false)
    {
        launchFlag = true;
        trigTime = currTime;
        analogWrite(Pinball::Constants::LAUNCH_SOLND_PIN, getLaunchStrength());
        Serial.println("Launching at " + String(getLaunchStrength()));
    }
    else if(launchFlag == true && currTime > trigTime + Constants::LAUNCH_TIME)
    {
        Serial.println("done launching");
        analogWrite(Pinball::Constants::LAUNCH_SOLND_PIN, Constants::OFF_PERCENT);
        launchFlag = false;
        launched = true;
    }
}

int Launcher::getPotValue()
{
    return analogRead(Pinball::Constants::LAUNCH_POT_PIN);
}

void Launcher::resetLaunched()
{
    launched = false;
}

bool Launcher::getLaunched()
{
    return launched;
}

bool Launcher::getLaunchButton()
{
    return !digitalRead(Pinball::Constants::LAUNCH_BTN_PIN);
}

int Launcher::getLaunchStrength() // map analog input to reasonable pwm output
{
    return map(getPotValue(), 0, 1023, Constants::LAUNCH_PERCENT_MIN, Constants::LAUNCH_PERCENT_MAX);
}
}
