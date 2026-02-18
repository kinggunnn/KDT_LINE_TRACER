#include "LSB_function.h"

// "강한 우회전 / 강한 좌회전 / 직진 / 정지" 구현한 코드
// + 흰색이 500ms 이상 유지되면 정지

int SL = 1, SC = 1, SR = 1;
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

  myservo.attach(2); // 서범 : 서보 모터를 몇 번 핀으로 설정할지
}

void loop() {
  // 서범 : 서보모터 
  //int servo_angle = 90; 
  //servo_control(servo_angle);

  // 서범 : 라인트레이서 값을 100ms 간격으로 출력하는 함수 -> 시각화용
  //line_value_serial(R_Line, C_Line, L_Line, 1000);

  // 서범 idea : 지금은 digital로 읽어와서 단순 0/1로 나누고있는데,
  //             analog로 읽어와서(0~1023) 검정색과 흰색의 출력값을 보고 이진화 하는것도 성능 개선을 위한 하나의 방법인 거 같음
  int L = digitalRead(L_Line);
  int C = digitalRead(C_Line);
  int R = digitalRead(R_Line);

  // 서범 : 현재 값(0/1)이 어떻게 출력되는지 확인하는 코드
  // Serial.print("digital : ");
  // Serial.print(L); Serial.print(", ");
  // Serial.print(C); Serial.print(", ");
  // Serial.print(R); Serial.print("   ");

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
    }
  } else {
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
