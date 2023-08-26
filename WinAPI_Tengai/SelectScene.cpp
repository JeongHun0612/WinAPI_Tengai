#include "Stdafx.h"
#include "SelectScene.h"

HRESULT SelectScene::init(void)
{
	_bgImg = IMAGEMANAGER->findImage("Select_BG");
	_selectMikoImg = IMAGEMANAGER->findImage("Miko_Idle");

	_idleAnim = new Animation;
	_idleAnim->init(_selectMikoImg->getWidth(), _selectMikoImg->getHeight(), _selectMikoImg->getFrameWidth(), _selectMikoImg->getFrameHeight());
	_idleAnim->setFPS(0.1f);
	_idleAnim->AniStart();

	return S_OK;
}

void SelectScene::release(void)
{
}

void SelectScene::update(void)
{
	_idleAnim->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void SelectScene::render(void)
{
	_bgImg->render(getMemDC());

	_selectMikoImg->aniRender(getMemDC(), 0, WINSIZE_Y_HALF, _idleAnim);
}
