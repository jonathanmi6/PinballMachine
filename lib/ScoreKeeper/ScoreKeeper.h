#pragma once

#include "ScoringElement.h"
#include "TM1637.h"

//score board controls the scoreboard

namespace Pinball {
enum Difficulty
{
    EASY,
    MEDIUM,
    HARD,
};

namespace ScoreKeep {   

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
        Difficulty difficulty;
        unsigned long flagTime;
        int totalScore;
        bool maxedScore;

    public:
        ScoreKeeper(Difficulty difficulty);
        void init();
        void updateTotalScore(int totalScore);
        void updateScoreBoard();
        void clearScoreBoard();
        void scoreBoardOff();
        void setScoreBoard(int value);
        void resetScore();
        int getTotalScore();

        bool getResetSensor();
};
}}