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
Pinball::DropTGT::DropTarget dropTargetC(Pinball::Constants::DROP_TGT_C_SERVO_PIN, Pinball::Constants::DROP_TGT_C_SWITCH_PIN);
Pinball::PopBump::PopBumper popBumperA(Pinball::Constants::POP_BUMP_A_SOLND_PIN, Pinball::Constants::POP_BUMP_A_SENSE_PIN);
Pinball::PopBump::PopBumper popBumperB(Pinball::Constants::POP_BUMP_B_SOLND_PIN, Pinball::Constants::POP_BUMP_B_SENSE_PIN);
//make slingshot a popbumper object?

Pinball::ScoreKeep::ScoreKeeper scoreKeeper(Pinball::EASY);

//variables
int totalScore;
unsigned long currTime;
bool roundRunning;

void updateScores()
{
  totalScore = (dropTargetA.getScore() + dropTargetB.getScore()) * Pinball::ScoreKeep::Constants::DROP_TGT_MULTIPLIER
              + popBumperA.getScore() * Pinball::ScoreKeep::Constants::POP_BUMP_MULTIPLIER;
}

void setup()  //for testing drop target
{
  Serial.begin(9600);
  totalScore = 0;
  roundRunning = false;

  //initialize objects
  // dropTargetA.init();
  // dropTargetB.init();
  popBumperA.init();
  popBumperB.init();
  pongSlider.init();
  
}

void loop()
{
  currTime = millis(); //update time

  // while (roundRunning)
  // {
  //   /* code */
  // }
  

  //update mechanisms
  // dropTargetA.update(currTime);
  // dropTargetB.update(currTime);
  popBumperA.update(currTime);
  popBumperB.update(currTime);
  pongSlider.update(currTime);

  // updateScores();
  // scoreKeeper.updateTotalScore(totalScore); //send total score to scoreKeeper
  // Serial.println(scoreKeeper.getTotalScore());
}


