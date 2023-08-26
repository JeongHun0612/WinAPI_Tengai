#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Bullet.h"

class Enemy : public GameNode
{
protected:
	GImage* _image;
	Animation* _anim;
	Bullet* _bullet;

	RECT _rc;

	int _maxHP;
	int _curHP;

	float _x, _y;
	float _speed;
	float _angle;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position, float speed, float angle = 0.0f);

	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);

	bool bulletCountFire(void);

	RECT getRC(void) { return _rc; }

	int getCurHP() { return _curHP; }
	void setCurHP(int curHP) { _curHP = curHP; }

	Enemy(void);
	~Enemy(void) {}
};

