#pragma once

// Total Available IO:
// DIO: 36 (14->43, 47-53)
// PWM: 15 (2->13, 44-46)
// ANALOG IN: 16 (A0 - A15)
// interrupt: 2, 3, 18, 19,  // I2C: 20, 21

namespace Pinball::Constants
{
// Game settings
const int MAX_ROUNDS = 3; // int
const int GAME_RST_PIN = 22; // DIO
const int GAME_RST_PIN_DBTIME = 5; // ms

// Drop target pins
const int DROP_TGT_A_SERVO_PIN = 13; // PWM
const int DROP_TGT_B_SERVO_PIN = 12; // PWM
const int DROP_TGT_C_SERVO_PIN = 11; // PWM
const int DROP_TGT_A_SWITCH_PIN = 36; // DIN
const int DROP_TGT_B_SWITCH_PIN = 34; // DIN
const int DROP_TGT_C_SWITCH_PIN = 32; // DIN

// Slingshot pins
const int SLINGSHOT_L_SOLND_PIN = 8;  // PWM
const int SLINGSHOT_R_SOLND_PIN = 3;  // PWM
const int SLINGSHOT_L_SENSE_PIN = 40; // DIN
const int SLINGSHOT_R_SENSE_PIN = 48; // DIN

// Pop bumper pins
const int POP_BUMP_A_SOLND_PIN = 9;	 // PWM
const int POP_BUMP_B_SOLND_PIN = 5; // PWM
const int POP_BUMP_C_SOLND_PIN = 7; // PWM
const int POP_BUMP_A_SENSE_PIN = 19; // interrupt //42; // DIN
const int POP_BUMP_B_SENSE_PIN = 2;// interrupt //46; // DIN
const int POP_BUMP_C_SENSE_PIN = 18; // interrupt //44; // DIN


// Pong Slider Input Pins
const int SLIDE_L_BTN_PIN = 29; // DIN
const int SLIDE_R_BTN_PIN = 25; // DIN
const int FLIP_L_BTN_PIN = 31;	// DIN
const int FLIP_R_BTN_PIN = 27;	// DIN

const int SLIDE_L_LS_PIN = 35; // DIN
const int SLIDE_R_LS_PIN = 33; // DIN

// Pong Slider Output Pins
const int AFMS_I2C_ADDR = 0x60;

const int FLIP_L_SOLND_PIN = 6; // PWM
const int FLIP_R_SOLND_PIN = 10; // PWM


// Scorekeeper pins
const int SB_L_MATRIX_I2C_ADDR = 0x70;
const int SB_R_MATRIX_I2C_ADDR = 0x71;

const int SB_DAT_PIN = 51; // SPI MOSI
const int SB_CLK_PIN = 52; // SPI CLK
const int SB_CS_PIN = 53;  // SPI SS

// Launcher Pins
const int LAUNCH_SOLND_PIN = 4; // PWM
const int LAUNCH_POT_PIN = 1;	 // analog
const int LAUNCH_BTN_PIN = 23;	 // DIO

// Slots pins
const int SLOT_L_PIN = 28;	// DIO
const int SLOT_C_PIN = 30;	// DIO
const int SLOT_R_PIN = 32;	// DIO
const int SLOT_DBTIME = 10; // DIO

// Horizontal Spinner pins
const int HSPINNER_MOTOR_PIN = 44; // PWM

enum Difficulty
{
	EASY,
	MEDIUM,
	HARD,
};

}
