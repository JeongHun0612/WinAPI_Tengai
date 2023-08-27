#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Bullet.h"

class Enemy : public GameNode
{
protected:
	GImage* _image;
	Animation* _anim;

	RECT _rc;

	const char* _imageName;

	int _maxHP;
	int _curHP;

	float _x, _y;
	float _speed;
	float _angle;

	float _rndFirecount;
	float _bulletFireCount;

public:
	HRESULT init(void);
	virtual HRESULT init(const char* imageName, POINT position, float speed, float angle = 0.0f);
	virtual void release(void);

	void update(void);
	void render(void);

	virtual void move(void);
	virtual bool bulletCountFire(void);

public:
	float getX(void) { return _x; }
	float getY(void) { return _y; }

	RECT getRC(void) { return _rc; }

	int getCurHP(void) { return _curHP; }
	void setCurHP(int curHP) { _curHP = curHP; }
	
	const char* getImageName(void) { return _imageName; }

	Enemy(void);
	~Enemy(void) {}
};

