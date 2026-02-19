#include "main_function.h"

// "강한 우회전 / 강한 좌회전 / 직진 / 정지" 구현한 코드
// + 흰색이 500ms 이상 유지되면 정지

unsigned long lostTime = 0;


void setup() {
  
  pinMode(RightMotor_E_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);

  // 라인트레이서 핀 번호
  pinMode(L_Line, INPUT); //A5 : 왼쪽
  pinMode(C_Line, INPUT); //A4 : 가운데
  pinMode(R_Line, INPUT); //A3 : 오른쪽

  Serial.begin(9600);
  Serial.println("hello arduino");

  servo.attach(2); // 서범 : 서보 모터를 몇 번 핀으로 설정할지
}

void loop() {  // 서범 : 서보모터 
  //int servo_angle = 90; 
  //servo_control(servo_angle);

  // 서범 : 라인트레이서 값을 100ms 간격으로 출력하는 함수 -> 시각화용
  //line_value_serial(R_Line, C_Line, L_Line, 1000);

  // 서범 : 기본적인 주행(직진, 우회전, 좌회전, 강한 우회전, 강한 좌회전, 검출되지 않을 때(모두 흰색), 모두 검출될 때(모두 검은색))
  int L = digitalRead(L_Line);
  int C = digitalRead(C_Line);
  int R = digitalRead(R_Line);
  driving_sys(L, C, R, lostTime);
}
