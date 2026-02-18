

#include "my_function.h"
//hi 테스트중

int SL = 1, SC = 1, SR = 1;


void setup() {
  EduServo.attach(2);                       // 서보모터 PWM 디지털입출력 2번핀 연결
  
  pinMode(echoPin, INPUT);                  // echoPin 입력
  pinMode(trigPin, OUTPUT);                 // trigPin 출력


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
  lineTrace_step();

}
