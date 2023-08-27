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
	SCENEMANAGER->changeScene("Title");

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
	IMAGEMANAGER->addImage("Stage_BG", "Resources/Images/Background/Stage.bmp", 3453, 3699);

	// UI
	IMAGEMANAGER->addFrameImage("Start_UI", "Resources/Images/UI/Start_UI.bmp", 536, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Board", "Resources/Images/UI/Select_Board.bmp", 160, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Miko_Left", "Resources/Images/UI/Select_Miko_Left.bmp", 450, 439, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Miko_Right", "Resources/Images/UI/Select_Miko_Right.bmp", 636, 497, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Tengai_Left", "Resources/Images/UI/Select_Tengai_Left.bmp", 450, 442, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Tengai_Right", "Resources/Images/UI/Select_Tengai_Right.bmp", 636, 416, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Kanata_Left", "Resources/Images/UI/Select_Kanata_Left.bmp", 450, 441, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Kanata_Right", "Resources/Images/UI/Select_Kanata_Right.bmp", 636, 492, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Sho_Left", "Resources/Images/UI/Select_Sho_Left.bmp", 450, 439, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Sho_Right", "Resources/Images/UI/Select_Sho_Right.bmp", 636, 403, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Junis_Left", "Resources/Images/UI/Select_Junis_Left.bmp", 450, 438, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Select_Junis_Right", "Resources/Images/UI/Select_Junis_Right.bmp", 636, 454, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("1P", "Resources/Images/UI/1P.bmp", 45, 27, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Life", "Resources/Images/UI/Life.bmp", 48, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Bomb_UI", "Resources/Images/UI/Bomb_UI.bmp", 84, 48, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Score", "Resources/Images/UI/Score.bmp", 270, 27, 10, 1, true, RGB(255, 0, 255));

	// Item
	IMAGEMANAGER->addFrameImage("Power_Item", "Resources/Images/UI/Power_Item.bmp", 555, 198, 5, 3, true, RGB(255, 0, 255));

	// Character
	// Miko
	IMAGEMANAGER->addFrameImage("Miko", "Resources/Images/Characters/Miko/Miko.bmp", 960, 87, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Miko_Idle", "Resources/Images/Characters/Miko/Miko_Idle.bmp", 288, 84, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Miko_Bullet", "Resources/Images/Characters/Miko/Bullet.bmp", 450, 28, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Miko_Bomb", "Resources/Images/Characters/Miko/Bomb.bmp", 4320, 480, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Miko_Bomb_Bullet", "Resources/Images/Characters/Miko/Bomb_Bullet.bmp", 351, 48, 9, 1, true, RGB(255, 0, 255));

	// Tengai
	IMAGEMANAGER->addFrameImage("Tengai_Idle", "Resources/Images/Characters/Tengai/Tengai_Idle.bmp", 258, 78, 3, 1, true, RGB(255, 0, 255));

	// Kanata
	IMAGEMANAGER->addFrameImage("Katana_Idle", "Resources/Images/Characters/Katana/Katana_Idle.bmp", 264, 90, 3, 1, true, RGB(255, 0, 255));

	// Sho
	IMAGEMANAGER->addFrameImage("Sho_Idle", "Resources/Images/Characters/Sho/Sho_Idle.bmp", 270, 82, 3, 1, true, RGB(255, 0, 255));

	// Junis
	IMAGEMANAGER->addFrameImage("Junis_Idle", "Resources/Images/Characters/Junis/Junis_Idle.bmp", 270, 84, 3, 1, true, RGB(255, 0, 255));

	// Enemy
	IMAGEMANAGER->addFrameImage("Enemy_Bullet", "Resources/Images/Enemy/Enemy_Bullet.bmp", 102, 18, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Green_Enemy", "Resources/Images/Enemy/Green_Enemy.bmp", 360, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Red_Enemy", "Resources/Images/Enemy/Red_Enemy.bmp", 360, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Spin_Enemy", "Resources/Images/Enemy/Spin_Enemy.bmp", 768, 87, 8, 1, true, RGB(255, 0, 255));

	// Boss
	IMAGEMANAGER->addFrameImage("Boss_Head", "Resources/Images/Enemy/Boss_Head.bmp", 870, 408, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Body", "Resources/Images/Enemy/Boss_Body.bmp", 1755, 681, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Tail", "Resources/Images/Enemy/Boss_Tail.bmp", 672, 654, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Bullet", "Resources/Images/Enemy/Boss_Bullet.bmp", 150, 50, 3, 1, true, RGB(255, 0, 255));


	// Particle
	IMAGEMANAGER->addFrameImage("Death_Enemy", "Resources/Images/Particle/Death_Enemy.bmp", 1232, 130, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Death_Player", "Resources/Images/Particle/Death_Player.bmp", 1792, 256, 7, 1, true, RGB(255, 0, 255));
}