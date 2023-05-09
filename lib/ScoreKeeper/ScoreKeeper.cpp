#include "Arduino.h"
#include "ScoreKeeper.h"
#include "constants.h"

namespace Pinball::ScoreKeep {
ScoreKeeper::ScoreKeeper(Difficulty difficulty)
{
    this->difficulty = difficulty;
    totalScore = 0;
    maxedScore = false;
}

void ScoreKeeper::init()
{
    pinMode(Pinball::Constants::SB_ONES_EN, OUTPUT);
    pinMode(Pinball::Constants::SB_TENS_EN, OUTPUT);
    pinMode(Pinball::Constants::SB_HUNS_EN, OUTPUT);
    pinMode(Pinball::Constants::SB_THDS_EN, OUTPUT);
    pinMode(Pinball::Constants::SB_SER, OUTPUT);
    pinMode(Pinball::Constants::SB_RCLK, OUTPUT);
    pinMode(Pinball::Constants::SB_SRCLK, OUTPUT);

    clearScoreBoard();
}

void ScoreKeeper::updateTotalScore(int totalScore)
{
    this->totalScore = totalScore;
}

void ScoreKeeper::updateScoreBoard(unsigned long currTime) //update display of score
{
    setScoreBoard(totalScore, currTime);
    //delay
    setScoreBoard(totalScore, currTime);
    //delay
    setScoreBoard(totalScore, currTime);
    //delay
    setScoreBoard(totalScore, currTime);
    //delay?
}

void ScoreKeeper::clearScoreBoard()
{
    digitalWrite(Pinball::Constants::SB_RCLK, LOW);
    shiftOut(Pinball::Constants::SB_SER, Pinball::Constants::SB_SRCLK, LSBFIRST, Constants::SEGMENT_DECIMAL[0]);
    digitalWrite(Pinball::Constants::SB_RCLK, HIGH);

    digitalWrite(Pinball::Constants::SB_ONES_EN, LOW);
    digitalWrite(Pinball::Constants::SB_TENS_EN, LOW);
    digitalWrite(Pinball::Constants::SB_HUNS_EN, LOW);
    digitalWrite(Pinball::Constants::SB_THDS_EN, LOW);
}

void ScoreKeeper::scoreBoardOff()
{
    digitalWrite(Pinball::Constants::SB_ONES_EN, HIGH);
    digitalWrite(Pinball::Constants::SB_TENS_EN, HIGH);
    digitalWrite(Pinball::Constants::SB_HUNS_EN, HIGH);
    digitalWrite(Pinball::Constants::SB_THDS_EN, HIGH);
}

void ScoreKeeper::setScoreBoard(int value, unsigned long currTime) //need to call at least 4 loops to work (and also delay between 4 cycles?)
{
    if(value > 9999) //catch overflow
    {
        value = 9999;
        maxedScore = true;
    }

    scoreBoardOff(); //turn digits off

    digitalWrite(Pinball::Constants::SB_RCLK, LOW); //force RCLK low
    shiftOut(Pinball::Constants::SB_SER, Pinball::Constants::SB_SRCLK, LSBFIRST, Constants::SEGMENT_DECIMAL[value]); //send serial

    //really dumb implementation bc i don't want to make an array or enum kek
    if(count == 0)
    {
        digitalWrite(Pinball::Constants::SB_ONES_EN, LOW);
    }
    else if(count == 1)
    {
        digitalWrite(Pinball::Constants::SB_TENS_EN, LOW);
    }
    else if(count == 2)
    {
        digitalWrite(Pinball::Constants::SB_HUNS_EN, LOW);
    }
    else if(count == 3)
    {
        digitalWrite(Pinball::Constants::SB_THDS_EN, LOW);
    }

    digitalWrite(Pinball::Constants::SB_RCLK, HIGH); //force RCLK high to send SR

    count++;
    if(count == 4)
    {
        count = 0;
    }
}

// void ScoreKeeper::writeDigit(int digitPin, int value) //common anode
// {
//     scribing = true;
//     digitalWrite(digitPin, LOW);
//     //add delay here somehow
//     digitalWrite(digitPin, HIGH);
// }

int ScoreKeeper::getTotalScore()
{
    return totalScore;
}
}
