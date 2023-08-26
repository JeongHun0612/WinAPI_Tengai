#pragma once
#include "GameNode.h"
#include "Animation.h"

struct tagBullet
{
	GImage* img;
	RECT rc;

	int radius;
	int frameX;

	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	float timeUpdateSec;

	bool fire;
	bool explosion;
};

class Bullet : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;

	int _bulletMax;
	float _range;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed, int power);
	void move(void);
	void draw(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet() { return _vBullet; }

	Bullet(void) {}
	virtual ~Bullet() {}
};

class EnemyBullet : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;

	int _bulletMax;
	float _range;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void move(void);
	void draw(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet() { return _vBullet; }

	EnemyBullet(void) {}
	virtual ~EnemyBullet() {}
};