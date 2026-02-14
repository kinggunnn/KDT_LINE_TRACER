
// pin 선언
#define LED1 5

//통신 관련 설정 
#define SERAL_SPEED 9600 //시리얼 통신 속도
#include "function_main.h"


void setup() {
  // put your setup code here, to run once:
  pinMode(LED1,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  ///메인은 일단 건들지 마세용~~ 예시코드만 넣어놀게요~
  tree(LED1);

  delay(1000);

}
