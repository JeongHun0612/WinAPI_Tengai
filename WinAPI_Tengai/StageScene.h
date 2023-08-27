#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Boss.h"
#include "UI.h"

class StageScene : public GameNode
{
private:
	GImage* _bgImg;

	Player* _player;
	EnemyManager* _em;
	Boss* _boss;
	UI* _ui;

	int _offsetX;
	int _offsetY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StageScene() {}
	~StageScene() {}
};
