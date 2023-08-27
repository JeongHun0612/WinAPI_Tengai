#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Bullet.h"

struct BossParts
{
	FrameImage frameImg;
	RECT rc;

	int maxHP;
	int curHP;

	float patternTimeElapsed;
	float patternTimeSec;

	bool isHit;
	bool isDestory;
};

class Player;

class Boss : public GameNode
{
private:
	BossParts* _body;
	BossParts* _head;
	BossParts* _tail;

	vector<BossParts*> _vBossParts;
	vector<BossParts*>::iterator _viBossParts;

	vector<FrameImage> _vDieEffect;
	vector<FrameImage>::iterator _viDieEffect;

	Player* _player;
	BossBullet* _bullet;

	float _x, _y;
	float _speed;

	bool _isDie;
	bool _isStart;
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void collision(void);
	void effectFrameUpdate(void);
	void setDestoryEffect(float x, float y, int count);

public:
	BossBullet* getBullet(void) { return _bullet; }

	vector<BossParts*> getBossParts(void) { return _vBossParts; }

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	bool getIsStart(void) { return _isStart; }
	void setIsStart(bool isStart) { _isStart = isStart; }

	bool getIsDie(void) { return _isDie; }

	Boss() {}
	~Boss() {}
};

