//===============================================================
// 모듈 로딩
//===============================================================

#include "my_function.h"

Servo myservo;  // 'myservo'라는 서보모터 생성자를 만드는 부분


//====================================================
// 작업자 : 이서범
// 최신화 일자 : 2026_02_15
// 용도 : servo_control
// 함수 기능 : 서보 모터 특정 각도로 꺽기
// 매개변수 : 각도
// return 값 : void(없음)
//====================================================
void servo_control(int angle) {
  myservo.write(angle);
}


//====================================================
// 작업자 : 이서범
// 최신화 일자 : 2026_02_15
// 용도 : line_value_serial
// 함수 기능 : 라인 시리얼 값 출력하기
// 매개변수 : line 핀1, line 핀2, line 핀3, 출력 delay 시간(line 핀 번호 차례대로 3개 입력하기)
// return 값 : void(없음)
//====================================================
void line_value_serial(uint8_t pin1, uint8_t pin2, uint8_t pin3, int delay__) {
  int val_1 = analogRead(pin1); // pin1 = A3 이런식으로 받아옴. -> A3는 내부적으로 define돼서 숫자로 처리됨
  int val_2 = analogRead(pin2);
  int val_3 = analogRead(pin3);
  
  Serial.print("1:");
  Serial.print(val_1);
  Serial.print(" 2:");
  Serial.print(val_2);
  Serial.print(" 3:");
  Serial.println(val_3);
  delay(delay__);
}



//-------
//아래는 예시니까 지우고 쓰세용~
//아래 양식은 함수 구현하면 구현하는사람이 적어주기~
//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_14
// 용도 : motor_role
// 함수 기능 : 바퀴 속도 제어
// 매개변수 : LED
// return 값 : void(없음)
//====================================================
void motor_role(int R_motor, int L_motor) {
  digitalWrite(RightMotor_1_pin, R_motor);
  digitalWrite(RightMotor_2_pin, !R_motor);
  digitalWrite(LeftMotor_3_pin, L_motor);
  digitalWrite(LeftMotor_4_pin, !L_motor);

  analogWrite(RightMotor_E_pin, R_MotorSpeed);  // 우측 모터 속도값
  analogWrite(LeftMotor_E_pin, L_MotorSpeed);   // 좌측 모터 속도값
}