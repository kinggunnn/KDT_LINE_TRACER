//===============================================================
// 모듈 로딩
//===============================================================
// Test PSH
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

//====================================================
// 작업자 : 박서희
// 최신화 일자 : 2026_02_15
// 용도 : Ultrasonic_sensor
// 함수 기능 : 물체와 초음파 센서간 거리 표시
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
void initUltra() {
	pinMode(echoPin, INPUT);                            // echoPin 입력
	pinMode(trigPin, OUTPUT);                           // trigPin 출력
}

void printUltra() {
	long duration, distance;

	digitalWrite(trigPin, HIGH);                        // trigPin에서 초음파 발생(echoPin도 HIGH)
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	duration = pulseIn(echoPin, HIGH);                  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
	distance = ((float)(340 * duration) / 10000) / 2;
	
	Serial.print("distance:");                          // 물체와 초음파 센서간 거리를 표시
	Serial.print(distance);
	Serial.println(" cm");
	delay(100);
}

//====================================================
// 작업자 : 박서희
// 최신화 일자 : 2026_02_15
// 용도 : IR_Serial
// 함수 기능 : 수신된 IR 리모컨 값을 출력
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
IRrecv irrecv(RECV_PIN);
decode_results results;

void initIR() {
	irrecv.enableIRIn();
}

void checkIR() {
	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		irrecv.resume();
	}
}

//====================================================
// 작업자 : 박서희
// 최신화 일자 : 2026_02_15
// 용도 : Servo_zero
// 함수 기능 : 서보모터 90도 회전
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
Servo servo;

void initServo() {
	servo.attach(2);
	Serial.begin(9600);
	servo.write(90);
	delay(1000);
}

//====================================================
// 작업자 : 박서희
// 최신화 일자 : 2026_02_15
// 용도 : RC_CAR_Serial
// 함수 기능 : 시리얼 입력으로 RC카 주행 제어
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
void initMotor() {
	pinMode(RightMotor_E_pin, OUTPUT);           // 출력모드로 설정
	pinMode(RightMotor_1_pin, OUTPUT);
	pinMode(RightMotor_2_pin, OUTPUT);
	pinMode(LeftMotor_3_pin, OUTPUT);
	pinMode(LeftMotor_4_pin, OUTPUT);
	pinMode(LeftMotor_E_pin, OUTPUT);
}

void commandSerialDirect() {
	if (Serial.available()) {
		char command = Serial.read();
		Serial.print("Recived command : ");
		if (command == 'g') {
			motor_role(HIGH, HIGH);
			Serial.println("직진");
		}
		else if (command == 'b') {
			motor_role(LOW, LOW);
			Serial.println("후진");
		}
		else if (command == 's') {
			analogWrite(RightMotor_E_pin, 0);
			analogWrite(LeftMotor_E_pin, 0);
			Serial.println("정지");
		}
		else {
			Serial.println("Wrong command");
		}
	}
}