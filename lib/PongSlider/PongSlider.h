#pragma once

#include "constants.h"
#include "Adafruit_MotorShield.h"

namespace Pinball::PongSlide
{
namespace Constants
{
    const unsigned long FLIP_TIME = 500;
    const int FLIP_PERCENT = 255;
    const int HOLD_PERCENT = 100;
    const int OFF_PERCENT = 0;
} 

class PongSlider
{
    public:
        enum Side
        {
            LEFT,
            HOLD,
            RIGHT,
        };

    private:
        unsigned long timeRightFlip;
        unsigned long timeLeftFlip;

        int sliderSpeedPercent;
        int sliderHoldPercent;
        
        bool leftFlipFlag;
        bool rightFlipFlag;

        bool slideRButton; 
        bool slideLButton;
        bool slideRLim;
        bool slideLLim;

        // Adafruit_MotorShield AFMS;
        Adafruit_DCMotor *sliderMotor;

    public:
        PongSlider(Adafruit_DCMotor *sliderMotor);
        void update(unsigned long currTime);
        void init();
        
        void slide(Side side);
        bool getFlipButton(Side side);
        Side getSlideDirection();

        void stop();
};
}
