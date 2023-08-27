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
		for (int i = 0; i < 3; i++)
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
	case 2:
		for (int i = 0; i < 4; i++)
		{
			tagBullet bullet;
			ZeroMemory(&bullet, sizeof(tagBullet));

			bullet.img = IMAGEMANAGER->findImage(_imageName);
			bullet.frameX = RND->getFromIntTo(0, bullet.img->getMaxFrameX());
			bullet.speed = speed;
			bullet.angle = angle + RND->getFromFloatTo(-0.2f, 0.2f);
			bullet.x = bullet.fireX = (i * 100) + x;
			bullet.y = bullet.fireY = (i * 20) + y;
			bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

			_vBullet.push_back(bullet);
		}
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


HRESULT Bomb::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void Bomb::release(void)
{
}

void Bomb::update(void)
{
	move();
}

void Bomb::render(void)
{
	draw();
}

void Bomb::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBomb.size()) return;

	tagBullet bomb;
	ZeroMemory(&bomb, sizeof(tagBullet));

	bomb.img = IMAGEMANAGER->findImage(_imageName);
	bomb.speed = speed;
	bomb.angle = angle;
	bomb.x = bomb.fireX = x;
	bomb.y = bomb.fireY = y;
	bomb.explosion = false;
	bomb.rc = RectMakeCenter(bomb.x, bomb.y, bomb.img->getFrameWidth(), bomb.img->getFrameHeight());

	_vBomb.push_back(bomb);
}

void Bomb::move(void)
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end();)
	{
		if (getDistance(_viBomb->fireX, _viBomb->fireY, _viBomb->x, _viBomb->y) < _range)
		{
			_viBomb->x += cosf(_viBomb->angle) * _viBomb->speed;
		}
		else
		{
			if (!_viBomb->explosion)
			{
				_viBomb->img = IMAGEMANAGER->findImage("Miko_Bomb");
				_viBomb->frameX = 0;
				_viBomb->timeUpdateSec = 0.0f;
				_viBomb->explosion = true;
			}
		}

		_viBomb->rc = RectMakeCenter(_viBomb->x, _viBomb->y, _viBomb->img->getFrameWidth(), _viBomb->img->getFrameHeight());

		_viBomb->timeUpdateSec += TIMEMANAGER->getElapsedTime();

		if (_viBomb->timeUpdateSec > 0.3f)
		{
			_viBomb->frameX++;

			_viBomb->timeUpdateSec = 0.0f;
		}

		if (_viBomb->explosion && _viBomb->frameX == _viBomb->img->getMaxFrameX())
		{
			_viBomb = _vBomb.erase(_viBomb);
		}
		else _viBomb++;
	}
}

void Bomb::draw(void)
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		_viBomb->img->frameRender(getMemDC(), _viBomb->rc.left, _viBomb->rc.top, _viBomb->frameX, _viBomb->img->getFrameY());
	}
}

// =========================================================================================================

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

		if (_vBullet[i].timeUpdateSec > 0.8f)
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
	if (_bulletMax <= _vBullet.size()) return;

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

// =========================================================================================================

HRESULT BossBullet::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void BossBullet::release(void)
{
	_vBullet.clear();
}

void BossBullet::update(void)
{
	move();

	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].timeUpdateSec += TIMEMANAGER->getElapsedTime();

		if (_vBullet[i].timeUpdateSec > 0.2f)
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

void BossBullet::render(void)
{
	draw();
}

void BossBullet::fire(const char* imageName, float x, float y, float angle, float speed, int pattern)
{
	if (_bulletMax <= _vBullet.size()) return;

	switch (pattern)
	{
	case 0:
		for (int i = 0; i < 6; i++)
		{
			tagBullet bullet;
			ZeroMemory(&bullet, sizeof(tagBullet));

			bullet.img = IMAGEMANAGER->findImage(imageName);
			bullet.frameX = 0;
			bullet.speed = speed;
			bullet.angle = angle - (i * 0.175f);
			bullet.x = bullet.fireX = x;
			bullet.y = bullet.fireY = y;
			bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

			_vBullet.push_back(bullet);
		}
		break;
	case 1:
		break;
	}
}

void BossBullet::move(void)
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

void BossBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->frameX, _viBullet->img->getFrameY());
	}
}

void BossBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
