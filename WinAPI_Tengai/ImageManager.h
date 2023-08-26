#pragma once
#include "SingletonBase.h"
#include "GImage.h"

// 1. 객체에 따른 new
// 2. 관리 문제
// Map / Vector / 함수 포인터 / delegate 를 통해 관리 문제를 고려

#pragma region STL 맵
/*
- 키 + 값
 ㄴ 첫번째 first -> key
 ㄴ 두번째 second -> value

- 추가하는 방법은 insert()를 사용하고 key와 value를 동시에 추가해야하니 pair / make_pair를 사용

- pair() : 2개의 자료형을 하나로 묶어주는 구조체 (템플릿 -> 어떤 자료형도 OK)

- make_pair() : pair를 만들어 주는 함수
 ㄴ pair.first = x / pair.second = y;
 ㄴ pair = make_pair(x, y);

- 하나의 key에 여러 개의 value를 저장하고 싶다면 멀티맵을 사용하는 것도 고려

- pair를 확장시켜 구조를 작성하거나 다수의 반환값을 가지고 싶다면 tuple도 고려해야 한다.
*/
#pragma endregion

class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, GImage*> mapImageList;
	typedef map<string, GImage*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	HRESULT init();
	void release(void);

	// 단독처리시 문제점
	// ㄴ 1. 프레임워크 코드 불일치
	// ㄴ 2. 객체간 (이미지) 충돌 가능성

	GImage* addImage(string strKey, int width, int height);
	GImage* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	GImage* findImage(string strKey);

	bool deleteImage(string strKey);
	bool deleteAll();

	// 렌더
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);

	//이미지 클리핑
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);

	// 프레임 렌더
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	// 알파 렌더
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// 루프 렌더
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	ImageManager() {}
	~ImageManager() {}
};