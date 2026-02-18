//===============================================================
// 모듈 로딩
//===============================================================

#include "main_function.h"



//====================================================
// 작업자 : 이서범
// 최신화 일자 : 2026_02_15
// 용도 : servo_control
// 함수 기능 : 서보 모터 특정 각도로 꺽기
// 매개변수 : 각도
// return 값 : void(없음)
//====================================================
void servo_control(int angle) {
  servo.write(angle);
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

//====================================================
// 작업자 : 이서범
// 최신화 일자 : 2026_02_18
// 용도 : driving_sys
// 함수 기능 : 기본적인 주행(직진, 우회전, 좌회전, 강한 우회전, 강한 좌회전, 검출되지 않을 때(모두 흰색), 모두 검출될 때(모두 검은색))
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
void driving_sys(int L, int C, int R, unsigned long &lostTime) {
  // 서범 : 모든 값에서 차선이 검출되지 않을 때, 500ms 이후 정지하는 코드
  if (L == LOW && C == LOW && R == LOW) {  // 0 0 0
    // 200ms 이상 해당 미검출 로직으로 들어오면 정지하기
    if (lostTime == 0) {
      lostTime = millis(); // 밀리 단위로 처음 로직에 들어갔을 때의 시간 저장
    }
    if (millis() - lostTime > 5000) { // 반복돼서 시간이 500ms가 넘어가면 정지.
      analogWrite(RightMotor_E_pin, 0);
      analogWrite(LeftMotor_E_pin, 0);
      Serial.println("500ms 라인 미검출로 정지");
      return;
    }
    // 5초 전까지는 이전 센서값으로 '치환'해서 조향 유지
    L = SL; C = SC; R = SR; 
  }
  else {
    lostTime = 0;
  }
  // 직진
  if (L == LOW && C == HIGH && R == LOW) {      // 0 1 0
    motor_control(HIGH, HIGH, 150, 150); // R , L , R_S , L_S
    Serial.println("직진");
  }
  // 약한 우회전
  else if (L == LOW && C == HIGH && R == HIGH) {  // 0 1 1
    motor_control(HIGH, HIGH, 40, 150);
    Serial.println("우회전");
  }
  // 약한 좌회전
  else if (L == HIGH && C == HIGH && R == LOW) {  // 1 1 0      
    motor_control(HIGH, HIGH, 150, 40);
    Serial.println("좌회전");
  }
  // 강한 우회전
  else if (L == LOW && C == LOW && R == HIGH) {  // 0 0 1
    motor_control(HIGH, HIGH, 0, 150);
    Serial.println("강한 우회전");
  }
  // 강한 좌회전
  else if (L == HIGH && C == LOW && R == LOW) {  // 1 0 0
    motor_control(HIGH, HIGH, 150, 0);
    Serial.println("강한 좌회전");
  }
  //정지 -> 모두 검정색이면
  else if (L == HIGH && C == HIGH && R == HIGH) {    // 1 1 1
    analogWrite(RightMotor_E_pin, 0);
    analogWrite(LeftMotor_E_pin, 0);
    Serial.println("정지");
  }
  SL = L; SC = C; SR = R;
}



// 혹시 모르는 추가 함수임
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

