#pragma once

//Total Available IO:
//DIO: 36 (14->43, 47-53)
//PWM: 15 (2->13, 44-46)
//ANALOG IN: 16 (A0 - A15)

namespace Pinball::Constants
{
//Game settings
const int MAX_ROUNDS = 3;
const int GAME_RST_PIN = 37;
const int GAME_RST_PIN_DBTIME = 10;

//Drop target pins
const int DROP_TGT_A_SERVO_PIN = 2; //PWM
const int DROP_TGT_B_SERVO_PIN = 3; //PWM
const int DROP_TGT_C_SERVO_PIN = 4; //PWM
const int DROP_TGT_A_SWITCH_PIN = 22; //DIN
const int DROP_TGT_B_SWITCH_PIN = 23; //DIN
const int DROP_TGT_C_SWITCH_PIN = 24; //DIN

//Pop bumper pins
const int POP_BUMP_A_SOLND_PIN = 5; //PWM
const int POP_BUMP_B_SOLND_PIN = 6; //PWM
const int POP_BUMP_C_SOLND_PIN = 7; //PWM
const int POP_BUMP_A_SENSE_PIN = 26; //DIN? or ANALOG IN
const int POP_BUMP_B_SENSE_PIN = 27; //DIN? or ANALOG IN
const int POP_BUMP_C_SENSE_PIN = 28; //DIN? or ANALOG IN

//Pong Slider Input Pins
const int SLIDE_L_BTN_PIN = 40; //DIN
const int SLIDE_R_BTN_PIN = 41; //DIN
const int FLIP_L_BTN_PIN = 42; //DIN
const int FLIP_R_BTN_PIN = 43; //DIN

const int SLIDE_L_LS_PIN = 44; //DIN
const int SLIDE_R_LS_PIN = 45; //DIN

//Pong Slider Output Pins
const int SLIDE_MOTOR_FWD_PIN = 14; //DIO
const int SLIDE_MOTOR_REV_PIN = 15; //DIO
const int SLIDE_MOTOR_PWM_PIN = 8; //PWN - do not need

const int FLIP_L_SOLND_PIN = 9; //PWM
const int FLIP_R_SOLND_PIN = 10; //PWM

//Slingshot pins
const int SLINGSHOT_L_SOLND_PIN = 11; //PWM
const int SLINGSHOT_R_SOLND_PIN = 12; //PWM
const int SLINGSHOT_L_SENSE_PIN = 29; //DIN? or ANALOG IN
const int SLINGSHOT_R_SENSE_PIN = 30; //DIN? or ANALOG IN

//Scorekeeper pins
const int SB_CLK_PIN = 52; //SPI CLK
const int SB_DAT_PIN = 51; //SPI MISO
const int SB_CS_PIN = 53; //SPI SS 

//Launcher Pins
const int LAUNCH_SOLND_PIN = 13; //PWM
const int LAUNCH_POT_PIN = 1; //analog
const int LAUNCH_BTN_PIN = 33; //DIO

//Slots pins
const int SLOT_L_PIN = 34;
const int SLOT_C_PIN = 35;
const int SLOT_R_PIN = 36;
const int SLOT_DBTIME = 10;

//Horizontal Spinner pins
const int HSPINNER_MOTOR_PIN = 8; //same as slider pwm since slider uses shield board instead


enum Difficulty
{
    EASY,
    MEDIUM,
    HARD,
};

}
