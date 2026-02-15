

#include "my_function.h"

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
}

void loop() {
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
