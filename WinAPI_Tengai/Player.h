#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Bullet.h"

#define PLAYER_SPEED	3.0f
#define BULLET_SPEED	15.0f

class EnemyManager;

class Player : public GameNode
{
private:
	FrameImage _frameImg;
	FrameImage _dieEffectImg;

	Bullet* _bullet;

	EnemyManager* _em;

	RECT _rc;

	int _bulletPower;
	int _bombCount;
	int _lifeCount;
	int _score;

	float _x, _y;
	float _invincibleTime;

	bool _isLeft;
	bool _isDie;
	bool _isReLive;
	bool _isInvincible;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collision(void);
	void frameUpdate(void);

public:
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }

	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }
	RECT getRect(void) { return _rc; }

	void setIsDie(bool isDie) { _isDie = isDie; }

	int getBombCount(void) { return _bombCount; }
	int getLifeCount(void) { return _lifeCount; } 
	int getScore(void) { return _score; }

	bool getIsInvincible(void) { return _isInvincible; }

	Player() {}
	~Player() {}
};

