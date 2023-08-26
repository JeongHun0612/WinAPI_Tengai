#pragma once
#include "SingletonBase.h"

// ��ü���� ��ȯ -> ���� ��� / �����

#define	KEY_MAX	256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];

	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

public:
	// �ʱ�ȭ
	HRESULT init(void);

	bool isOnceKeyDown(int key);	// Ű�� �ѹ��� ���ȴ���
	bool isOnceKeyUp(int key);		// �ѹ� ������ �������
	bool isStayKeyDown(int key);	// Ű�� ��� ���� �ִ���
	bool isToggleKey(int key);		// ���Ű
	bool isAnyKeyDown();			// �ƹ� Ű�� ������ ��

	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager() {}
	~KeyManager() {}
};