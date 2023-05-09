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

    const int SEGMENT_DECIMAL[10] = {3, 159, 33, 13, 153, 73, 65, 31, 1, 35}; //0->9 common anode, index starting with a = QA
    //2nd column is inverted for common anode
    //0: 11111100 // 00000011
    //1: 01100000 // 10011111
    //2: 11011110 // 00100001
    //3: 11110010 // 00001101
    //4: 01100110 // 10011001
    //5: 10110110 // 01001001
    //6: 10111110 // 01000001
    //7: 11100000 // 00011111
    //8: 11111110 // 00000001
    //9: 11100110 // 00011001
}

class ScoreKeeper 
{
    private:
        Difficulty difficulty;
        unsigned long flagTime;
        int totalScore;
        int elements;
        int onesDisplay;
        int tensDisplay;
        int hunsDisplay;
        int thdsDisplay;
        int count;
        bool maxedScore;
        bool scribing;

    public:
        ScoreKeeper(Difficulty difficulty);
        void init();
        void updateTotalScore(int totalScore);
        void updateScoreBoard(unsigned long currTime);
        void clearScoreBoard();
        void scoreBoardOff();
        void setScoreBoard(int value, unsigned long currTime);
        void writeDigit(int digitPin, int value);
        int getTotalScore();
};
}}