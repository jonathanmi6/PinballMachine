#include "ScoreKeeper.h"

namespace Pinball::ScoreKeep {
ScoreKeeper::ScoreKeeper(MD_Parola &cMatrix, Adafruit_8x8matrix &lMatrix, Adafruit_8x8matrix &rMatrix) : cenDisplay{cMatrix}, lDisplay{lMatrix}, rDisplay{rMatrix} //member intiailizer list intializes the object
{
    totalScore = 0;
    maxedScore = false;
}

ScoreKeeper::ScoreKeeper(MD_Parola &cMatrix) : cenDisplay{cMatrix} //member intiailizer list intializes the object
{
    totalScore = 0;
    maxedScore = false;
}

void ScoreKeeper::init()
{
    cenDisplay.begin();
    cenDisplay.setIntensity(3); //brightness from 0->15
    cenDisplay.displayClear();

    // lDisplay.begin(Pinball::Constants::SB_L_MATRIX_I2C_ADDR);
    // rDisplay.begin(Pinball::Constants::SB_R_MATRIX_I2C_ADDR);
    // lDisplay.setBrightness(15); //brightness from 0->15
    // rDisplay.setBrightness(15);
    // lDisplay.clear();
    // rDisplay.clear();
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
    if(value > 99999) //catch overflow
    {
        value = 99999;
        maxedScore = true;
    }

    // cenDisplay.displayClear();
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

void ScoreKeeper::printTextBlocking(String text, textPosition_t tPos = PA_CENTER, textEffect_t tEffect = PA_SCROLL_LEFT, int speed = Constants::DISPLAY_SCROLL_SPEED, int pauseTime = 0)
{
    cenDisplay.displayClear();
    cenDisplay.displayScroll(text.c_str(), tPos, tEffect, speed);
    cenDisplay.setPause(pauseTime);
    while(!cenDisplay.displayAnimate()) //while not done displaying, display!
    {
        cenDisplay.displayAnimate();
    }
}

void ScoreKeeper::printTextNonBlocking(String text, textPosition_t tPos, textEffect_t tEffect, int speed, int pauseTime) //need to call displayAnimate still each time
{    
    cenDisplay.displayClear();
    cenDisplay.displayScroll(text.c_str(), tPos, tEffect, speed);
    cenDisplay.setPause(pauseTime);
}
}
