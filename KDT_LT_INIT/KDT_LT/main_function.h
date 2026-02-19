#ifndef MAIN_FUNCTION_H
#define MAIN_FUNCTION_H

#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

// IR 기능 쓸 거면 주석 풀어야 extern 타입이 살아남음
#include <IRremote.h>

//====================================================
// 핀 정의 (공통)
//====================================================

// 모터 핀
#define RightMotor_E_pin 5
#define LeftMotor_E_pin  6
#define RightMotor_1_pin 8
#define RightMotor_2_pin 9
#define LeftMotor_3_pin  10
#define LeftMotor_4_pin  11

// 초음파 핀
#define trigPin 13
#define echoPin 12

// 블루투스 핀
#define BT_RXD 3
#define BT_TXD 4

// 라인센서 핀 (const int 대신 define로 통일 추천)
#define L_Line A5
#define C_Line A4
#define R_Line A3

// IR 리모컨 핀
#define RECV_PIN A0

//====================================================
// extern 객체/전역 (정의는 cpp 딱 한 곳에서만!)
//====================================================

// PHS IR 객체(사용 시)
extern IRrecv irrecv;
extern decode_results results;

// Servo 객체(프로젝트 전체에서 1개만 쓰면 extern으로 공유)
extern Servo servo;

extern int SL;
extern int SC;
extern int SR;

//====================================================
// === LJH FUNCTION ===
//====================================================

void motor_role(int R_motor, int L_motor);

int Ultrasonic();
int Servo_con();

void stop_motors();
void lineTrace_step();
void smartcar_step();

void bt_bridge_init(long baud);
void bt_bridge_step();

void rc_bt_init(long baud);
void rc_bt_step();

//====================================================
// === PHS FUNCTION ===
//====================================================

void initUltra();
void printUltra();

void initIR();
void checkIR();

void initServo();
void initMotor();
void commandSerialDirect();

//====================================================
// === LSB FUNCTION ===
//====================================================

void servo_control(int angle);
void line_value_serial(uint8_t pin1, uint8_t pin2, uint8_t pin3, int delay__);

void motor_control(int R_motor, int L_motor, int R_speed, int L_speed);

void Right_role(int R_motor, int L_motor, int Speed);
void Left_role(int R_motor, int L_motor, int Speed);
void driving_sys(int L, int C, int R, unsigned long &lostTime);


#endif  // MAIN_FUNCTION_H
