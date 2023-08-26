#pragma once

// 4005라는 경고를 무시하겠다.
#pragma warning(disable : 4005)
// 4005 : DXGI 등 그래픽 인터페이스에서 매크로 관련하여 출력되는 경고
//#include "targetver.h" 

/*
▶ Stdafx

- MS의 비쥬얼 스튜디오를 이용하여 프로젝트를 만들면 생성되는 클래스이다.
	ㄴ 이 친구가 의미하는 바는 표준 어플리케이션 프레임워크의 틀

- MS에서 개발자들의 능률 향상을 위해 만들어둔 PCH 파일
	ㄴ 자주 쓰이는 여러가지 헤더들은 미리 컴파일 해두어 이후 다시 컴파일하지 않고 사용하게 된다.

- 개발에 초기 구축 단계에서는 필요성을 못느끼지만 헤더 파일의 크기가 커지거나 양이 많아 질수록 활용도 및 효율이 급상승한다.
*/

// SDKDDKVER.h는 프로그램에서 지원할 OS 혹은 라이브러리에 따라 Windows 헤더에서 코드가 포함될 함수 / 상수 등을 제어하는데 사용 한다.
#include <SDKDDKVER.h>


// 거의 사용되지 않는 내용은 Windows 헤더에서 제외
// ㄴ GDI+를 사용하려면 헤더파일에서 꺼내와야 한다.
//#include <ole2.h>
#define WIN32_LEAN_AND_MEAN

// 디버깅 콘솔창
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// ! 라이브러리 추가 ============================================================================================================
#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "winmm.lib")

//! Windows 헤더 파일 ============================================================================================================
#include <Windows.h>

//! C 런타임 헤더 파일 ============================================================================================================
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <tchar.h>
#include <stdio.h>
#include <timeapi.h>


//! C++ 런타임 헤더 파일 ============================================================================================================
#include <iostream>

#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <cassert>
#include <bitset>

using namespace std;

using std::vector;
using std::map;
using std::bitset;

// # 사용자 정의 헤더 파일 #
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Utils.h"

using namespace MY_UTIL;

// # 싱글톤 #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()

// ! 타이틀
#define WINNAME				(LPTSTR)(TEXT("WindowsAPI"))

// ! 전체 화면
//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics() : 인자로 전달되는 시스템 설정 정보를 반환
// ㄴ SM_CXSCREEN + SM_CYSCREEN = 현재 화면 해상도 X / Y 축 반환
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)  
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE

#else
// # 매크로 # (윈도우 창 초기화)
#define WINSTART_X			400
#define WINSTART_Y			100
#define WINSIZE_X			1280
#define WINSIZE_Y			800
#define WINSIZE_X_HALF		WINSIZE_X / 2
#define WINSIZE_Y_HALF		WINSIZE_Y / 2

// # 구조체 # 
struct FrameImage
{
	GImage* img;
	int alpha;
	int frameX;
	int frameY;
	int startFrameX;
	int endFrameX;

	float x, y;
	float timeUpdateSec;
	float elpasedSec;
};


// WS_CAPTION : 타이틀바를 가지기 위한 옵션
// WS_SYSMENU : 제목 표시줄에 컨트롤 메뉴 상자 창
#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#endif


// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
// 매크로 함수가 2줄 이상 내려갈때 \를 사용하면 된다.
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}


// # 전역 변수 # (데이터 영역)
// extern 키워드는 다른 헤더 / cpp에서 변수를 공유해서 쓰기 위해 사용한다.
// ㄴ 객체를 공유하기 위해 사용하면 더 좋다.
// 기본적으로 전역 변수는 키워드를 생략해도 기본적으로 extern화 되는 경우가 많다.
extern HINSTANCE		_hInstance;
extern HWND				_hWnd;
// X 좌표와 Y 좌표를 평면의 좌표에 정의할 때 사용을 한다.
extern POINT			_ptMouse;