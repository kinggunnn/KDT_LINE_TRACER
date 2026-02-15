#ifndef MY_FUNCTION_H
#define MY_FUNCTION_H

#include <Arduino.h>
#include <Servo.h> // 서보모터 헤더파일 추가

extern Servo myservo; // 서보모터 생성자 'myservo'가 어딘가에 있다는걸 알려주는 부분.


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

// 서범 : 서보 모터 정의
void servo_control(int angle);

// 서범 : 라인트레이서 정의
void line_value_serial(uint8_t pin1, uint8_t pin2, uint8_t pin3, int delay__);

//

#endif
