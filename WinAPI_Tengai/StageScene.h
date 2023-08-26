#pragma once
#include "GameNode.h"
#include "Player.h"
#include "EnemyManager.h"

#include "PowerItem.h"

class StageScene : public GameNode
{
private:
	Player* _player;
	EnemyManager* _enemyManager;

	PowerItem* _item;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StageScene() {}
	~StageScene() {}
};
