#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_img = IMAGEMANAGER->findImage("Miko");

	_idleAnim = new Animation;
	_idleAnim->init(_img->getWidth(), _img->getHeight(), _img->getFrameWidth(), _img->getFrameHeight());
	_idleAnim->setFPS(0.15f);
	_idleAnim->setPlayFrame(0, 2);
	_idleAnim->AniStart();

	_bullet = new Bullet;
	_bullet->init("Miko_Bullet", 100, WINSIZE_X);

	_bulletPower = 0;

	_x = -100;
	_y = WINSIZE_Y_HALF - 200;

	_isStart = false;

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	_idleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	if (!_isStart)
	{
		if (_x > 300.0f)
		{
			_isStart = true;
		}

		_x += PLAYER_SPEED - 1.0f;
	}
	else
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_x -= PLAYER_SPEED;
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_x += PLAYER_SPEED;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_y -= PLAYER_SPEED;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_y += PLAYER_SPEED;
		}

		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			_bullet->fire(_x , _y, PI_2, 15.0f, _bulletPower);
		}
	}

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_bullet->update();
}

void Player::render(void)
{
	_img->aniRender(getMemDC(), _rc.left, _rc.top, _idleAnim);

	_bullet->render();
}
