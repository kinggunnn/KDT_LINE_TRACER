//===============================================================
// 모듈 로딩
//===============================================================

#include "my_function.h"

#include <Servo.h>
#include <SoftwareSerial.h>

Servo EduServo;


// 전역변수 정의(여기서 메모리 할당)
int Ultra_d = 0;

static SoftwareSerial bluetooth(BT_RXD, BT_TXD);
int L_MotorSpeed = 153;
int R_MotorSpeed = 153;

//아래는 예시니까 지우고 쓰세용~
//아래 양식은 함수 구현하면 구현하는사람이 적어주기~
//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_14
// 용도 : 크리스마스 트리에 올릴 led 기능
// 함수 기능 : LED가 점점 밝아지다가 10ms 딜레이 후 다시 점점 어두워 진다
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


//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : 초음파 센서 거리 측정
// 함수 기능 : 트리거 신호를 발생시키고 echo 펄스 길이로 거리(mm)를 계산하여 반환
// 매개변수 : 없음
// return 값 : int distance (mm)
//====================================================
int Ultrasonic() {
  long duration, distance;
  digitalWrite(trigPin, HIGH);                                            // trigPin에서 초음파 발생(echoPin도 HIGH)        
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 1000) / 2;

  Serial.print("DIstance:");  // 물체와 초음파 센서간 거리를 표시.
  Serial.println(distance);

  return distance;
}

//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : 서보모터로 좌/우 거리 비교 후 회피 방향 결정
// 함수 기능 : 서보를 좌(30도) / 우(150도)로 회전시키며 거리 측정 후 더 먼 방향을 반환
// 매개변수 : 없음
// return 값 : int val (0: 우회전, 1: 좌회전)
//====================================================
int Servo_con() {
  int val;
  EduServo.write(30);
  delay(300);
  int Ult_30 = Ultrasonic();
  delay(700);
  EduServo.write(150);
  delay(300);
  int Ult_150 = Ultrasonic();
  delay(700);

  if (Ult_30 > Ult_150) {
    val = 1;
  } else {
    val = 0;
  }
  EduServo.write(90);
  return val;
}

//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : 모터 정지(PWM 0)
// 함수 기능 : 좌/우 모터 Enable(PWM)을 0으로 설정하여 구동을 멈춤
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
void stop_motors() {
  analogWrite(RightMotor_E_pin, 0);
  analogWrite(LeftMotor_E_pin, 0);
}

//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : 라인트레이싱 1스텝 수행
// 함수 기능 : 좌/중/우 라인 센서를 읽고(0,0,0이면 이전값 유지) 방향에 따라 모터 제어
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
void lineTrace_step() {
  // 이전값 유지용 상태(전역 안 쓰고 여기서 유지)
  static int SL = HIGH, SC = HIGH, SR = HIGH;

  int L = digitalRead(L_Line);
  int C = digitalRead(C_Line);
  int R = digitalRead(R_Line);

  Serial.print("digital : ");
  Serial.print(L);
  Serial.print(", ");
  Serial.print(C);
  Serial.print(", ");
  Serial.print(R);
  Serial.print("   ");

  // 0 0 0이면 직전값 유지
  if (L == LOW && C == LOW && R == LOW) {
    L = SL;
    C = SC;
    R = SR;
  }

  if (L == LOW && C == HIGH && R == LOW) {  // 0 1 0
    motor_role(HIGH, HIGH);
    Serial.println("직진");
  } else if (L == LOW && R == HIGH) {  // 우측 감지
    motor_role(LOW, HIGH);
    Serial.println("우회전");
  } else if (L == HIGH && R == LOW) {  // 좌측 감지
    motor_role(HIGH, LOW);
    Serial.println("좌회전");
  } else if (L == HIGH && R == HIGH) {  // 정지
    stop_motors();
    Serial.println("정지");
  }

  // 이전값 저장
  SL = L;
  SC = C;
  SR = R;
}

//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : 초음파 기반 장애물 회피 주행 1스텝
// 함수 기능 : 전방 거리 측정 후 임계값에 따라 직진/후진/서보 스캔 후 회전 동작 수행
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
void smartcar_step() {
  int Ultra_d = Ultrasonic();
  Serial.println(Ultra_d);

  motor_role(HIGH, HIGH);  // 기본 직진

  if (Ultra_d < 250) {
    if (Ultra_d < 150) {
      Serial.println("150 이하.");
      motor_role(LOW, LOW);  // 후진
      delay(1000);
      stop_motors();
      delay(200);
    } else {
      stop_motors();
      delay(200);

      Serial.println("150 이상.");
      int val = Servo_con();  // 0: 우회전, 1: 좌회전 (너 기존 로직 그대로)

      if (val == 0) {
        Serial.println("우회전.");
        stop_motors();
        delay(500);

        motor_role(LOW, LOW);  // 후진
        delay(500);

        motor_role(LOW, HIGH);  // 우회전(제자리 회전)
        delay(800);
      } else if (val == 1) {
        Serial.println("좌회전.");
        stop_motors();
        delay(500);

        motor_role(LOW, LOW);  // 후진
        delay(500);

        motor_role(HIGH, LOW);  // 좌회전(제자리 회전)
        delay(800);
      }
    }
  }
}


//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : 블루투스 브릿지 초기화
// 함수 기능 : SoftwareSerial(블루투스) 통신 속도(baudrate) 설정
// 매개변수 : long baud (예: 9600)
// return 값 : void(없음)
//====================================================
void bt_bridge_init(long baud) {
  bluetooth.begin(baud);
}
//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : 블루투스 브릿지 1스텝
// 함수 기능 : 블루투스 수신 데이터를 Serial로 전달하고, Serial 입력을 블루투스로 전달
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
void bt_bridge_step() {
  if (bluetooth.available()) Serial.write(bluetooth.read());
  if (Serial.available()) bluetooth.write(Serial.read());
}

// mode 정의 (숫자 쓰는 것보다 이게 덜 헷갈림)
enum DriveMode : uint8_t {
  MODE_GO_BACK = 0,
  MODE_RIGHT = 1,
  MODE_LEFT = 2,
  MODE_STOP = 3,
  MODE_ROT_L = 4,
  MODE_ROT_R = 5
};

//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : RC 모드 - 우측 편향 주행(내부 함수)
// 함수 기능 : 방향핀 설정 후 우측 모터 PWM을 낮춰 차량이 우측으로 틀어지게 제어
// 매개변수 : int R_motor (HIGH/LOW), int L_motor (HIGH/LOW)
// return 값 : void(없음)
//====================================================
static void right_role(int R_motor, int L_motor) {
  digitalWrite(RightMotor_1_pin, R_motor);
  digitalWrite(RightMotor_2_pin, !R_motor);
  digitalWrite(LeftMotor_3_pin, L_motor);
  digitalWrite(LeftMotor_4_pin, !L_motor);

  analogWrite(RightMotor_E_pin, max((int)(R_MotorSpeed * 0.4), 90));
  analogWrite(LeftMotor_E_pin, 255);
}
//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : RC 모드 - 좌측 편향 주행(내부 함수)
// 함수 기능 : 방향핀 설정 후 좌측 모터 PWM을 낮춰 차량이 좌측으로 틀어지게 제어
// 매개변수 : int R_motor (HIGH/LOW), int L_motor (HIGH/LOW)
// return 값 : void(없음)
//====================================================
static void left_role(int R_motor, int L_motor) {
  digitalWrite(RightMotor_1_pin, R_motor);
  digitalWrite(RightMotor_2_pin, !R_motor);
  digitalWrite(LeftMotor_3_pin, L_motor);
  digitalWrite(LeftMotor_4_pin, !L_motor);

  analogWrite(RightMotor_E_pin, 255);
  analogWrite(LeftMotor_E_pin, max((int)(L_MotorSpeed * 0.4), 90));
}
//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : RC 모드 - 좌회전 제자리 회전(내부 함수)
// 함수 기능 : 좌/우 모터를 반대 방향으로 돌려 제자리 좌회전 수행
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
static void left_rotation() {
  digitalWrite(RightMotor_1_pin, HIGH);
  digitalWrite(RightMotor_2_pin, LOW);
  digitalWrite(LeftMotor_3_pin, LOW);
  digitalWrite(LeftMotor_4_pin, HIGH);

  analogWrite(RightMotor_E_pin, R_MotorSpeed);
  analogWrite(LeftMotor_E_pin, L_MotorSpeed);
}

//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : RC 모드 - 우회전 제자리 회전(내부 함수)
// 함수 기능 : 좌/우 모터를 반대 방향으로 돌려 제자리 우회전 수행
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
static void right_rotation() {
  digitalWrite(RightMotor_1_pin, LOW);
  digitalWrite(RightMotor_2_pin, HIGH);
  digitalWrite(LeftMotor_3_pin, HIGH);
  digitalWrite(LeftMotor_4_pin, LOW);

  analogWrite(RightMotor_E_pin, R_MotorSpeed);
  analogWrite(LeftMotor_E_pin, L_MotorSpeed);
}
//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : RC 모드 - 주행 모드 적용(내부 함수)
// 함수 기능 : mode 값에 따라 직진/후진/좌우 편향/제자리 회전/정지 동작을 실행
// 매개변수 : uint8_t mode, int R_motor (HIGH/LOW), int L_motor (HIGH/LOW)
// return 값 : void(없음)
//====================================================
static void apply_drive_mode(uint8_t mode, int R_motor, int L_motor) {
  switch (mode) {
    case MODE_GO_BACK: motor_role(R_motor, L_motor); break;
    case MODE_RIGHT:   right_role(R_motor, L_motor); break;
    case MODE_LEFT:    left_role(R_motor, L_motor);  break;
    case MODE_ROT_L:   left_rotation();              break;
    case MODE_ROT_R:   right_rotation();             break;
    default:           stop_motors();                break;
  }
}

void rc_bt_init(long baud) {
  bluetooth.begin(baud);
}

//====================================================
// 작업자 : 임진효
// 최신화 일자 : 2026_02_18
// 용도 : RC 블루투스 제어 1스텝
// 함수 기능 : 블루투스 명령 1글자를 읽어 주행 상태를 업데이트하고 모터 동작을 실행
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
void rc_bt_step() {
  // 상태를 전역이 아니라 함수 내부 static으로 유지
  static int R_motor = HIGH;
  static int L_motor = HIGH;
  static uint8_t mode = MODE_STOP;

  if (!bluetooth.available()) return;

  char cmd = (char)bluetooth.read();
  Serial.print(cmd);

  // 파싱(기존 control_SmartCar 역할)
  if (cmd == 'g') {
    R_motor = HIGH;
    L_motor = HIGH;
    mode = MODE_GO_BACK;
  } else if (cmd == 'b') {
    R_motor = LOW;
    L_motor = LOW;
    mode = MODE_GO_BACK;
  } else if (cmd == 'r') {
    mode = MODE_RIGHT;
  } else if (cmd == 'l') {
    mode = MODE_LEFT;
  } else if (cmd == 's') {
    mode = MODE_STOP;
  } else if (cmd == 'q') {
    mode = MODE_ROT_L;
  } else if (cmd == 'w') {
    mode = MODE_ROT_R;
  } else {
    return;
  }

  // 적용(기존 loop의 mode 분기 역할)
  if (mode == MODE_STOP) stop_motors();
  else apply_drive_mode(mode, R_motor, L_motor);
}
