#include "Arduino.h"
#include "Servo.h"
#include "MD_MAX72xx.h"
#include "MD_Parola.h"
#include "Adafruit_LEDBackpack.h"
#include "DropTarget.h"
#include "ScoreKeeper.h"
#include "PopBumper.h"
#include "constants.h"
#include "PongSlider.h"
#include "Launcher.h"
#include "DigitalDebounce.h"


//Hardware Objects
Adafruit_MotorShield AFMS;
Adafruit_DCMotor *sliderMotor = AFMS.getMotor(3);
MD_Parola centerDisplay(MD_MAX72XX::FC16_HW, Pinball::Constants::SB_DAT_PIN, Pinball::Constants::SB_CLK_PIN, Pinball::Constants::SB_CS_PIN, 4); //create matrix display obj
Adafruit_8x8matrix leftDisplay;
Adafruit_8x8matrix rightDisplay;


//create objects
Pinball::ScoreKeep::ScoreKeeper scoreKeeper(centerDisplay, leftDisplay, rightDisplay);
Pinball::PongSlide::PongSlider pongSlider(sliderMotor);
Pinball::Launch::Launcher launcher;

Pinball::DigDB::DigitalDebounce rstSensor(Pinball::Constants::GAME_RST_PIN, Pinball::Constants::GAME_RST_PIN_DBTIME, true);
Pinball::DigDB::DigitalDebounce slotLeft(Pinball::Constants::SLOT_L_PIN, Pinball::Constants::SLOT_DBTIME, true);
Pinball::DigDB::DigitalDebounce slotCenter(Pinball::Constants::SLOT_C_PIN, Pinball::Constants::SLOT_DBTIME, true);
Pinball::DigDB::DigitalDebounce slotRight(Pinball::Constants::SLOT_R_PIN, Pinball::Constants::SLOT_DBTIME, true);

Pinball::DropTGT::DropTarget dropTargetA(Pinball::Constants::DROP_TGT_A_SERVO_PIN, Pinball::Constants::DROP_TGT_A_SWITCH_PIN);
Pinball::DropTGT::DropTarget dropTargetB(Pinball::Constants::DROP_TGT_B_SERVO_PIN, Pinball::Constants::DROP_TGT_B_SWITCH_PIN);
Pinball::DropTGT::DropTarget dropTargetC(Pinball::Constants::DROP_TGT_C_SERVO_PIN, Pinball::Constants::DROP_TGT_C_SWITCH_PIN);
Pinball::PopBump::PopBumper popBumperA(Pinball::Constants::POP_BUMP_A_SOLND_PIN, Pinball::Constants::POP_BUMP_A_SENSE_PIN);
Pinball::PopBump::PopBumper popBumperB(Pinball::Constants::POP_BUMP_B_SOLND_PIN, Pinball::Constants::POP_BUMP_B_SENSE_PIN);
Pinball::PopBump::PopBumper popBumperC(Pinball::Constants::POP_BUMP_C_SOLND_PIN, Pinball::Constants::POP_BUMP_C_SENSE_PIN);
Pinball::PopBump::PopBumper slingShotL(Pinball::Constants::SLINGSHOT_L_SOLND_PIN, Pinball::Constants::SLINGSHOT_L_SENSE_PIN);
Pinball::PopBump::PopBumper slingShotR(Pinball::Constants::SLINGSHOT_R_SOLND_PIN, Pinball::Constants::SLINGSHOT_R_SENSE_PIN);


// variables
int totalScore;
unsigned long currTime;
bool roundRunning;
bool checkRoundEnd;
int roundNum;
String idleText;

void updateScores()
{
	totalScore = (slotLeft.getScore() + slotRight.getScore()) * Pinball::ScoreKeep::Constants::SLOT_SIDE_MULTIPLIER
	+ (slotCenter.getScore()) * Pinball::ScoreKeep::Constants::SLOT_CENTER_MULTIPLIER
	+ (dropTargetA.getScore() + dropTargetB.getScore() + dropTargetC.getScore()) * Pinball::ScoreKeep::Constants::DROP_TGT_MULTIPLIER 
	+ (popBumperA.getScore() + popBumperB.getScore() + popBumperC.getScore()) * Pinball::ScoreKeep::Constants::POP_BUMP_MULTIPLIER 
	+ (slingShotL.getScore() + slingShotR.getScore()) * Pinball::ScoreKeep::Constants::SLINGSHOT_MULTIPLIER;
}

void setup()
{
	Serial.begin(9600);
	//initialize round keeping variables
	totalScore = 0;
	roundNum = 1;
	roundRunning = false;
	checkRoundEnd = true;


	//connect motor shield
	if (!AFMS.begin(Pinball::Constants::AFMS_I2C_ADDR)) 
    {
        Serial.println("Could not find Motor Shield");
        while (1);
    }

	// initialize objects
	//non scoring objects
	scoreKeeper.init();
	pongSlider.init();
	launcher.init();

	//IR sensors
	rstSensor.init();
	slotLeft.init();
	slotCenter.init();
	slotRight.init();

	//scoring objects
	dropTargetA.init();
	dropTargetB.init();
	dropTargetC.init();
	popBumperA.init();
	popBumperB.init();
	popBumperC.init();
	slingShotL.init();
	slingShotR.init();

	roundRunning = true;   // manual override to skip waiting for launch
	checkRoundEnd = false; // set to false so that round lasts forever

	// flash some shit onetime
	centerDisplay.displayScroll("Finished Initialization", PA_CENTER, PA_SCROLL_LEFT, 100);
	while(!centerDisplay.displayAnimate()) //while not done displaying
	{
		centerDisplay.displayAnimate();
	}
}

void loop()
{
	if (roundNum > Pinball::Constants::MAX_ROUNDS) //if max round number reached
	{
		// reset the game
		Serial.println("Game Over");
		// game over text
		// 
		//
		//

		// reset score and round
		totalScore = 0;
		roundNum = 0;

		// wait for user to start a new game 
		centerDisplay.displayScroll("Press launch button to play again!", PA_CENTER, PA_SCROLL_LEFT, 100);
		while (!launcher.getLaunchButton()) // wait for launch to be pressed to play again (does not actually launch)
		{
			centerDisplay.displayAnimate(); // put idle animation while waiting
			// need to reset the animation 
		}
	}

	Serial.println("Waiting for launch");
	delay(2000); // hard delay to prevent accidental launching from pressing launch button to restart game

	launcher.resetLaunched();
	while (!roundRunning) // while waiting for round to start
	{
		currTime = millis();
		launcher.update(currTime); // update launcher
		roundRunning = launcher.getLaunched(); // returns launched once ball has been fully launched

		// display some shit while idling
		idleText = "Round " + String(roundNum) + " of " + String(Pinball::Constants::MAX_ROUNDS) + ", press launch button to launch ball";
		centerDisplay.displayClear();
		centerDisplay.displayScroll(idleText.c_str(), PA_CENTER, PA_SCROLL_LEFT, 100);
		if(centerDisplay.displayAnimate())
		{
			centerDisplay.displayReset();
		}

	}

	// put one time round start code below
	// initialize all objects to reset them
	pongSlider.init();
	launcher.init();

	rstSensor.init();
	slotLeft.init();
	slotCenter.init();
	slotRight.init();

	dropTargetA.init();
	dropTargetB.init();
	dropTargetC.init();
	popBumperA.init();
	popBumperB.init();
	popBumperC.init();
	slingShotL.init();
	slingShotR.init();

	Serial.println("Initialization successful, round " + String(roundNum) + " starting");

	while (roundRunning) // round started
	{
		currTime = millis(); // update time

		// update mechanisms
		pongSlider.update(currTime);

		rstSensor.update(currTime);
		slotLeft.update(currTime);
		slotCenter.update(currTime);
		slotRight.update(currTime);

		dropTargetA.update(currTime);
		dropTargetB.update(currTime);
		dropTargetC.update(currTime);
		popBumperA.update(currTime);
		popBumperB.update(currTime);
		popBumperC.update(currTime);
		slingShotL.update(currTime);
		slingShotR.update(currTime);

		updateScores();
		scoreKeeper.updateTotalScore(totalScore); // send total score to scoreKeeper
		// scoreKeeper.updateScoreBoard();
		// Serial.println(scoreKeeper.getTotalScore());

		if (rstSensor.update(currTime) && checkRoundEnd) // if rst sensor triged
		{
			// round end code
			Serial.println("Round " + String(roundNum) + " over");
			roundNum++;
			roundRunning = false;
		}
	}
}
