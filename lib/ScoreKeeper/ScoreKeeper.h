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
}

class ScoreKeeper 
{
    private:
        unsigned long flagTime;
        int totalScore;
        bool maxedScore;
        MD_Parola cenDisplay;
        Adafruit_8x8matrix lDisplay;
        Adafruit_8x8matrix rDisplay;

    public:
        ScoreKeeper(MD_Parola &cMatrix, Adafruit_8x8matrix &lMatrix, Adafruit_8x8matrix &rMatrix);
        void init();
        void updateTotalScore(int totalScore);
        void updateScoreBoard();
        void setScoreBoard(int value);
        void resetScore();
        int getTotalScore();

        bool getResetSensor();
};
}