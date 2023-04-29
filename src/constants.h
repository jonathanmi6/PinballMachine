#pragma once
namespace Pinball::Constants
{

//Drop target pins
const int DROP_TGT_A_SERVO_PIN = 2; //PWM
const int DROP_TGT_A_SWITCH_PIN = 22; //DIN
const int DROP_TGT_B_SERVO_PIN = 3; //PWM
const int DROP_TGT_B_SWITCH_PIN = 23; //DIN
const int DROP_TGT_C_SERVO_PIN = 4; //PWM
const int DROP_TGT_C_SWITCH_PIN = 24; //DIN

//Pop bumper pins
const int POP_BUMP_A_SOLND_PIN = 5; //PWM
const int POP_BUMP_A_SENSE_PIN = 25; //DIN? or ANALOG IN

//Pong Slider Pins
const int SLIDE_L_BTN_PIN; //DIN
const int SLIDE_R_BTN_PIN; //DIN
const int FLIP_L_BTN_PIN; //DIN
const int FLIP_R_BTN_PIN; //DIN
const int SLIDE_MOTOR_FWD_PIN; //PWM
const int SLIDE_MOTOR_REV_PIN; //PWM
const int FLIP_L_SOLND_PIN; //PWM
const int FLIP_R_SOLND_PIN; //PWM
const int SLIDE_R_LS_PIN; //DIN
const int SLIDE_L_LS_PIN; //DIN

}
