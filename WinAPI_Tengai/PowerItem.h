#pragma once
#include "GameNode.h"
#include "Animation.h"

#define ITEM_SPEED	1.5f

class PowerItem : public GameNode
{
private:
	GImage* _img;
	Animation* _anim;

	RECT _rc;

	float _x, _y;
	float _angle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	PowerItem() {}
	~PowerItem() {}
};

