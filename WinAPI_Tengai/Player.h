#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Bullet.h"

#define PLAYER_SPEED	3.0f;

class Player : public GameNode
{
private:
	GImage* _img;
	RECT _rc;

	Animation* _idleAnim;

	// ÃÑ¾Ë
	Bullet* _bullet;

	int _bulletPower;

	float _x, _y;

	bool _isStart;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Player() {}
	~Player() {}
};

