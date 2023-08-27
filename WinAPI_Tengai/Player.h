#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Bullet.h"

#define PLAYER_SPEED	3.0f
#define BULLET_SPEED	15.0f
#define BOMB_SPEED		3.0f

class EnemyManager;
class Boss;
class PowerItem;

class Player : public GameNode
{
private:
	FrameImage _frameImg;
	FrameImage _dieEffectImg;

	Bullet* _bullet;
	Bomb* _bomb;

	EnemyManager* _em;
	Boss* _boss;
	PowerItem* _item;

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
	void setBossManagerMemoryAddress(Boss* boss) { _boss = boss; }

	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }
	RECT getRect(void) { return _rc; }

	void setIsDie(bool isDie) { _isDie = isDie; }

	void setPower(int power) { _bulletPower = power; }
	int getPower(void) { return _bulletPower; }

	int getBombCount(void) { return _bombCount; }
	int getLifeCount(void) { return _lifeCount; } 

	void setScore(int score) { _score = score; }
	int getScore(void) { return _score; }

	bool getIsInvincible(void) { return _isInvincible; }

	Player() {}
	~Player() {}
};

