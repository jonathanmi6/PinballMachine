#pragma once

#include "ScoreKeeper.h"

namespace Pinball::PongSlide
{   
namespace Constants
{
    const unsigned long FLIP_TIME = 100;
    const int FLIP_PERCENT = 255;
    const int HOLD_PERCENT = 100;
    const int OFF_PERCENT = 0;
} 

class PongSlider
{
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

    public:
        PongSlider(Difficulty difficulty);
        void update(unsigned long currTime);
        void init();
        
        void flip(Side side);
        void slide(Side side);
        bool getFlipButton(Side side);
        Side getSlideDirection();
        
        
};

}