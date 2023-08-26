#include "Stdafx.h"
#include "SelectScene.h"

HRESULT SelectScene::init(void)
{
	_bgImg = IMAGEMANAGER->findImage("Select_BG");
	_selectBoard = IMAGEMANAGER->findImage("Select_Board");

	_vSelectCharacterImg.push_back(IMAGEMANAGER->findImage("Miko_Idle"));
	_vSelectCharacterImg.push_back(IMAGEMANAGER->findImage("Tengai_Idle"));
	_vSelectCharacterImg.push_back(IMAGEMANAGER->findImage("Katana_Idle"));
	_vSelectCharacterImg.push_back(IMAGEMANAGER->findImage("Sho_Idle"));
	_vSelectCharacterImg.push_back(IMAGEMANAGER->findImage("Junis_Idle"));

	_index = 0;
	_selectIndex = 0;

	_timeCnt = 0.0f;

	return S_OK;
}

void SelectScene::release(void)
{
	_vSelectCharacterImg.clear();
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

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _selectIndex < _vSelectCharacterImg.size() - 1)
	{
		_selectIndex++;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _selectIndex == MIKO)
	{
		SCENEMANAGER->changeScene("Stage");
	}
}

void SelectScene::render(void)
{
	_bgImg->render(getMemDC());
	_selectBoard->render(getMemDC(), 150 + 200 * _selectIndex, 655 - _selectBoard->getHeight() / 2);

	for (int i = 0; i < _vSelectCharacterImg.size(); i++)
	{
		_vSelectCharacterImg[i]->frameRender(getMemDC(), 180 + 200 * i, 655 - _vSelectCharacterImg[i]->getFrameHeight() / 2, _index, 0);
	}

	switch (_selectIndex)
	{
	case MIKO:
		IMAGEMANAGER->findImage("Select_Miko_Left")->render(getMemDC(), 64, 101);
		IMAGEMANAGER->findImage("Select_Miko_Right")->render(getMemDC(), 
			900 - IMAGEMANAGER->findImage("Select_Miko_Right")->getWidth() / 2, 
			310 - IMAGEMANAGER->findImage("Select_Miko_Right")->getHeight() / 2);
		break;
	case TENGAI:
		IMAGEMANAGER->findImage("Select_Tengai_Left")->render(getMemDC(), 64, 101);
		IMAGEMANAGER->findImage("Select_Tengai_Right")->render(getMemDC(),
			900 - IMAGEMANAGER->findImage("Select_Tengai_Right")->getWidth() / 2,
			310 - IMAGEMANAGER->findImage("Select_Tengai_Right")->getHeight() / 2);
		break;
	case KANATA:
		IMAGEMANAGER->findImage("Select_Kanata_Left")->render(getMemDC(), 64, 101);
		IMAGEMANAGER->findImage("Select_Kanata_Right")->render(getMemDC(),
			900 - IMAGEMANAGER->findImage("Select_Kanata_Right")->getWidth() / 2,
			310 - IMAGEMANAGER->findImage("Select_Kanata_Right")->getHeight() / 2);
		break;
	case SHO:
		IMAGEMANAGER->findImage("Select_Sho_Left")->render(getMemDC(), 64, 101);
		IMAGEMANAGER->findImage("Select_Sho_Right")->render(getMemDC(),
			900 - IMAGEMANAGER->findImage("Select_Sho_Right")->getWidth() / 2,
			310 - IMAGEMANAGER->findImage("Select_Sho_Right")->getHeight() / 2);
		break;
	case JUNIS:
		IMAGEMANAGER->findImage("Select_Junis_Left")->render(getMemDC(), 64, 101);
		IMAGEMANAGER->findImage("Select_Junis_Right")->render(getMemDC(),
			900 - IMAGEMANAGER->findImage("Select_Junis_Right")->getWidth() / 2,
			310 - IMAGEMANAGER->findImage("Select_Junis_Right")->getHeight() / 2);
		break;
	}
}
