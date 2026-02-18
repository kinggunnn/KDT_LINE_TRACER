#ifndef LSB_FUNCTION_H
#define LSB_FUNCTION_H

#include <Arduino.h>
#include <Servo.h> // 서보모터 헤더파일 추가

extern Servo myservo; // 서보모터 생성자 'myservo'가 어딘가에 있다는걸 알려주는 부분.

// 핀 정의
#define RightMotor_E_pin 5  // 오른쪽 모터의 Enable & PWM
#define LeftMotor_E_pin  6  // 왼쪽 모터의 Enable & PWM
#define RightMotor_1_pin 8  // 오른쪽 모터 제어선 IN1
#define RightMotor_2_pin 9  // 오른쪽 모터 제어선 IN2
#define LeftMotor_3_pin  10 // 왼쪽 모터 제어선 IN3
#define LeftMotor_4_pin  11 // 왼쪽 모터 제어선 IN4

const int L_Line = A5;            // 왼쪽 라인트레이서 센서는 A5 핀에 연결
const int C_Line = A4;            // 가운데 라인트레이서 센서는 A4 핀에 연결
const int R_Line = A3;            // 오른쪽 라인트레이서 센서는 A3 핀에 연결

void motor_role(int R_motor, int L_motor);

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
