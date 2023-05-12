#include "Arduino.h"
#include "ScoreKeeper.h"
#include "constants.h"

TM1637 scoreDisplay(Pinball::Constants::SB_CLK_PIN, Pinball::Constants::SB_DIO_PIN);

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

void ScoreKeeper::resetScore()
{
    totalScore = 0;
}

int ScoreKeeper::getTotalScore()
{
    return totalScore;
}

bool ScoreKeeper::getResetSensor()
{
    //debounce?
    return digitalRead(Pinball::Constants::GAME_RST_PIN);
}
}
