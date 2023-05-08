#pragma once
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
const int POP_BUMP_A_SENSE_PIN = 25; //DIN? or ANALOG IN

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
const int SLIDE_MOTOR_FWD_LOW_PIN = 0; //PWN
const int SLIDE_MOTOR_REV_LOW_PIN = 0; //PWM

const int FLIP_L_SOLND_PIN = 0; //PWM
const int FLIP_R_SOLND_PIN = 0; //PWM

//Scoreboard pins
const int SB_SER = 0; //DIO
const int SB_CLK = 0; //DIO
const int SB_SRCLK = 0; //DIO
//PNP - LOW = EN, HIGH = OFF
const int SB_ONES_EN = 0; //DIO 
const int SB_TENS_EN = 0; //DIO
const int SB_HUNS_EN = 0; //DIO
const int SB_THDS_EN = 0; //DIO


}
