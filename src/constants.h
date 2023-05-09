#pragma once

//Total Available IO:
//DIO: 36 (14->43, 47-53)
//PWM: 15 (2->13, 44-46)
//ANALOG IN: 16 (A0 - A15)

namespace Pinball::Constants
{
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
const int POP_BUMP_A_SENSE_PIN = 25; //DIN? or ANALOG IN
const int POP_BUMP_B_SENSE_PIN = 25; //DIN? or ANALOG IN

//Pong Slider Input Pins
const int SLIDE_L_BTN_PIN = 0; //DIN
const int SLIDE_R_BTN_PIN = 0; //DIN
const int FLIP_L_BTN_PIN = 0; //DIN
const int FLIP_R_BTN_PIN = 0; //DIN

const int SLIDE_R_LS_PIN = 0; //DIN
const int SLIDE_L_LS_PIN = 0; //DIN

//Pong Slider Output Pins
const int SLIDE_MOTOR_FWD_HIGH_PIN = 0; //DIO
const int SLIDE_MOTOR_REV_HIGH_PIN = 0; //DIO
const int SLIDE_MOTOR_FWD_LOW_PIN = 7; //PWN
const int SLIDE_MOTOR_REV_LOW_PIN = 8; //PWM

const int FLIP_L_SOLND_PIN = 9; //PWM
const int FLIP_R_SOLND_PIN = 10; //PWM

//Slingshot pins
const int SLING_SHOT_L_SOLND_PIN = 11; //PWM
const int SLING_SHOT_R_SOLND_PIN = 12; //PWM
const int SLING_SHOT_L_SENSE_PIN = 0; //DIN? or ANALOG IN
const int SLING_SHOT_R_SENSE_PIN = 0; //DIN? or ANALOG IN

//Scoreboard pins
const int SB_SER = 0; //DIO
const int SB_RCLK = 0; //DIO
const int SB_SRCLK = 0; //DIO
//PNP - LOW = EN, HIGH = OFF
const int SB_ONES_EN = 0; //DIO 
const int SB_TENS_EN = 0; //DIO
const int SB_HUNS_EN = 0; //DIO
const int SB_THDS_EN = 0; //DIO


}
