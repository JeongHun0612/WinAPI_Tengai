#pragma once

/*
- API 공용 함수
ㄴ 문제가 있다..
ㄴ 최초 설계 단계에서 게임을 고려하고 만든 타이머들이 아니기 때문에 정밀도가 떨어진다.
ㄴ

timeGetTime (윈도우가 시작되고 1분이 지났으면 60000 리턴)
GetTickCount (부팅 시간 체크 -> 부팅된 이후 1초에 1000씩 틱이 증가한다. 약 50일 이후 오류)

하지만 이 함수는 한계가 있는데 바로 반환 시간이 최대 DWORD(32비트)라는 것이다.
날짜로 따지면 49.7일인데, 49.7일 동안 윈도우즈를 종료하지 않을 경우 0으로 초기화 되는 것이다.

GetTickCount64

- 타이머
ㄴ 시간을 측정하는 함수들은 기본적으로 윈도우가 시작된 이후 지난 시간을 Milli Second 단위로 변환 (1000분의 1초)
ㄴ 밀리 세컨은 기본적으로 정밀도가 떨어진다. -> 게임에서
 ㄴ 그렇기 때문에 보다 높은 정밀도를 원한다면 고 해상도 타이머를 추가해서 사용해야 한다.

 - 타이머를 구현할때는 보통 해상도와 클럭을 알고 있어야 한다.

◈ 해상도

- 다양한 시간 함수들은 시간을 측정하기 위한 각각의 틱 계산 로직이 있다.
	ㄴ 이 기준은 1분을 중점으로 삼았을 때 얼마나 많은 프레임으로 나눌 수 있는지 계산

- 1분동안 얼마나 많은 틱으로 나눠서 시간의 정확도를 높이느냐가 고해상도와 저해상도의 차이를 발생 시킨다.

◈ 클럭 (진동수)

- 타이머에서 얘기하는 클럭은 CPU 클럭

- 클럭 자체는 디지털 회로의 전기적 진동 수이며 헤르츠 단위로 표기하는게 일반적 (Hz)
ㄴ EX : 1초에 1Hz면 이진수의 신호를 한번 준다는 얘기 (0 또는 1)
	ㄴ 1 비트를 옮길 수 있다는 얘기
	ㄴ 1GHz는 10에 9제곱 -> 10억번
		ㄴ 3.7GHz는 37억번 (1초에 36 비트를 옮길 수 있다.)

단위
ㄴ Milli Second
ㄴ 10 Milli Second
ㄴ 100 Milli Second
*/

class Timer
{
private:
	float _timeScale;				// 경과 시간
	float _timeElapsed;				// 마지막 시간과 현재 시간의 경과값
	bool _isHardware;				// 하드웨어에 따라 고성능 타이머를 사용할지

	__int64 _curTime;				// 현재 시간
	__int64 _lastTime;				// 이전 시간
	__int64 _periodFrequency;		// 시간 주기

	unsigned long _frameRate;		// 초당 프레임 수
	unsigned long _FPSFrameCount;	// 초당 프레임 카운트
	float _FPSTimeElapsed;			// 프레임에 대한 시간 경과량
	float _worldTime;				// 전체 시간

public:
	HRESULT init(void);
	void tick(float lockFPS = 0.0f);

	unsigned long getFrameRate(char* str = nullptr) const;
	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }

	Timer() {}
	~Timer() {}
};