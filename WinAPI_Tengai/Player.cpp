#include "Stdafx.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Boss.h"

HRESULT Player::init(void)
{
	_frameImg.img = IMAGEMANAGER->findImage("Miko");
	_frameImg.timeUpdateSec = 0.15f;
	_frameImg.startFrameX = 0;
	_frameImg.endFrameX = 2;
	_frameImg.alpha = 255;

	_dieEffectImg.img = IMAGEMANAGER->findImage("Death_Player");
	_dieEffectImg.timeUpdateSec = 0.2f;

	_bullet = new Bullet;
	_bullet->init("Miko_Bullet", 100, WINSIZE_X);

	_bomb = new Bomb;
	_bomb->init("Miko_Bomb_Bullet", 1, 400);

	_bulletPower = 0;
	_bombCount = 2;
	_lifeCount = 3;
	_score = 0;

	_x = -100;
	_y = WINSIZE_Y_HALF - 200;

	_invincibleTime = TIMEMANAGER->getWorldTime();

	_isLeft = false;
	_isReLive = true;
	_isDie = false;
	_isInvincible = false;

	return S_OK;
}

void Player::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);

	_bomb->release();
	SAFE_DELETE(_bomb);
}

void Player::update(void)
{
	frameUpdate();

	// 재등장
	if (_isReLive)
	{
		if (_x > 200.0f)
		{
			_isReLive = false;
		}

		if (!_isInvincible)
		{
			_isInvincible = true;
		}

		_x += PLAYER_SPEED - 1.0f;
	}

	// 무적 상태 일때
	if (_isInvincible)
	{
		_invincibleTime += TIMEMANAGER->getElapsedTime();

		if (_invincibleTime > 5.0f)
		{
			_frameImg.alpha = 255;
			_invincibleTime = 0.0f;
			_isInvincible = false;
		}
	}

	// 사망 상태일 때
	if (_isDie)
	{
		if (_frameImg.frameX != 9)
		{
			_frameImg.startFrameX = 9;
			_frameImg.endFrameX = 9;
			_frameImg.frameX = _frameImg.startFrameX;

			_dieEffectImg.frameX = 0;
			_dieEffectImg.elpasedSec = 0.0f;
			_bulletPower = 0;
			_bombCount = 2;
			_lifeCount--;
		}

		_dieEffectImg.elpasedSec += TIMEMANAGER->getElapsedTime();

		if (_dieEffectImg.elpasedSec > _dieEffectImg.timeUpdateSec)
		{
			if (_dieEffectImg.frameX < _dieEffectImg.img->getMaxFrameX())
			{
				_dieEffectImg.frameX++;
				_dieEffectImg.elpasedSec -= _dieEffectImg.timeUpdateSec;
			}
		}

		_x -= 2.0f;
		_y += 5.0f;

		if (_y >= WINSIZE_Y + 200)
		{
			_x = -100;
			_y = WINSIZE_Y_HALF - 200;
			_frameImg.startFrameX = 0;
			_frameImg.endFrameX = 2;
			_frameImg.frameX = _frameImg.startFrameX;
			_isDie = false;
			_isReLive = true;
		}
	}

	if (!_isReLive && !_isDie && !_boss->getIsDie())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left >= 0.0f)
		{
			if (!_isLeft)
			{
				_frameImg.startFrameX = 3;
				_frameImg.endFrameX = 5;
				_frameImg.frameX = 3;
				_frameImg.timeUpdateSec = 0.3f;
				_isLeft = true;
			}
			_x -= PLAYER_SPEED;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_frameImg.startFrameX = 3;
			_frameImg.endFrameX = 5;
			_frameImg.frameX = 5;
			_frameImg.timeUpdateSec = 0.3f;
			_isLeft = false;
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right <= WINSIZE_X)
		{
			_x += PLAYER_SPEED;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top >= 0.0f)
		{
			_y -= PLAYER_SPEED;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom <= WINSIZE_Y)
		{
			_y += PLAYER_SPEED;
		}

		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			_bullet->fire(_x, _y, PI_2, BULLET_SPEED, _bulletPower);
		}
		if (KEYMANAGER->isOnceKeyDown('S') && _bombCount > 0 && _bomb->getBomb().size() == 0)
		{
			_bombCount--;
			_bomb->fire(_x, _y, PI_2, BOMB_SPEED);
		}
	}

	if (_boss->getIsDie())
	{
		if (_frameImg.startFrameX != 0)
		{
			_frameImg.startFrameX = 0;
			_frameImg.endFrameX = 3;
			_frameImg.frameX = _frameImg.startFrameX;
			_isInvincible = true;
		}

		if (_y > WINSIZE_Y_HALF)
		{
			_y -= 1.0f;
		}

		if (_x < WINSIZE_X_HALF)
		{
			_x += 2.0f;
		}
		else
		{
			_x += 4.0f;
		}

		if (_x > WINSIZE_X + 1000)
		{
			SCENEMANAGER->changeScene("Title");
		}
	}

	_bullet->update();
	_bomb->update();

	collision();

	_rc = RectMakeCenter(_x, _y, _frameImg.img->getFrameWidth(), _frameImg.img->getFrameHeight());
}

void Player::render(void)
{
	_frameImg.img->frameAlphaRender(getMemDC(), _rc.left, _rc.top, _frameImg.frameX, _frameImg.frameY, _frameImg.alpha);

	if (_isDie)
	{
		_dieEffectImg.img->frameRender(getMemDC(), _x - _dieEffectImg.img->getFrameWidth() / 2, _y - _dieEffectImg.img->getFrameHeight() / 2, _dieEffectImg.frameX, _dieEffectImg.frameY);
	}

	_bullet->render();
	_bomb->render();
}

void Player::collision(void)
{
	// 미사일 충돌
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		// 미니언
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;

			if (IntersectRect(&rc, &_bullet->getBullet()[i].rc, &_em->getMinions()[j]->getRC()))
			{
				_bullet->removeBullet(i);

				_em->getMinions()[j]->setCurHP(_em->getMinions()[j]->getCurHP() - 1);

				if (_em->getMinions()[j]->getCurHP() == 0)
				{
					_score += 100;
					_em->removeMinion(j);
				}
				break;
			}
		}
	}

	if (_boss->getIsStart())
	{
		// 미사일 충돌
		for (int i = 0; i < _bullet->getBullet().size(); i++)
		{
			// 보스
			RECT rc;
			for (int j = 0; j < _boss->getBossParts().size(); j++)
			{
				if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
					&CollisionAreaResizing(_boss->getBossParts()[j]->rc, 40, 40)) && !_boss->getBossParts()[j]->isDestory)
				{
					_bullet->removeBullet(i);

					_boss->getBossParts()[j]->curHP -= 1;
					_boss->getBossParts()[j]->isHit = true;

					break;
				}
			}
		}
	}

	// 폭탄 충돌
	for (int i = 0; i < _bomb->getBomb().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;

			if (IntersectRect(&rc, &CollisionAreaResizing(_bomb->getBomb()[i].rc, 100, 100), &_em->getMinions()[j]->getRC()))
			{
				_em->getMinions()[j]->setCurHP(_em->getMinions()[j]->getCurHP() - 1);

				if (_em->getMinions()[j]->getCurHP() == 0)
				{
					_score += 100;
					_em->removeMinion(j);
				}
				break;
			}
		}
	}
}

void Player::frameUpdate(void)
{
	_frameImg.elpasedSec += TIMEMANAGER->getElapsedTime();

	if (_frameImg.frameX >= 3 && _frameImg.frameX <= 5)
	{
		if (_frameImg.elpasedSec >= _frameImg.timeUpdateSec)
		{
			if (_isLeft)
			{
				_frameImg.frameX++;

				if (_frameImg.frameX > _frameImg.endFrameX)
				{
					_frameImg.startFrameX = 6;
					_frameImg.endFrameX = 8;
					_frameImg.frameX = _frameImg.startFrameX;
					_frameImg.timeUpdateSec = 0.15f;
				}
			}
			else
			{
				_frameImg.frameX--;

				if (_frameImg.frameX < _frameImg.startFrameX)
				{
					_frameImg.startFrameX = 0;
					_frameImg.endFrameX = 2;
					_frameImg.frameX = _frameImg.startFrameX;
					_frameImg.timeUpdateSec = 0.15f;
				}
			}

			_frameImg.elpasedSec -= _frameImg.timeUpdateSec;
		}
	}
	else
	{
		if (_frameImg.elpasedSec >= _frameImg.timeUpdateSec)
		{
			if (_isInvincible)
			{
				if (_frameImg.alpha == 255)
				{
					_frameImg.alpha = 0;
				}
				else
				{
					_frameImg.alpha = 255;
				}
			}

			_frameImg.frameX++;

			if (_frameImg.frameX > _frameImg.endFrameX)
			{
				_frameImg.frameX = _frameImg.startFrameX;
			}

			_frameImg.elpasedSec -= _frameImg.timeUpdateSec;
		}
	}
}
