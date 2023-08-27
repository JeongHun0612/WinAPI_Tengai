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

	_boss = new Boss;
	_boss->init();

	_em->setPlayerMemoryAddress(_player);
	_boss->setPlayerMemoryAddress(_player);
	_ui->setPlayerMemoryAddress(_player);

	_player->setEnemyManagerMemoryAddress(_em);
	_player->setBossManagerMemoryAddress(_boss);

	_offsetX = 0;
	_offsetY = 2899;

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

	if (_boss != nullptr)
	{
		_boss->release();
		SAFE_DELETE(_boss);
	}
}

void StageScene::update(void)
{
	_player->update();
	_em->update();
	_ui->update();

	if (_offsetX < 15000)
	{
		_offsetX += 3;
	}
	else
	{
		if (_offsetY > 0)
		{
			_offsetX += 1;
			_offsetY -= 2;
		}
		else
		{
			_offsetX += 3;
		}
	}
	
	if (_offsetX > 20000 && _offsetY <= 0)
	{
		if (!_boss->getIsStart())
		{
			_boss->setIsStart(true);
		}
	}

	if (_boss != nullptr)
	{
		_boss->update();
	}
}

void StageScene::render(void)
{
	_bgImg->loopRender(getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _offsetX, _offsetY);

	_player->render();
	_em->render();
	_ui->render();

	if (_boss != nullptr)
	{
		_boss->render();
	}

	//TIMEMANAGER->render(getMemDC());
}
