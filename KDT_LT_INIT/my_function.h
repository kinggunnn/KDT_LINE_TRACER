#ifndef MY_FUNCTION_H
#define MY_FUNCTION_H

#include <Arduino.h>
#include <IRremote.h> // 적외선 리모컨
extern int Ultra_d;

#include <Servo.h> // 서보모터 헤더파일 추가
extern Servo myservo; // 서보모터 생성자 'myservo'가 어딘가에 있다는걸 알려주는 부분.


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


const int L_Line = A5;            // 왼쪽 라인트레이서 센서는 A5 핀에 연결
const int C_Line = A4;            // 가운데 라인트레이서 센서는 A4 핀에 연결
const int R_Line = A3;            // 오른쪽 라인트레이서 센서는 A3 핀에 연결


//함수선언부
void lineTrace_step();                 // 한 번 업데이트(센서읽기+모터제어)
void stop_motors();                    // 정지(속도 0)

void smartcar_step();     // 초음파+서보 스캔 기반 장애물 회피 1스텝
void bt_bridge_init(long baud); //블루투스
void bt_bridge_step();

void rc_bt_init(long baud); //블르투스 rc카
void rc_bt_step();


int Ultrasonic(); //초음파
int Servo_con(); //


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
extern IRrecv irrecv;
extern decode_results results;

void initIR();
void checkIR();

// =======================================
// 서보모터 90도 세팅 함수
extern Servo servo;
void initServo();


void commandSerialDirect();

// 서범 : 서보 모터 정의
void servo_control(int angle);
// 서범 : 라인트레이서 정의
void line_value_serial(uint8_t pin1, uint8_t pin2, uint8_t pin3, int delay__);
// 서범 : 모터 방향 및 속도 정의
void motor_control(int R_motor, int L_motor, int R_speed, int L_speed);
// 서범 : 오른쪽 왼쪽의 강한 회전을 정의한 함수
void Right_role(int R_motor, int L_motor, int Speed);
void Left_role(int R_motor, int L_motor, int Speed);

#endif
