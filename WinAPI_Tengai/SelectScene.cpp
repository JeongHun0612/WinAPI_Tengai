#include "Stdafx.h"
#include "SelectScene.h"

HRESULT SelectScene::init(void)
{
	_bgImg = IMAGEMANAGER->findImage("Select_BG");
	_selectBoard = IMAGEMANAGER->findImage("Select_Board");

	_vSeclctCharacterImg.push_back(IMAGEMANAGER->findImage("Miko_Idle"));
	_vSeclctCharacterImg.push_back(IMAGEMANAGER->findImage("Tengai_Idle"));
	_vSeclctCharacterImg.push_back(IMAGEMANAGER->findImage("Katana_Idle"));
	_vSeclctCharacterImg.push_back(IMAGEMANAGER->findImage("Sho_Idle"));
	_vSeclctCharacterImg.push_back(IMAGEMANAGER->findImage("Junis_Idle"));

	_index = 0;
	_selectIndex = 0;

	_timeCnt = 0.0f;

	return S_OK;
}

void SelectScene::release(void)
{
	_vSeclctCharacterImg.clear();
}

void SelectScene::update(void)
{
	_timeCnt += TIMEMANAGER->getElapsedTime();

	if (_timeCnt >= 0.1f)
	{
		_index++;

		if (_index == 3)
		{
			_index = 0;
		}

		_timeCnt = 0.0f;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _selectIndex > 0)
	{
		_selectIndex--;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _selectIndex < _vSeclctCharacterImg.size() - 1)
	{
		_selectIndex++;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("Stage");
	}
}

void SelectScene::render(void)
{
	_bgImg->render(getMemDC());
	_selectBoard->render(getMemDC(), 150 + 200 * _selectIndex, 655 - _selectBoard->getHeight() / 2);

	for (int i = 0; i < _vSeclctCharacterImg.size(); i++)
	{
		_vSeclctCharacterImg[i]->frameRender(getMemDC(), 180 + 200 * i, 655 - _vSeclctCharacterImg[i]->getFrameHeight() / 2, _index, 0);
	}
}
