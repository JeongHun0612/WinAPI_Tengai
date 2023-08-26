#include "Stdafx.h"
#include "MainGame.h"

#include "TitleScene.h"
#include "SelectScene.h"
#include "StageScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	// 이미지 추가
	addImage();

	// 씬 추가
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Select", new SelectScene);
	SCENEMANAGER->addScene("Stage", new StageScene);

	// 초기 화면 (타이틀) <->
	SCENEMANAGER->changeScene("Stage");

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	// ==================================================================

	SCENEMANAGER->render();

	// ==================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void MainGame::addImage(void)
{
	// BackGround
	IMAGEMANAGER->addImage("Title_BG", "Resources/Images/Background/Title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Select_BG", "Resources/Images/Background/Select.bmp", WINSIZE_X, WINSIZE_Y);

	// UI
	IMAGEMANAGER->addFrameImage("Start_UI", "Resources/Images/UI/Start_UI.bmp", 536, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Board", "Resources/Images/UI/Select_Board.bmp", 160, 160, true, RGB(255, 0, 255));

	// Item
	IMAGEMANAGER->addFrameImage("Power_Item", "Resources/Images/UI/Power_Item.bmp", 555, 198, 5, 3, true, RGB(255, 0, 255));

	// Character
	// Miko
	IMAGEMANAGER->addFrameImage("Miko", "Resources/Images/Characters/Miko/Miko.bmp", 960, 87, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Miko_Idle", "Resources/Images/Characters/Miko/Miko_Idle.bmp", 288, 84, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Miko_Bullet", "Resources/Images/Characters/Miko/Bullet.bmp", 450, 28, 15, 1, true, RGB(255, 0, 255));

	// Tengai
	IMAGEMANAGER->addFrameImage("Tengai_Idle", "Resources/Images/Characters/Tengai/Tengai_Idle.bmp", 258, 78, 3, 1, true, RGB(255, 0, 255));

	// Kanata
	IMAGEMANAGER->addFrameImage("Katana_Idle", "Resources/Images/Characters/Katana/Katana_Idle.bmp", 264, 90, 3, 1, true, RGB(255, 0, 255));

	// Sho
	IMAGEMANAGER->addFrameImage("Sho_Idle", "Resources/Images/Characters/Sho/Sho_Idle.bmp", 270, 82, 3, 1, true, RGB(255, 0, 255));

	// Junis
	IMAGEMANAGER->addFrameImage("Junis_Idle", "Resources/Images/Characters/Junis/Junis_Idle.bmp", 270, 84, 3, 1, true, RGB(255, 0, 255));


	// Enemy
	IMAGEMANAGER->addImage("Enmey1", "Resources/Images/Enemy/Enemy1.bmp", 512, 58, true, RGB(255, 0, 255));
}
