#pragma once

// 간소화 시키고 싶은 로직 -> 수학적 기능을 정의하면 좋다.

// 디그리 1도의 라디안
#define DEG_TO_RAD		0.017453f

#define PI				3.141592653f
#define PI_2			6.283185308f

// 각도 표기 -> 라디안 표기 변환
#define DEGREE_RADIAN(_deg)			(PI * (_deg) / 180.f)

/*
- 반올림 오차 (Rounding Error)

- 부동소수는 기본적으로 실수를 정확하게 표현하는게 불가능
ㄴ 이유는 수학적으로 실수는 무한한 반면 이 실수를 유한한 비트로 표현을 하기 때문
ㄴ 그렇기때문에 컴퓨터는 어쩔 수 없이 근사값으로 처리를 한다.

- 이게 부동소수점 반올림 오차
ㄴ 컴퓨터는 실수를 이진수의 형태로 저장
ㄴ 이러한 특징 때문에 오차 범위가 발생하고 정확한 계산을 위해서는 상수값이 반드시 필요하다.

- 2D 좌표계에서는 체감을 상대적으로 못할 수 있으나 3D에서는 체감이 확 되는 부분
*/

#define FLOAT_EPSILION		0.001f

/*
- C++ 캐스팅 연산자는 4종류

1. reinterpret_cast
ㄴ 간단히 얘기하면 데이터가 메모리상에 배열되는 순서가 역순으로 들어올 수 있다.
ㄴ 이는 프로그래머가 의도한 상황을 연출하는 경우가 아니기 때문에 대부분 -> 버그


*/

// 실수 -> 정수
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILION)

// 두 실수가 같은지 비교
// ㄴ 여기서 사용된 절대값은 소수점 차의 절대값 반환
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILION)


namespace MY_UTIL
{
	// 두 점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);

	// 스타트 -> 엔드 -> 각을 라디안으로
	float getAngle(float startX, float startY, float endX, float endY);
}