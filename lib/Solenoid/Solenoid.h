#pragma once

#include "Arduino.h"

class Solenoid
{
    private:
        int solenoidPin;
        int instTime; //ms
        int instPercent;
        int holdTime;
        int holdPercent;

    public:
        Solenoid(int solenoidPin);
        
};