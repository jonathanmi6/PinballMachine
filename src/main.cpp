#include "Arduino.h"
#include "Servo.h"
#include "DropTarget.h"
#include "ScoreKeeper.h"
#include "PopBumper.h"
#include "constants.h"
#include "PongSlider.h"
#include "Launcher.h"
#include "DigitalDebounce.h"

//create objects
Pinball::PongSlide::PongSlider pongSlider(Pinball::EASY);
Pinball::Launch::Launcher launcher(1);
Pinball::DigDB::DigitalDebounce rstSensor(Pinball::Constants::GAME_RST_PIN, Pinball::Constants::GAME_RST_PIN_DBTIME, true);

Pinball::DropTGT::DropTarget dropTargetA(Pinball::Constants::DROP_TGT_A_SERVO_PIN, Pinball::Constants::DROP_TGT_A_SWITCH_PIN);
Pinball::DropTGT::DropTarget dropTargetB(Pinball::Constants::DROP_TGT_B_SERVO_PIN, Pinball::Constants::DROP_TGT_B_SWITCH_PIN);
Pinball::DropTGT::DropTarget dropTargetC(Pinball::Constants::DROP_TGT_C_SERVO_PIN, Pinball::Constants::DROP_TGT_C_SWITCH_PIN);
Pinball::PopBump::PopBumper popBumperA(Pinball::Constants::POP_BUMP_A_SOLND_PIN, Pinball::Constants::POP_BUMP_A_SENSE_PIN);
Pinball::PopBump::PopBumper popBumperB(Pinball::Constants::POP_BUMP_B_SOLND_PIN, Pinball::Constants::POP_BUMP_B_SENSE_PIN);
Pinball::PopBump::PopBumper popBumperC(Pinball::Constants::POP_BUMP_C_SOLND_PIN, Pinball::Constants::POP_BUMP_C_SENSE_PIN);
//make slingshot a popbumper object?
//make slingshot a popbumper object?

Pinball::ScoreKeep::ScoreKeeper scoreKeeper(Pinball::EASY);

//variables
int totalScore;
unsigned long currTime;
bool roundRunning;
bool checkRoundEnd;
int roundNum;

void updateScores()
{
  totalScore = (dropTargetA.getScore() + dropTargetB.getScore() + dropTargetC.getScore()) * Pinball::ScoreKeep::Constants::DROP_TGT_MULTIPLIER
              + (popBumperA.getScore() + popBumperB.getScore() + popBumperC.getScore()) * Pinball::ScoreKeep::Constants::POP_BUMP_MULTIPLIER;
}

void setup()
{
  Serial.begin(9600);
  totalScore = 0;
  roundNum = 1;
  roundRunning = false;
  checkRoundEnd = true;

  //initialize objects
  launcher.init();
  rstSensor.init();

  dropTargetA.init();
  // dropTargetB.init();
  // dropTargetC.init();
  popBumperA.init();
  popBumperB.init();
  popBumperC.init();
  pongSlider.init();

  //flash some shit onetime

  // roundRunning = true; //manual override to skip waiting for launch
  // checkRoundEnd = false; //set to false so that round lasts forever
}

void loop()
{
  if(roundNum > Pinball::Constants::MAX_ROUNDS)
  {
    //reset the game
    Serial.println("Game Over");
    totalScore = 0;
    scoreKeeper.resetScore(); //why reset in two places??? badge code
    roundNum = 0;
    while(!launcher.getLaunchButton())
    {
      //wait for launch to be pressed
      //put idle animation
    }
  }

  Serial.println("Waiting for launch");
  delay(1000); //delay to prevent accidental launching

  launcher.resetLaunched();
  while (!roundRunning) //waiting for round to start
  {
    currTime = millis();
    launcher.update(currTime);
    roundRunning = launcher.getLaunched(); //once launched, start round

    //display some shit while idling
  }

  //put one time round start code below
  
  while (roundRunning) //round started
  {
    currTime = millis(); //update time

    //update mechanisms
    dropTargetA.update(currTime);
    // dropTargetB.update(currTime);
    // dropTargetC.update(currTime);
    popBumperA.update(currTime);
    popBumperB.update(currTime);
    popBumperC.update(currTime);
    // pongSlider.update(currTime);

    updateScores();
    scoreKeeper.updateTotalScore(totalScore); //send total score to scoreKeeper
    // scoreKeeper.updateScoreBoard();
    // Serial.println(scoreKeeper.getTotalScore());

    if(rstSensor.update(currTime) && checkRoundEnd) //if rst sensor triged
    {
      //round end code
      Serial.println("Round " + String(roundNum) + " over");
      roundNum++;
      roundRunning = false;
    }
  }
}


