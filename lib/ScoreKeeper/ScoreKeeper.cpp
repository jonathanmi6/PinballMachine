#include "Arduino.h"
#include "ScoreKeeper.h"
#include "constants.h"
#include "MD_MAX72xx.h"
#include "MD_Parola.h"

namespace Pinball::ScoreKeep {
ScoreKeeper::ScoreKeeper(MD_Parola &cMatrix) : cenDisplay{cMatrix} //member intiailizer list intializes the object
{
    totalScore = 0;
    maxedScore = false;
}

void ScoreKeeper::init()
{
    cenDisplay.begin();
    cenDisplay.setIntensity(15);
    cenDisplay.displayClear();
}
void ScoreKeeper::updateTotalScore(int totalScore)
{
    this->totalScore = totalScore;
}

void ScoreKeeper::updateScoreBoard() //update display of score
{
    setScoreBoard(totalScore);
}

void ScoreKeeper::setScoreBoard(int value)
{
    if(value > 9999) //catch overflow
    {
        value = 9999;
        maxedScore = true;
    }

    cenDisplay.setTextAlignment(PA_CENTER);
    cenDisplay.print(value);
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
