#include "Stdafx.h"
#include "StageScene.h"

HRESULT StageScene::init(void)
{
	_bgImg = IMAGEMANAGER->findImage("Stage_BG");

	_player = new Player;
	_player->init();

	_em = new EnemyManager;
	_em->init();

	_ui = new UI;
	_ui->init();

	_item = new PowerItem;
	_item->init();

	_em->setPlayerMemoryAddress(_player);
	_ui->setPlayerMemoryAddress(_player);
	_player->setEnemyManagerMemoryAddress(_em);

	_offestX = 0.0f;
	_offestY = 0.0f;

	return S_OK;
}

void StageScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);

	_em->release();
	SAFE_DELETE(_em);

	_ui->release();
	SAFE_DELETE(_ui);
}

void StageScene::update(void)
{
	_player->update();
	_em->update();
	_ui->update();

	_item->update();

	_offestX += 3.0f;
}

void StageScene::render(void)
{
	_bgImg->loopRender(getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _offestX, _offestY);

	_player->render();
	_em->render();
	_ui->render();

	TIMEMANAGER->render(getMemDC());

	_item->render();
}
