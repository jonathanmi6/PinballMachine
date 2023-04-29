#pragma once

#include "ScoringElement.h"

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
    const double DROP_TGT_MULTIPLIER = 5;
    const double POP_BUMP_MULTIPLIER = 1;
    const double SLINGSHOT_MULTIPLIER = 1;
    const double VERT_SPINNER_MULTIPLIER = 0.5;
}

class ScoreKeeper 
{
    private:
        Difficulty difficulty;
        int totalScore;
        int elements;

    public:
        ScoreKeeper(Difficulty difficulty);
        void updateTotalScore(int totalScore);
        void updateScoreBoard();
        int getTotalScore();
};
}}