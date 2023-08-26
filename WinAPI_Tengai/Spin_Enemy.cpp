#include "Stdafx.h"
#include "Spin_Enemy.h"

HRESULT Spin_Enemy::init(const char* imageName, POINT position, float speed, float angle)
{
	Enemy::init(imageName, position, speed, angle);

	_fireCount = 0;

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFirecount = RND->getFromFloatTo(0.5f, 1.5f);

	return S_OK;
}

void Spin_Enemy::release(void)
{
	cout << "Spin Relase" << endl;
}

void Spin_Enemy::move(void)
{
	_x += cosf(_angle) * _speed;
	_y -= sinf(_angle) * _speed;

	if (_x > WINSIZE_X_HALF)
	{
		if (_speed > 3.0f)
		{
			_speed -= 0.02f;
		}
	}
	else
	{
		_speed += 0.05f;
	}
}

bool Spin_Enemy::bulletCountFire(void)
{
	if (_rndFirecount + _bulletFireCount <= TIMEMANAGER->getWorldTime() && _fireCount < 2)
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_rndFirecount = RND->getFromFloatTo(0.5f, 1.5f);
		_fireCount++;

		return true;
	}

	return false;
}
