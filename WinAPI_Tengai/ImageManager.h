#pragma once
#include "SingletonBase.h"
#include "GImage.h"

// 1. ��ü�� ���� new
// 2. ���� ����
// Map / Vector / �Լ� ������ / delegate �� ���� ���� ������ ���

#pragma region STL ��
/*
- Ű + ��
 �� ù��° first -> key
 �� �ι�° second -> value

- �߰��ϴ� ����� insert()�� ����ϰ� key�� value�� ���ÿ� �߰��ؾ��ϴ� pair / make_pair�� ���

- pair() : 2���� �ڷ����� �ϳ��� �����ִ� ����ü (���ø� -> � �ڷ����� OK)

- make_pair() : pair�� ����� �ִ� �Լ�
 �� pair.first = x / pair.second = y;
 �� pair = make_pair(x, y);

- �ϳ��� key�� ���� ���� value�� �����ϰ� �ʹٸ� ��Ƽ���� ����ϴ� �͵� ���

- pair�� Ȯ����� ������ �ۼ��ϰų� �ټ��� ��ȯ���� ������ �ʹٸ� tuple�� ����ؾ� �Ѵ�.
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

	// �ܵ�ó���� ������
	// �� 1. �����ӿ�ũ �ڵ� ����ġ
	// �� 2. ��ü�� (�̹���) �浹 ���ɼ�

	GImage* addImage(string strKey, int width, int height);
	GImage* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	GImage* findImage(string strKey);

	bool deleteImage(string strKey);
	bool deleteAll();

	// ����
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);

	//�̹��� Ŭ����
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);

	// ������ ����
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	// ���� ����
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// ���� ����
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	ImageManager() {}
	~ImageManager() {}
};