#include "Stdafx.h"
#include "Bullet.h"

HRESULT Bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void Bullet::release(void)
{
	_vBullet.clear();
}

void Bullet::update(void)
{
	move();
}

void Bullet::render(void)
{
	draw();
}

void Bullet::fire(float x, float y, float angle, float speed, int power)
{
	if (_bulletMax <= _vBullet.size()) return;

	switch (power)
	{
	case 0:
		for (int i = 0; i < 2; i++)
		{
			tagBullet bullet;
			ZeroMemory(&bullet, sizeof(tagBullet));

			bullet.img = IMAGEMANAGER->findImage(_imageName);
			bullet.frameX = RND->getFromIntTo(0, bullet.img->getMaxFrameX());
			bullet.speed = speed;
			bullet.angle = angle;
			bullet.x = bullet.fireX = (i * 100) + x;
			bullet.y = bullet.fireY = (i * 20) + y;
			bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

			_vBullet.push_back(bullet);
		}

		break;
	case 1:
		break;
	case 2:
		break;
	}
}

void Bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		// ∫“∏¥ ¡¬«• ∫Ø∞Ê
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		// ∫“∏¥ ªË¡¶ ¡∂∞«
		if (_range <= MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void Bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->frameX, _viBullet->img->getFrameY());
	}
}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT EnemyBullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void EnemyBullet::release(void)
{
	_vBullet.clear();
}

void EnemyBullet::update(void)
{
	move();

	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].timeUpdateSec += TIMEMANAGER->getElapsedTime();

		if (_vBullet[i].timeUpdateSec > 0.5f)
		{
			_vBullet[i].frameX++;

			if (_vBullet[i].frameX == _vBullet[i].img->getMaxFrameX())
			{
				_vBullet[i].frameX = 0;
			}

			_vBullet[i].timeUpdateSec = 0.0f;
		}
	}
}

void EnemyBullet::render(void)
{
	draw();
}

void EnemyBullet::fire(float x, float y, float angle, float speed)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.frameX = 0;
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void EnemyBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		// ∫“∏¥ ¡¬«• ∫Ø∞Ê
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		// ∫“∏¥ ªË¡¶ ¡∂∞«
		if (_range <= MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void EnemyBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->frameX, _viBullet->img->getFrameY());
	}
}

void EnemyBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
