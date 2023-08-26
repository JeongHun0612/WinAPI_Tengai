#include "Stdafx.h"
#include "MainGame.h"

#include "TitleScene.h"
#include "SelectScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	// 이미지 추가
	addImage();


	// 씬 추가
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Select", new SelectScene);


	// 초기 화면 (타이틀) <->
	SCENEMANAGER->changeScene("Select");

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
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
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
	IMAGEMANAGER->addFrameImage("Select_Charater", "Resources/Images/UI/Select_Charater.bmp", 536, 60, 2, 1, true, RGB(255, 0, 255));

	// Character
	// Miko
	IMAGEMANAGER->addFrameImage("Miko_Idle", "Resources/Images/Characters/Miko/Miko_Idle.bmp", 288, 84, 3, 1, true, RGB(255, 0, 255));
}
