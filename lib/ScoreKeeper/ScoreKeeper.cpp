#include "Arduino.h"
#include "ScoreKeeper.h"

namespace Pinball::ScoreKeep {
ScoreKeeper::ScoreKeeper(Difficulty difficulty)
{
    this->difficulty = difficulty;
    totalScore = 0;
}

void ScoreKeeper::updateTotalScore(int totalScore)
{
    this->totalScore = totalScore;
}

void ScoreKeeper::updateScoreBoard() //update display of score
{

}

int ScoreKeeper::getTotalScore()
{
    return totalScore;
}
}
