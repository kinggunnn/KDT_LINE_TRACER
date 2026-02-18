#ifndef MY_FUNCTION_H
#define MY_FUNCTION_H

#include <Arduino.h>
#include <Servo.h>
extern Servo EduServo;
extern int Ultra_d;



// 핀 정의 모터 관련
#define RightMotor_E_pin 5
#define LeftMotor_E_pin  6
#define RightMotor_1_pin 8
#define RightMotor_2_pin 9
#define LeftMotor_3_pin  10
#define LeftMotor_4_pin  11

// 핀 연결 정의
#define trigPin 13
#define echoPin 12


#define BT_RXD 3
#define BT_TXD 4


#define L_Line A5
#define C_Line A4
#define R_Line A3

//함수선언부
void lineTrace_step();                 // 한 번 업데이트(센서읽기+모터제어)
void stop_motors();                    // 정지(속도 0)

void smartcar_step();     // 초음파+서보 스캔 기반 장애물 회피 1스텝
void bt_bridge_init(long baud); //블루투스
void bt_bridge_step();

void rc_bt_init(long baud); //블르투스 rc카
void rc_bt_step();


void motor_role(int R_motor, int L_motor); // 모터제어
int Ultrasonic(); //초음파
int Servo_con(); //

#endif
