#include "Stdafx.h"
#include "UI.h"
#include "Player.h"

HRESULT UI::init(void)
{
	_bombImg = IMAGEMANAGER->findImage("Bomb_UI");
	_bombAnim = new Animation;
	_bombAnim->init(_bombImg->getWidth(), _bombImg->getHeight(), _bombImg->getFrameWidth(), _bombImg->getFrameHeight());
	_bombAnim->setFPS(0.2f);
	_bombAnim->AniStart();

	_lifeImg = IMAGEMANAGER->findImage("Life");
	_scoreImg = IMAGEMANAGER->findImage("Score");

	return S_OK;
}

void UI::release(void)
{
	SAFE_DELETE(_bombAnim);
}

void UI::update(void)
{
	// ÆøÅº UI ¾Ö´Ï¸ÞÀÌ¼Ç
	_bombAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void UI::render(void)
{
	// 1P
	IMAGEMANAGER->findImage("1P")->render(getMemDC(), 20, 30 - IMAGEMANAGER->findImage("1P")->getHeight() / 2);

	// Bomb
	for (int i = 0; i < _player->getBombCount(); i++)
	{
		_bombImg->aniRender(getMemDC(), 20 + (i * _bombImg->getFrameWidth() + 10), 50, _bombAnim);
	}

	// Life
	for (int i = 0; i < _player->getLifeCount(); i++)
	{
		_lifeImg->render(getMemDC(), 350 + i * _lifeImg->getWidth(), 30 - _lifeImg->getHeight() / 2);
	}

	// Score
	for (int i = to_string(_player->getScore()).size(); i >= 0; i--)
	{
		_scoreImg->frameRender(getMemDC(), 
			200 + (i * _scoreImg->getFrameWidth()), 
			30 - _scoreImg->getFrameHeight() / 2, 
			to_string(_player->getScore())[i] - 48, 0);
	}
}
