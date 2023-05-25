#pragma once

#include "Arduino.h"
#include "constants.h"
#include "MD_MAX72xx.h"
#include "MD_Parola.h"
#include "Adafruit_LEDBackpack.h"


//score board controls the scoreboard

namespace Pinball::ScoreKeep {

namespace Constants
{
    const double DROP_TGT_MULTIPLIER = 500;
    const double POP_BUMP_MULTIPLIER = 50;
    const double SLINGSHOT_MULTIPLIER = 50;
    const double VERT_SPINNER_MULTIPLIER = 0.5;
    const double SLOT_SIDE_MULTIPLIER = 100;
    const double SLOT_CENTER_MULTIPLIER = 300;

    const int DISPLAY_SCROLL_SPEED = 40; //time between frames (smaller is faster)
}

class ScoreKeeper 
{
    private:
        unsigned long flagTime;
        int totalScore;
        bool maxedScore;
        MD_Parola &cenDisplay;
        Adafruit_8x8matrix &lDisplay;
        Adafruit_8x8matrix &rDisplay;



    public:
        ScoreKeeper(MD_Parola &cMatrix, Adafruit_8x8matrix &lMatrix, Adafruit_8x8matrix &rMatrix);
        ScoreKeeper(MD_Parola &cMatrix);
        void init();
        void updateTotalScore(int totalScore);
        void updateScoreBoard();
        void setScoreBoard(int value);
        void resetScore();
        int getTotalScore();

        bool getResetSensor();

        void printTextBlocking(String text, textPosition_t tPos = PA_CENTER, textEffect_t tEffect = PA_SCROLL_LEFT, int speed = Constants::DISPLAY_SCROLL_SPEED, int pauseTime = 0);
        void printTextNonBlocking(String text, textPosition_t tPos = PA_CENTER, textEffect_t tEffect = PA_SCROLL_LEFT, int speed = Constants::DISPLAY_SCROLL_SPEED, int pauseTime = 0);
};

namespace Sprites
{
    const uint8_t F_FBALL = 2;
    const uint8_t W_FBALL = 11;
    const uint8_t PROGMEM fireball[F_FBALL * W_FBALL] =  // fireball
    {
        0x7e, 0xab, 0x54, 0x28, 0x52, 0x24, 0x40, 0x18, 0x04, 0x10, 0x08,
        0x7e, 0xd5, 0x2a, 0x14, 0x24, 0x0a, 0x30, 0x04, 0x28, 0x08, 0x10,
    };
}

}