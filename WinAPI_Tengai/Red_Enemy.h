#pragma once
#include "Enemy.h"
#include "PowerItem.h"

class Red_Enemy : public Enemy
{
private:
	PowerItem* _powerItem;

public:
	HRESULT init(const char* imageName, POINT position, float speed, float angle = 0.0f);
	void release(void);

	void move(void);
	bool bulletCountFire(void);

	Red_Enemy() {}
	~Red_Enemy() {}
};

