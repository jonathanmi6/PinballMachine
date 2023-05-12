#include "Arduino.h"
#include "ScoreKeeper.h"
#include "constants.h"

TM1637 scoreDisplay(Pinball::Constants::SB_CLK, Pinball::Constants::SB_DIO);

namespace Pinball::ScoreKeep {
ScoreKeeper::ScoreKeeper(Difficulty difficulty)
{
    this->difficulty = difficulty;
    totalScore = 0;
    maxedScore = false;
}

void ScoreKeeper::init()
{
    scoreDisplay.begin();
    scoreDisplay.setBrightness(4);
    scoreDisplay.colonOff();
    clearScoreBoard();
}

void ScoreKeeper::updateTotalScore(int totalScore)
{
    this->totalScore = totalScore;
}

void ScoreKeeper::updateScoreBoard() //update display of score
{
    setScoreBoard(totalScore);
}

void ScoreKeeper::clearScoreBoard()
{
    scoreDisplay.display(0000);
}

void ScoreKeeper::scoreBoardOff()
{
    scoreDisplay.clearScreen();
}

void ScoreKeeper::setScoreBoard(int value) //need to call at least 4 loops to work (and also delay between 4 cycles?)
{
    if(value > 9999) //catch overflow
    {
        value = 9999;
        maxedScore = true;
    }
    scoreDisplay.display(value);
}

int ScoreKeeper::getTotalScore()
{
    return totalScore;
}
}
