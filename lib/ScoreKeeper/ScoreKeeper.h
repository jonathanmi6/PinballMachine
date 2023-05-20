#pragma once

#include "ScoringElement.h"
#include "TM1637.h"
#include "MD_MAX72xx.h"
#include "MD_Parola.h"
#include "constants.h"


//score board controls the scoreboard

namespace Pinball::ScoreKeep {
    
MD_Parola matrixDisplay(MD_MAX72XX::FC16_HW, Pinball::Constants::SB_DAT_PIN, Pinball::Constants::SB_CLK_PIN, Pinball::Constants::SB_CS_PIN, 4); //create matrix display obj

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

    public:
        ScoreKeeper(int a);
        void init();
        void updateTotalScore(int totalScore);
        void updateScoreBoard();
        void setScoreBoard(int value);
        void resetScore();
        int getTotalScore();

        bool getResetSensor();
};
}