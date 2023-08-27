#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "PowerItem.h"

class Player;

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

	vEnemy _vMinion;
	viEnemy _viMinion;

	EnemyBullet* _bullet;
	Player* _player;

	vector<PowerItem*> _vItem;
	vector<PowerItem*>::iterator _viItem;

	vector<FrameImage> _vDieEffect;
	vector<FrameImage>::iterator _viDieEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setSpinEnemy(int count);
	void setReturnEnemy(int count);

	void removeMinion(int arrNum);

	void minionSpawn(void);
	void minionBulletFire(void);
	void collision(void);

public:
	vector<Enemy*> getMinions(void) { return _vMinion; }

	EnemyBullet* getBullet(void) { return _bullet; }

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	EnemyManager() {}
	~EnemyManager() {}
};
