//===============================================================
// 모듈 로딩
//===============================================================

#include "my_function.h"

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