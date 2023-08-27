#include "Stdafx.h"
#include "Boss.h"
#include "Player.h"

HRESULT Boss::init(void)
{
	_x = WINSIZE_X + 300;
	_y = WINSIZE_Y + 100;

	_bullet = new BossBullet;
	_bullet->init(100, 3000);

	_body = new BossParts;
	_body->frameImg.img = IMAGEMANAGER->findImage("Boss_Body");
	_body->frameImg.startFrameX = 0;
	_body->frameImg.endFrameX = 4;
	_body->frameImg.frameX = _body->frameImg.startFrameX;
	_body->frameImg.frameY = 0;
	_body->frameImg.timeUpdateSec = 0.2f;
	_body->maxHP = 40;
	_body->curHP = _body->maxHP;
	_body->rc = RectMakeCenter(_x, _y, _body->frameImg.img->getFrameWidth(), _body->frameImg.img->getFrameHeight());
	_body->isDestory = false;

	_vBossParts.push_back(_body);

	_head = new BossParts;
	_head->frameImg.img = IMAGEMANAGER->findImage("Boss_Head");
	_head->frameImg.startFrameX = 0;
	_head->frameImg.endFrameX = 4;
	_head->frameImg.frameX = _head->frameImg.startFrameX;
	_head->frameImg.frameY = 0;
	_head->frameImg.elpasedSec = 0.0f;
	_head->frameImg.timeUpdateSec = 0.5f;
	_head->maxHP = 40;
	_head->curHP = _body->maxHP;
	_head->rc = RectMakeCenter(_x - 140, _y + 55, _head->frameImg.img->getFrameWidth(), _head->frameImg.img->getFrameHeight());
	_head->patternTimeElapsed = 0.0f;
	_head->patternTimeSec = 5.0f;
	_head->isDestory = false;

	_vBossParts.push_back(_head);

	_tail = new BossParts;
	_tail->frameImg.img = IMAGEMANAGER->findImage("Boss_Tail");
	_tail->frameImg.startFrameX = 0;
	_tail->frameImg.endFrameX = 0;
	_tail->frameImg.frameX = _tail->frameImg.startFrameX;
	_tail->frameImg.frameY = 0;
	_tail->maxHP = 40;
	_tail->curHP = _body->maxHP;
	_tail->rc = RectMakeCenter(_x - 100, _y - 238, _tail->frameImg.img->getFrameWidth(), _tail->frameImg.img->getFrameHeight());
	_tail->isDestory = false;

	_vBossParts.push_back(_tail);

	_speed = 2.0f;

	_isStart = false;
	_isDie = false;



	return S_OK;
}

void Boss::release(void)
{
}

void Boss::update(void)
{
	if (!_isDie && _isStart)
	{
		// 헤드 패턴 업데이트
		_head->patternTimeElapsed += TIMEMANAGER->getElapsedTime();

		if (_head->patternTimeElapsed >= _head->patternTimeSec)
		{
			_bullet->fire("Boss_Bullet",
				_head->rc.left + (_head->rc.right - _head->rc.left) / 2,
				_head->rc.top + (_head->rc.bottom - _head->rc.top) / 2,
				DEGREE_RADIAN(170),
				5.0f, 0);

			_head->patternTimeElapsed -= _vBossParts[1]->patternTimeSec;
		}


		// 바디 프레임 업데이트
		_body->frameImg.elpasedSec += TIMEMANAGER->getElapsedTime();
		if (_body->frameImg.elpasedSec >= _body->frameImg.timeUpdateSec)
		{
			_body->frameImg.frameX++;

			if (_body->frameImg.frameX == _body->frameImg.endFrameX)
			{
				_body->frameImg.frameX = _body->frameImg.startFrameX;
			}

			_body->frameImg.elpasedSec -= _body->frameImg.timeUpdateSec;
		}

		// 히트
		for (_viBossParts = _vBossParts.begin(); _viBossParts != _vBossParts.end(); ++_viBossParts)
		{
			if ((*_viBossParts)->isHit)
			{
				(*_viBossParts)->frameImg.frameY = 1;
				(*_viBossParts)->isHit = false;

				if ((*_viBossParts)->curHP == 0)
				{
					(*_viBossParts)->frameImg.frameX = (*_viBossParts)->frameImg.img->getMaxFrameX();
					(*_viBossParts)->isDestory = true;

					setDestoryEffect(
						(*_viBossParts)->rc.left + ((*_viBossParts)->rc.right - (*_viBossParts)->rc.left) / 2,
						(*_viBossParts)->rc.top + ((*_viBossParts)->rc.bottom - (*_viBossParts)->rc.top) / 2, 10);
				}
			}
			else
			{
				(*_viBossParts)->frameImg.frameY = 0;
			}
		}

		if (_body->isDestory && _head->isDestory && _tail->isDestory)
		{
			if (!_isDie)
			{
				_isDie = true;
				setDestoryEffect(_x, _y, 30);
			}
		}
	}

	// 렉트 업데이트
	_body->rc = RectMakeCenter(_x, _y, _body->frameImg.img->getFrameWidth(), _body->frameImg.img->getFrameHeight());
	_head->rc = RectMakeCenter(_x - 140, _y + 55, _head->frameImg.img->getFrameWidth(), _head->frameImg.img->getFrameHeight());
	_tail->rc = RectMakeCenter(_x - 100, _y - 238, _tail->frameImg.img->getFrameWidth(), _tail->frameImg.img->getFrameHeight());

	move();

	_bullet->update();

	effectFrameUpdate();
	collision();
}

void Boss::render(void)
{
	for (_viBossParts = _vBossParts.begin(); _viBossParts != _vBossParts.end(); ++_viBossParts)
	{
		(*_viBossParts)->frameImg.img->frameRender(getMemDC(),
			(*_viBossParts)->rc.left,
			(*_viBossParts)->rc.top,
			(*_viBossParts)->frameImg.frameX,
			(*_viBossParts)->frameImg.frameY);
	}

	_bullet->render();

	// 이펙트 렌더
	for (_viDieEffect = _vDieEffect.begin(); _viDieEffect != _vDieEffect.end(); ++_viDieEffect)
	{
		_viDieEffect->img->frameRender(getMemDC(), _viDieEffect->x, _viDieEffect->y, _viDieEffect->frameX, _viDieEffect->frameY);
	}
}

void Boss::move(void)
{
	if (_isStart)
	{
		if (_isDie)
		{
			_x += 0.5f;
			_y += 0.5f;
		}
		else
		{
			if (_x > WINSIZE_X - 300)
			{
				_x -= 1.0f;
				_y -= 0.5f;
			}
		}
	}
}

void Boss::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;

		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
			&CollisionAreaResizing(_player->getRect(), 60, 50)) && !_player->getIsInvincible())
		{
			_bullet->removeBullet(i);
			_player->setIsDie(true);
		}
	}
}

void Boss::effectFrameUpdate(void)
{
	// 이펙트 프레임 업데이트
	for (int i = 0; i < _vDieEffect.size(); i++)
	{
		_vDieEffect[i].elpasedSec += TIMEMANAGER->getElapsedTime();

		if (_vDieEffect[i].elpasedSec >= _vDieEffect[i].timeUpdateSec)
		{
			_vDieEffect[i].frameX++;
			_vDieEffect[i].elpasedSec -= _vDieEffect[i].timeUpdateSec;

			if (_vDieEffect[i].frameX >= _vDieEffect[i].img->getMaxFrameX())
			{
				_vDieEffect.erase(_vDieEffect.begin() + i);
			}
		}
	}
}

void Boss::setDestoryEffect(float x, float y, int count)
{
	for (int i = 0; i < count; i++)
	{
		FrameImage dieEffect;
		ZeroMemory(&dieEffect, sizeof(FrameImage));
		dieEffect.img = IMAGEMANAGER->findImage("Death_Enemy");
		dieEffect.x = x - RND->getFromIntTo(-60, 60);
		dieEffect.y = y - RND->getFromIntTo(-60, 60);
		dieEffect.elpasedSec = 0.0f;
		dieEffect.timeUpdateSec = RND->getFromFloatTo(0.2f, 0.5f);
		_vDieEffect.push_back(dieEffect);
	}
}
