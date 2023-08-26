#include "Stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Return_Enemy.h"
#include "Spin_Enemy.h"

HRESULT EnemyManager::init(void)
{
	_bullet = new EnemyBullet;
	_bullet->init("Enemy_Bullet", 200, 2000);

	setSpinEnemy(10);

	for (int i = 0; i < 4; i++)
	{
		Enemy* _enemy;

		if (i == 3)
		{
			_enemy = new Return_Enemy;
			_enemy->init("Red_Enemy", PointMake(WINSIZE_X + (i * 60), WINSIZE_Y_HALF + (i * 60)), 5.0f, PI);
		}
		else
		{
			_enemy = new Return_Enemy;
			_enemy->init("Green_Enemy", PointMake(WINSIZE_X + (i * 60), WINSIZE_Y_HALF + (i * 60)), 5.0f, PI);
		}

		_vMinion.push_back(_enemy);
	}

	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}

	_bullet->release();
	SAFE_DELETE(_bullet);

	_vDieEffect.clear();
}

void EnemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end();)
	{
		(*_viMinion)->update();

		if ((*_viMinion)->getX() < 0.0f)
		{
			_viMinion = _vMinion.erase(_viMinion);
		}
		else ++_viMinion;
	}

	minionBulletFire();
	_bullet->update();
	collision();

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

void EnemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_bullet->render();

	for (_viDieEffect = _vDieEffect.begin(); _viDieEffect != _vDieEffect.end(); ++_viDieEffect)
	{
		_viDieEffect->img->frameRender(getMemDC(), _viDieEffect->x, _viDieEffect->y, _viDieEffect->frameX, _viDieEffect->frameY);
	}
}

void EnemyManager::setSpinEnemy(int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy* _enemy;
		_enemy = new Spin_Enemy;
		_enemy->init("Spin_Enemy", PointMake(WINSIZE_X + (i * 200), RND->getFromIntTo(WINSIZE_Y_HALF - 100, WINSIZE_Y_HALF + 100)), 5.0f, RND->getFromFloatTo(3.0f, 3.3f));

		_vMinion.push_back(_enemy);
	}
}

void EnemyManager::removeMinion(int arrNum)
{
	FrameImage dieEffect;
	ZeroMemory(&dieEffect, sizeof(FrameImage));
	dieEffect.img = IMAGEMANAGER->findImage("Death_Enemy");
	dieEffect.x = _vMinion[arrNum]->getX() - dieEffect.img->getFrameWidth() / 2;
	dieEffect.y = _vMinion[arrNum]->getY() - dieEffect.img->getFrameHeight() / 2;
	dieEffect.timeUpdateSec = 0.1f;
	_vDieEffect.push_back(dieEffect);

	_vMinion[arrNum]->release();
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void EnemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRC();

			_bullet->fire(
				rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2,
				getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, _player->getPosition().x, _player->getPosition().y),
				RND->getFromFloatTo(3.0f, 4.0f));
		}
	}
}

void EnemyManager::collision(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		for (int i = 0; i < _bullet->getBullet().size(); i++)
		{
			RECT rc;

			if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
				&CollisionAreaResizing(_player->getRect(), 
					(_player->getRect().right - _player->getRect().left) - 10,
					(_player->getRect().bottom - _player->getRect().top) - 5))
				&& !_player->getIsInvincible())
			{
				_bullet->removeBullet(i);
				_player->setIsDie(true);
			}
		}
	}
}
