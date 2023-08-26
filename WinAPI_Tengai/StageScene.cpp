#include "Stdafx.h"
#include "StageScene.h"

HRESULT StageScene::init(void)
{
	_player = new Player;
	_player->init();

	_enemyManager = new EnemyManager;
	_enemyManager->init();

	_item = new PowerItem;
	_item->init();

	return S_OK;
}

void StageScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void StageScene::update(void)
{
	_player->update();

	_enemyManager->update();

	_item->update();
}

void StageScene::render(void)
{
	_player->render();

	_enemyManager->render();

	_item->render();
}
