#include "my_function.h"

/// 메인 -> 브런치 테스트 2


int SL = 1, SC = 1, SR = 1;

void setup() {
  pinMode(RightMotor_E_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);

  pinMode(L_Line, INPUT);
  pinMode(C_Line, INPUT);
  pinMode(R_Line, INPUT);

  Serial.begin(9600);
  Serial.println("hello arduino");

  myservo.attach(2); // 서범 : 서보 모터를 몇 번 핀으로 설정할지
  Serial.begin(9600); // 서범 : 시리얼 초기화 
}

void loop() {
  // 서범 : 서보모터 
  int servo_angle = 90; 
  servo_control(servo_angle);

  // 서범 : 라인트레이서 값 출력하는 함수
  line_value_serial(A3, A4, A5, 100);



  int L = digitalRead(L_Line);
  int C = digitalRead(C_Line);
  int R = digitalRead(R_Line);

  Serial.print("digital : ");
  Serial.print(L); Serial.print(", ");
  Serial.print(C); Serial.print(", ");
  Serial.print(R); Serial.print("   ");

  if (L == LOW && C == LOW && R == LOW) {  // 0 0 0
    L = SL; C = SC; R = SR;               // 이전값 유지
  }

  if (L == LOW && C == HIGH && R == LOW) {      // 0 1 0
    motor_role(HIGH, HIGH);
    Serial.println("직진");
  }
  else if (L == LOW && R == HIGH) {             // 우측 감지
    motor_role(LOW, HIGH);
    Serial.println("우회전");
  }
  else if (L == HIGH && R == LOW) {             // 좌측 감지
    motor_role(HIGH, LOW);
    Serial.println("좌회전");
  }
  else if (L == HIGH && R == HIGH) {            // 정지
    analogWrite(RightMotor_E_pin, 0);
    analogWrite(LeftMotor_E_pin, 0);
    Serial.println("정지");
  }

  SL = L; SC = C; SR = R;
}
