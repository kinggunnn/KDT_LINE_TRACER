
// pin 선언
#define LED1 5

//test for git branch


//통신 관련 설정 
#define SERAL_SPEED 9600 //시리얼 통신 속도
#include "function_main.h"


void setup() {
  // put your setup code here, to run once:
  pinMode(LED1,OUTPUT);

}

void loop() {
  // 각자 함수 돌려보세용~
  tree(LED1);

  delay(1000);

}
