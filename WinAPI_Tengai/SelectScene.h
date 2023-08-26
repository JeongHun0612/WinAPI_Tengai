#pragma once
#include "GameNode.h"
#include "Animation.h"

class SelectScene : public GameNode
{
private:
	GImage* _bgImg;
	GImage* _selectBoard;

	vector<GImage*> _vSeclctCharacterImg;

	int _index;
	int _selectIndex;

	float _timeCnt;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SelectScene() {}
	~SelectScene() {}
};

