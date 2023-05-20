#include "Arduino.h"
#include "ScoreKeeper.h"
#include "constants.h"
#include "MD_MAX72xx.h"
#include "MD_Parola.h"

namespace Pinball::ScoreKeep {
ScoreKeeper::ScoreKeeper(int a)
{
    totalScore = 0;
    maxedScore = false;
}

void ScoreKeeper::init()
{
    matrixDisplay.begin();
    matrixDisplay.setIntensity(15);
    matrixDisplay.displayClear();
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

    matrixDisplay.setTextAlignment(PA_CENTER);
    matrixDisplay.print(value);
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
