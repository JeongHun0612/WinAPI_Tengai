#pragma once

// 4005��� ��� �����ϰڴ�.
#pragma warning(disable : 4005)
// 4005 : DXGI �� �׷��� �������̽����� ��ũ�� �����Ͽ� ��µǴ� ���
//#include "targetver.h" 

/*
�� Stdafx

- MS�� ����� ��Ʃ����� �̿��Ͽ� ������Ʈ�� ����� �����Ǵ� Ŭ�����̴�.
	�� �� ģ���� �ǹ��ϴ� �ٴ� ǥ�� ���ø����̼� �����ӿ�ũ�� Ʋ

- MS���� �����ڵ��� �ɷ� ����� ���� ������ PCH ����
	�� ���� ���̴� �������� ������� �̸� ������ �صξ� ���� �ٽ� ���������� �ʰ� ����ϰ� �ȴ�.

- ���߿� �ʱ� ���� �ܰ迡���� �ʿ伺�� ���������� ��� ������ ũ�Ⱑ Ŀ���ų� ���� ���� ������ Ȱ�뵵 �� ȿ���� �޻���Ѵ�.
*/

// SDKDDKVER.h�� ���α׷����� ������ OS Ȥ�� ���̺귯���� ���� Windows ������� �ڵ尡 ���Ե� �Լ� / ��� ���� �����ϴµ� ��� �Ѵ�.
#include <SDKDDKVER.h>


// ���� ������ �ʴ� ������ Windows ������� ����
// �� GDI+�� ����Ϸ��� ������Ͽ��� �����;� �Ѵ�.
//#include <ole2.h>
#define WIN32_LEAN_AND_MEAN

// ����� �ܼ�â
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// ! ���̺귯�� �߰� ============================================================================================================
#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "winmm.lib")

//! Windows ��� ���� ============================================================================================================
#include <Windows.h>

//! C ��Ÿ�� ��� ���� ============================================================================================================
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <tchar.h>
#include <stdio.h>
#include <timeapi.h>


//! C++ ��Ÿ�� ��� ���� ============================================================================================================
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

// # ����� ���� ��� ���� #
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Utils.h"

using namespace MY_UTIL;

// # �̱��� #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()

// ! Ÿ��Ʋ
#define WINNAME				(LPTSTR)(TEXT("WindowsAPI"))

// ! ��ü ȭ��
//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics() : ���ڷ� ���޵Ǵ� �ý��� ���� ������ ��ȯ
// �� SM_CXSCREEN + SM_CYSCREEN = ���� ȭ�� �ػ� X / Y �� ��ȯ
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)  
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE

#else
// # ��ũ�� # (������ â �ʱ�ȭ)
#define WINSTART_X			400
#define WINSTART_Y			100
#define WINSIZE_X			1280
#define WINSIZE_Y			800
#define WINSIZE_X_HALF		WINSIZE_X / 2
#define WINSIZE_Y_HALF		WINSIZE_Y / 2

// # ����ü # 
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


// WS_CAPTION : Ÿ��Ʋ�ٸ� ������ ���� �ɼ�
// WS_SYSMENU : ���� ǥ���ٿ� ��Ʈ�� �޴� ���� â
#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#endif


// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
// ��ũ�� �Լ��� 2�� �̻� �������� \�� ����ϸ� �ȴ�.
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}


// # ���� ���� # (������ ����)
// extern Ű����� �ٸ� ��� / cpp���� ������ �����ؼ� ���� ���� ����Ѵ�.
// �� ��ü�� �����ϱ� ���� ����ϸ� �� ����.
// �⺻������ ���� ������ Ű���带 �����ص� �⺻������ externȭ �Ǵ� ��찡 ����.
extern HINSTANCE		_hInstance;
extern HWND				_hWnd;
// X ��ǥ�� Y ��ǥ�� ����� ��ǥ�� ������ �� ����� �Ѵ�.
extern POINT			_ptMouse;