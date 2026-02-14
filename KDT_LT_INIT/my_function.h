#ifndef MY_FUNCTION_H
#define MY_FUNCTION_H

#include <Arduino.h>

// 핀 정의
#define RightMotor_E_pin 5
#define LeftMotor_E_pin  6
#define RightMotor_1_pin 8
#define RightMotor_2_pin 9
#define LeftMotor_3_pin  10
#define LeftMotor_4_pin  11

#define L_Line A5
#define C_Line A4
#define R_Line A3

// 속도 정의
#define L_MotorSpeed 100
#define R_MotorSpeed 100

void motor_role(int R_motor, int L_motor);

#endif
