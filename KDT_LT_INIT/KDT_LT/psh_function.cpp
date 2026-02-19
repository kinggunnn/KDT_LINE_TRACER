#include "main_function.h"

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
// IRrecv irrecv(RECV_PIN);
// decode_results results;

// void initIR() {
// 	irrecv.enableIRIn();
// }

// void checkIR() {
// 	if (irrecv.decode(&results)) {
// 		Serial.println(results.value, HEX);
// 		irrecv.resume();
// 	}
// }

//====================================================
// 작업자 : 박서희
// 최신화 일자 : 2026_02_15
// 용도 : Servo_zero
// 함수 기능 : 서보모터 90도 회전
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
void initServo() {
	servo.attach(2);	// servo객체가 2번 핀을 통해 서보를 제어하도록 연결
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

//====================================================
// 작업자 : 박서희
// 최신화 일자 : 2026_02_19
// 용도 : basePWM
// 함수 기능 : 출발 임계 PWM을 찾기 위해 1초마다 속도를 올리며 전진시키고,
//			   255 도달 시 측정 종료 및 모터 정지
// 매개변수 : 없음
// return 값 : void(없음)
//====================================================
int thresholdPWM = 0;		// 현재 모터에 주는 PWM값(0~255)
bool end = false;			// 측정 끝났는지 여부
unsigned long lastTime = 0;	// 마지막으로 PWM 올렸던 시간(1초마다 갱신)

void basePWM() {
	if (!end) {
		// 모터 방향 고정(전진)
		digitalWrite(RightMotor_1_pin, HIGH);
		digitalWrite(RightMotor_2_pin, LOW);
		digitalWrite(LeftMotor_3_pin, HIGH);
		digitalWrite(LeftMotor_4_pin, LOW);

		if (millis() - lastTime > 1000) {
			// 양쪽 Enable(PWM) 핀에 동일한 thresholdPWM 줘서 속도 증가
			analogWrite(RightMotor_E_pin, thresholdPWM);
			analogWrite(LeftMotor_E_pin, thresholdPWM);
						
			// 현재 PWM 시리얼 출력
			Serial.print("PWM: ");
			Serial.println(thresholdPWM);

			// 5씩 증가
			thresholdPWM += 5;

			// PWM이 최대(255)가 되면 종료 처리
			if (thresholdPWM >= 255) {
				thresholdPWM = 255;
				end = true;

				analogWrite(RightMotor_E_pin, 0);
				analogWrite(LeftMotor_E_pin, 0);
			}

			// 시간 갱신
			lastTime = millis();	// 아두이노 켜진 이후 흐른 시간(ms)
		}
		return;
	}
}