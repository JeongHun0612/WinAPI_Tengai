#pragma once
#include "GameNode.h"
#include "Animation.h"

class SelectScene : public GameNode
{
private:
	GImage* _bgImg;

	GImage* _selectMikoImg;
	Animation* _idleAnim;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SelectScene() {}
	~SelectScene() {}
};

