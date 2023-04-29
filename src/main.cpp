#include "Arduino.h"
#include "Servo.h"
#include "DropTarget.h"
#include "ScoreKeeper.h"
#include "PopBumper.h"
#include "constants.h"
#include "PongSlider.h"

//create objects
Pinball::PongSlide::PongSlider pongSlider(Pinball::EASY);

Pinball::DropTGT::DropTarget dropTargetA(Pinball::Constants::DROP_TGT_A_SERVO_PIN, Pinball::Constants::DROP_TGT_A_SWITCH_PIN);
Pinball::DropTGT::DropTarget dropTargetB(Pinball::Constants::DROP_TGT_B_SERVO_PIN, Pinball::Constants::DROP_TGT_B_SWITCH_PIN);
Pinball::PopBump::PopBumper popBumperA(Pinball::Constants::POP_BUMP_A_SOLND_PIN, Pinball::Constants::POP_BUMP_A_SENSE_PIN);


Pinball::ScoreKeep::ScoreKeeper scoreKeeper(Pinball::HARD);

//variables
int totalScore;
unsigned long currTime;

void updateScores()
{
  totalScore = (dropTargetA.getScore() + dropTargetB.getScore()) * Pinball::ScoreKeep::Constants::DROP_TGT_MULTIPLIER
              + popBumperA.getScore() * Pinball::ScoreKeep::Constants::POP_BUMP_MULTIPLIER;
}

void setup()  //for testing drop target
{
  Serial.begin(9600);
  totalScore = 0;

  //initialize objects
  // dropTargetA.init();
  // dropTargetB.init();
  popBumperA.init();
}

void loop()
{
  currTime = millis(); //update time
  // dropTargetA.update(currTime);//update drop target
  // dropTargetB.update(currTime);
  popBumperA.update(currTime);

  // updateScores();
  // scoreKeeper.updateTotalScore(totalScore); //send total score to scoreKeeper
  // Serial.println(scoreKeeper.getTotalScore());
}


