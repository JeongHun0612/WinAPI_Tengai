#pragma once
#include "GameNode.h"
#include "Enemy.h"

class Player;

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

	vEnemy _vMinion;
	viEnemy _viMinion;

	Bullet* _bullet;
	Player* _player;

	GImage* _dieEffectImg;
	Animation* _dieAnim;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(const char* imageName, int count, float speed);
	void removeMinion(int arrNum);

	void minionBulletFire(void);
	void collision(void);

	vector<Enemy*> getMinions(void) { return _vMinion; }
	Bullet* getBullet(void) { return _bullet; }
	void setRocketMemoryAddress(Player* player) { _player = player; }

	EnemyManager() {}
	~EnemyManager() {}
};
