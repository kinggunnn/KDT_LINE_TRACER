#ifndef MY_FUNCTION_H
#define MY_FUNCTION_H

#include <Arduino.h>
#include <IRremote.h> // 적외선 리모컨
#include <Servo.h> // 서보모터

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


// =======================================
// 초음파 핀 정의
#define trigPin 13
#define echoPin 12
// 리모컨 핀 정의
#define RECV_PIN A0
// =======================================
// 초음파 값 출력 함수
void initUltra();
void printUltra();
// =======================================
// 리모컨 값 출력 함수
void initIR();
void checkIR();
// =======================================
// 서보모터 90도 세팅 함수
void initServo();
// =======================================
// 시리얼로 주행 제어 함수
void initMotor();
void commandSerialDirect();

#endif
