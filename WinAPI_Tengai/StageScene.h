#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Player.h"
#include "EnemyManager.h"
#include "UI.h"

#include "PowerItem.h"

class StageScene : public GameNode
{
private:
	GImage* _bgImg;

	Player* _player;
	EnemyManager* _em;
	UI* _ui;

	PowerItem* _item;

	float _offestX;
	float _offestY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StageScene() {}
	~StageScene() {}
};
