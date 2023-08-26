#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_bgImg = IMAGEMANAGER->findImage("Title_BG");

	_startImg = IMAGEMANAGER->findImage("Start_UI");
	_startAnim = new Animation;
	_startAnim->init(_startImg->getWidth(), _startImg->getHeight(), _startImg->getFrameWidth(), _startImg->getFrameHeight());
	_startAnim->setFPS(1.0f);
	_startAnim->AniStart();

	return S_OK;
}

void TitleScene::release(void)
{
}

void TitleScene::update(void)
{
	_startAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("Select");
	}
}

void TitleScene::render(void)
{
	_bgImg->render(getMemDC());

	_startImg->aniRender(getMemDC(), WINSIZE_X_HALF - _startImg->getFrameWidth() / 2, WINSIZE_Y_HALF + 100, _startAnim);
}
