#pragma once

#include "ScoringElement.h"
#include "constants.h"
#include "MD_MAX72xx.h"
#include "MD_Parola.h"


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

    public:
        ScoreKeeper(MD_Parola &cMatrix);
        void init();
        void updateTotalScore(int totalScore);
        void updateScoreBoard();
        void setScoreBoard(int value);
        void resetScore();
        int getTotalScore();

        bool getResetSensor();
};
}