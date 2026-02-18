//===============================================================
// 모듈 로딩
//===============================================================

#include "LSB_function.h"

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

  int val_1_d = digitalRead(pin1); 
  int val_2_d = digitalRead(pin2);
  int val_3_d = digitalRead(pin3);
  
  Serial.println("** Analog result **");
  Serial.print("L:");
  Serial.print(val_1);
  Serial.print(" C:");
  Serial.print(val_2);
  Serial.print(" R:");
  Serial.println(val_3);

  Serial.println("** Digital result **");
  Serial.print("L:");
  Serial.print(val_1_d);
  Serial.print(" C:");
  Serial.print(val_2_d);
  Serial.print(" R:");
  Serial.println(val_3_d);
  delay(delay__);
}


//====================================================
// 작업자 : 이서범
// 최신화 일자 : 2026_02_15
// 용도 : motor_control
// 함수 기능 : 바퀴 속도 및 방향 제어
// 매개변수 : 오른쪽 on/off , 왼쪽 on/off , 오른쪽 speed , 왼쪽 speed
// return 값 : void(없음)
//====================================================
void motor_control(int R_motor, int L_motor, int R_speed, int L_speed) {
  digitalWrite(RightMotor_1_pin, R_motor);
  digitalWrite(RightMotor_2_pin, !R_motor);
  digitalWrite(LeftMotor_3_pin, L_motor);
  digitalWrite(LeftMotor_4_pin, !L_motor);

  analogWrite(RightMotor_E_pin, R_speed);  // 우측 모터 속도값
  analogWrite(LeftMotor_E_pin, L_speed);   // 좌측 모터 속도값
}

void Right_role(int R_motor, int L_motor, int Speed){
   digitalWrite(RightMotor_1_pin, R_motor);
   digitalWrite(RightMotor_2_pin, !R_motor);
   digitalWrite(LeftMotor_3_pin, L_motor);
   digitalWrite(LeftMotor_4_pin, !L_motor);
   
   analogWrite(RightMotor_E_pin, max(Speed*0.4,50));  // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, min(Speed*1.4,255));   // 좌측 모터 속도값
}

void Left_role(int R_motor, int L_motor, int Speed){
   digitalWrite(RightMotor_1_pin, R_motor);
   digitalWrite(RightMotor_2_pin, !R_motor);
   digitalWrite(LeftMotor_3_pin, L_motor);
   digitalWrite(LeftMotor_4_pin, !L_motor);
   
   analogWrite(RightMotor_E_pin, min(Speed*1.4,255));  // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, max(Speed*0.2,50));   // 좌측 모터 속도값   
}

