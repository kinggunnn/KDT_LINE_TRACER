#include "main_function.h"

//====================================================
// 작업자 : 김효리
// 최신화 일자 : 2026_02_18
// 용도 : turnCorner90
// 함수 기능 : 직각 라인 주행 기능
//            직각 코너에서 라인을 잠깐 잃더라도, 제자리 회전으로 라인을 다시 잡는 순간까지 회전 수행
//            센터(IR) 센서가 라인을 연속으로 감지(stable)하면 라인 재획득으로 판단하고 회전을 종료함(디바운스 적용)
//            타임아웃(timeout)으로 무한 회전을 방지함
//            ★★★ 이 코드 핵심 : (111) 안뜬다는 가정하에(차선이 안두껍다면), 직진 회전 하는것.
//                         만약, 111이 뜨면 우선은 왼쪽 탐색후, 없으면 오른쪽으로 방향 전환해서 탐지함.
// 매개변수 :  dir             (-1: 좌회전, +1: 우회전)  ※ 부호만 사용
//            pivotSpeed      (제자리 회전 속도, 0~255 권장)
//            timeoutMs       (최대 회전 허용 시간(ms), 초과 시 실패 처리)
//            stableCountNeed (센터 센서가 연속으로 라인을 감지해야 하는 횟수, 값 튐 방지용)
// return 값 :(bool) true  - 라인 재획득 성공(회전 종료)
//            (bool) false - 타임아웃 실패(라인 재획득 못함)
//====================================================

bool turnCorner90(int pivotSpeed = 110,
                       unsigned long timeoutMs = 900,
                       int stableCountNeed = 3,
                       unsigned long probeMs = 120) // 방향 애매할 때 한쪽 먼저 살짝 탐색
{
  // 람다 함수 : IR 센서 값 디지털로 읽기
  auto readLCR = [&](int &L, int &C, int &R) {
    L = digitalRead(L_Line);
    C = digitalRead(C_Line);
    R = digitalRead(R_Line);
  };

  // 람다 함수 : motor_role 함수에 따른 모터 속도 제어
  auto pivot = [&](int dir) {
    // dir -1: 좌회전(오른쪽 전진, 왼쪽 후진), dir +1: 우회전
    if (dir < 0) motor_role(+pivotSpeed, -pivotSpeed); //motor_role이라는 함수가 있을때  motor_role(왼쪽 속도, 오른쪽 속도)
    else         motor_role(-pivotSpeed, +pivotSpeed); 
  };

  // 1) 시작 시점 센서로 방향 1차 결정
  int L, C, R;
  readLCR(L, C, R);

  int dir = 0;
  if ((L==1 && C==0 && R==0) || (L==1 && C==1 && R==0)) dir = -1;      // 100, 110이면 좌측 코너 가능성↑
  else if ((L==0 && C==0 && R==1) || (L==0 && C==1 && R==1)) dir = +1; // 001, 011이면 우측 코너 가능성↑
  else dir = -1; // 그래도 애매하면 일단 왼쪽부터 탐색

  unsigned long t0 = millis();    // 회전을 시작한 시각
  int stable = 0;                 // 센터 센서(C)가 라인을 “연속으로” 잡은 횟수 카운트

  // 2) 만약 애매해서 lastDir/기본값으로 정했는데 틀릴 수 있으니
  //    초반 probeMs 동안은 "잡히는지" 보고, 안 잡히면 반대로 전환하는 탐색 로직 추가
  bool probed = false; //탐색(probe) 방향 반전 시도를 이미 했는지를 기록하는 플래그. 무한 방향 반전 하면 안되니까.

  // 타임아웃 전까지 계속 회전하면서, 센터 센서(C)가 라인을 '연속으로' 잡으면 멈추고 성공 반환
  while (millis() - t0 < timeoutMs) {  // 타임아웃 전까지만 회전. 무한 회전 방지
    pivot(dir);                        // dir 방향으로 제자리 회전

    readLCR(L, C, R);                  // IR 센서값을 다시 최신으로 읽어오기

    // 재획득 조건: 센터가 연속 stableCountNeed번 1이면 확정(디바운스)
    if (C == 1) {                     // 센터가 검정(1)을 감지하면 
      stable++;                       // 센터가 1인 상태가 연속으로 몇 번 유지되는지 카운트 증가
      if (stable >= stableCountNeed) { // 센터 1인 상태가 3번 이상 찍히면 라인 재획득 잘했다고 탐지
        motor_role(0, 0);             // 모터 정지. 회전 종료.
        delay(20);                   
        return true;
      }
    } else {
      stable = 0;                     // 다시 시작.
    }

    // probe: 초반에 아무것도 못 잡고(특히 C가 계속 0이고 L/R도 안 잡히면) 방향 반대로 한 번 바꿔보기
    if (!probed && (millis() - t0 > probeMs)) {
      // 아직도 라인을 거의 못 느끼면(000에 가까운 상황) 반대로 시도
      if (L==0 && C==0 && R==0) {
        dir = -dir;      // 방향 반전
        probed = true;   // 한 번만 반전
      } else {
        probed = true;   // 뭔가 잡히면 그대로 가자
      }
    }

    delay(3);
  }

  motor_role(0, 0);    // 모터 정지
  return false;
}