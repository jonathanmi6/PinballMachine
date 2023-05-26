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
Adafruit_MotorShield AFMS = Adafruit_MotorShield(Pinball::Constants::AFMS_I2C_ADDR); //if motor shield does not successfully connect, setup will NOT run
Adafruit_DCMotor *sliderMotor = AFMS.getMotor(4);
MD_Parola centerDisplay(MD_MAX72XX::FC16_HW, Pinball::Constants::SB_DAT_PIN, Pinball::Constants::SB_CLK_PIN, Pinball::Constants::SB_CS_PIN, 4); //create matrix display obj
Adafruit_8x8matrix leftDisplay;
Adafruit_8x8matrix rightDisplay;


//create objects
Pinball::ScoreKeep::ScoreKeeper scoreKeeper(centerDisplay, leftDisplay, rightDisplay);
// Pinball::ScoreKeep::ScoreKeeper scoreKeeper(centerDisplay);
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


// game variables
unsigned long currTime;
bool roundRunning;
bool checkRoundEnd;
int roundNum;
String idleText;

int getScore()
{
	return (slotLeft.getScore() + slotRight.getScore()) * Pinball::ScoreKeep::Constants::SLOT_SIDE_MULTIPLIER
	+ (slotCenter.getScore()) * Pinball::ScoreKeep::Constants::SLOT_CENTER_MULTIPLIER
	+ (dropTargetA.getScore() + dropTargetB.getScore() + dropTargetC.getScore()) * Pinball::ScoreKeep::Constants::DROP_TGT_MULTIPLIER 
	+ (popBumperA.getScore() + popBumperB.getScore() + popBumperC.getScore()) * Pinball::ScoreKeep::Constants::POP_BUMP_MULTIPLIER 
	+ (slingShotL.getScore() + slingShotR.getScore()) * Pinball::ScoreKeep::Constants::SLINGSHOT_MULTIPLIER;
}


void interruptPopA()
{
	popBumperA.interruptFlag = true;
	Serial.println("interrupt A");
}

void interruptPopB()
{
	popBumperB.interruptFlag = true;
	Serial.println("interrupt B");
}

void interruptPopC()
{
	popBumperC.interruptFlag = true;
	Serial.println("interrupt C");
}


void setup()
{
	Serial.begin(9600);
	Serial.println("Bruh");

	//initialize round keeping variables
	roundNum = 1;
	roundRunning = false;
	checkRoundEnd = true;

	// connect motor shield
	if (!AFMS.begin(Pinball::Constants::AFMS_I2C_ADDR)) 
    {
        Serial.println("Could not find Motor Shield");
        while (1);
    }

	// non scoring objects
	scoreKeeper.init();
	pongSlider.init();
	launcher.init();

	// IR sensors
	rstSensor.init();
	slotLeft.init();
	slotCenter.init();
	slotRight.init();

	// scoring objects
	dropTargetA.init();
	dropTargetB.init();
	dropTargetC.init();
	popBumperA.init();
	popBumperB.init();
	popBumperC.init();
	slingShotL.init();
	slingShotR.init();

	attachInterrupt(digitalPinToInterrupt(Pinball::Constants::POP_BUMP_A_SENSE_PIN), interruptPopA, LOW);
	attachInterrupt(digitalPinToInterrupt(Pinball::Constants::POP_BUMP_B_SENSE_PIN), interruptPopB, LOW);
	attachInterrupt(digitalPinToInterrupt(Pinball::Constants::POP_BUMP_C_SENSE_PIN), interruptPopC, LOW);

	// roundRunning = true;   // manual override to skip waiting for launch
	// checkRoundEnd = false; // set to false so that round lasts forever

	Serial.println("Initialized");
	// flash some shit onetime
	scoreKeeper.printTextBlocking("READY!");
}

void loop()
{
	if (roundNum > Pinball::Constants::MAX_ROUNDS) //if max round number reached
	{
		// reset the game
		Serial.println("Game Over");
		scoreKeeper.printTextBlocking("GAME", PA_CENTER, PA_OPENING_CURSOR, Pinball::ScoreKeep::Constants::DISPLAY_SCROLL_SPEED, 500);
		scoreKeeper.printTextBlocking("OVER!", PA_CENTER, PA_OPENING_CURSOR, Pinball::ScoreKeep::Constants::DISPLAY_SCROLL_SPEED, 500);
		// reset round num
		roundNum = 0;

		// wait for user to start a new game 
		centerDisplay.displayScroll("Press launch button to play again!", PA_CENTER, PA_SCROLL_LEFT, Pinball::ScoreKeep::Constants::DISPLAY_SCROLL_SPEED);
		int count = 0;
		bool nextAnimation = true;
		while (!launcher.getLaunchButton()) // wait for launch to be pressed to play again (does not actually launch)
		{
			if(nextAnimation) //if time to set next animation
			{
				nextAnimation = false; //lower flag
				centerDisplay.displayClear();			
				switch (count) //check which animation
				{
				case 0:
					scoreKeeper.printTextNonBlocking("Press launch button to play again!");
					break;

				case 1:
					scoreKeeper.printTextNonBlocking("Previous score: ");
					break;

				case 2:
					centerDisplay.setSpriteData(Pinball::ScoreKeep::Sprites::fireball, Pinball::ScoreKeep::Sprites::W_FBALL, Pinball::ScoreKeep::Sprites::F_FBALL, Pinball::ScoreKeep::Sprites::fireball, Pinball::ScoreKeep::Sprites::W_FBALL, Pinball::ScoreKeep::Sprites::F_FBALL);
					scoreKeeper.printTextNonBlocking(String(scoreKeeper.getTotalScore()), PA_CENTER, PA_SPRITE, 50, 1000);
					break;
				}
			}

			if(centerDisplay.displayAnimate()) // check if animation is done, if done, advance to next animation and raise flag for it
			{
				count++;
				nextAnimation = true;
				if(count == 3) //finished count 2 so reset to first string
				{
					count = 0;
				}
			}
		}

		// reset scoring objects
		rstSensor.reset();
		// slotLeft.reset();
		// slotCenter.reset();
		// slotRight.reset();

		dropTargetA.reset();
		dropTargetB.reset();
		dropTargetC.reset();
		popBumperA.reset();
		popBumperB.reset();
		popBumperC.reset();
		slingShotL.reset();
		slingShotR.reset();
	}

	Serial.println("Waiting for launch");
	delay(1000); // hard delay to prevent accidental launching from pressing launch button to restart game

	launcher.resetLaunched(); // set launched flag back to false

	// idling text display setup
	centerDisplay.displayClear();
	idleText = "Round " + String(roundNum) + " of " + String(Pinball::Constants::MAX_ROUNDS) + ". Launch ball to begin!";
	centerDisplay.displayScroll(idleText.c_str(), PA_CENTER, PA_SCROLL_LEFT, Pinball::ScoreKeep::Constants::DISPLAY_SCROLL_SPEED*1.5); //send text
	while (!roundRunning) // while waiting for round to start
	{
		currTime = millis();
		launcher.update(currTime); // update launcher
		roundRunning = launcher.getLaunched(); // returns launched once ball has been fully launched

		// display some shit while idling
		if(centerDisplay.displayAnimate()) // check if animation is done, if done, reset to scroll again
		{
			centerDisplay.displayReset();
		}

	}

	// put one time round start code below


	Serial.println("Round " + String(roundNum) + " starting");

	while (roundRunning) // running round loop
	{
		currTime = millis(); // update time

		// update mechanisms
		pongSlider.update(currTime);

		rstSensor.update(currTime);
		// slotLeft.update(currTime);
		// slotCenter.update(currTime);
		// slotRight.update(currTime);

		// dropTargetA.update(currTime);
		// dropTargetB.update(currTime);
		// dropTargetC.update(currTime);
		popBumperA.update(currTime);
		popBumperB.update(currTime);
		popBumperC.update(currTime);
		// slingShotL.update(currTime);
		// slingShotR.update(currTime);

		scoreKeeper.updateTotalScore(getScore()); // send total score to scoreKeeper
		scoreKeeper.updateScoreBoard(); //update the scoreboard
		// Serial.println(scoreKeeper.getTotalScore()); //debug: serial print score

		if (rstSensor.update(currTime) && checkRoundEnd) // if rst sensor triged, end round
		{
			// round end code
			Serial.println("Round " + String(roundNum) + " over");
			roundNum++;
			roundRunning = false;
			scoreKeeper.printTextBlocking("ROUND", PA_CENTER, PA_GROW_UP, Pinball::ScoreKeep::Constants::DISPLAY_SCROLL_SPEED, 500);
			scoreKeeper.printTextBlocking("OVER", PA_CENTER, PA_GROW_UP, Pinball::ScoreKeep::Constants::DISPLAY_SCROLL_SPEED, 500);

		}
		// Serial.println("Loop time: " + String(millis() - currTime));
	}
}


// void interruptPopB()
// {
// 	popBumperB.interruptFlag = true;
// }

// void interruptPopC()
// {
// 	popBumperC.interruptFlag = true;
// }
