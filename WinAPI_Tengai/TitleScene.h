#pragma once
#include "GameNode.h"
#include "Animation.h"

class TitleScene : public GameNode
{
private:
	GImage* _bgImg;

	GImage* _startImg;
	Animation* _startAnim;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TitleScene() {}
	~TitleScene() {}
};

