#pragma once
#include "Enemy.h"

class Spin_Enemy : public Enemy
{
private:
	int _fireCount;

public:
	HRESULT init(const char* imageName, POINT position, float speed, float angle = 0.0f);
	void release(void);

	void move(void);
	bool bulletCountFire(void);

	Spin_Enemy() {}
	~Spin_Enemy() {}
};