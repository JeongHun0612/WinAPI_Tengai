#include "Stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Return_Enemy.h"
#include "Spin_Enemy.h"

HRESULT EnemyManager::init(void)
{
	_bullet = new EnemyBullet;
	_bullet->init("Enemy_Bullet", 200, 5000);

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
	// 애너미 업데이트
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end();)
	{
		(*_viMinion)->update();

		if ((*_viMinion)->getX() < 0.0f)
		{
			SAFE_DELETE((*_viMinion));
			_viMinion = _vMinion.erase(_viMinion);
		}
		else ++_viMinion;
	}

	// 애너미 스폰
	minionSpawn();

	// 애너미 총알 생성
	minionBulletFire();

	// 애너미 업데이트
	_bullet->update();

	// 아이템 업데이트
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->update();
	}

	if (_player->getIsInvincible())
	{
		for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end();)
		{
			SAFE_DELETE((*_viMinion));
			_viMinion = _vMinion.erase(_viMinion);
		}
	}

	// 충동 업데이트
	collision();


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

void EnemyManager::render(void)
{
	// 애너미 렌더
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	// 불릿 렌더
	_bullet->render();

	// 아이템 렌더
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->render();
	}

	// 이펙트 렌더
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

void EnemyManager::setReturnEnemy(int count)
{
	int spawnY = (RND->getInt(2) == 0) ? 100 : WINSIZE_Y_HALF;

	for (int i = 0; i < count; i++)
	{
		Enemy* _enemy;

		if (i == count - 1)
		{
			_enemy = new Return_Enemy;
			_enemy->init("Red_Enemy", PointMake(WINSIZE_X + (i * 60), spawnY + (i * 60)), 5.0f, PI);
		}
		else
		{
			_enemy = new Return_Enemy;
			_enemy->init("Green_Enemy", PointMake(WINSIZE_X + (i * 60), spawnY + (i * 60)), 5.0f, PI);
		}

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

	if (_vMinion[arrNum]->getImageName() == "Red_Enemy")
	{
		PowerItem* item = new PowerItem;
		item->init(PointMake(_vMinion[arrNum]->getX(), _vMinion[arrNum]->getY()));
		_vItem.push_back(item);
	}

	_vMinion[arrNum]->release();
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void EnemyManager::minionSpawn(void)
{
	if (_player->getIsInvincible()) return;

	float static spinEnemySpanwTime = 0.0f;
	float static returnEnemySpanwTime = 0.0f;

	spinEnemySpanwTime += TIMEMANAGER->getElapsedTime();
	returnEnemySpanwTime += TIMEMANAGER->getElapsedTime();

	if (spinEnemySpanwTime >= 4.0f)
	{
		setSpinEnemy(RND->getFromIntTo(5, 8));
		spinEnemySpanwTime = 0.0f;
	}

	if (returnEnemySpanwTime >= 10.0f)
	{
		setReturnEnemy(RND->getFromIntTo(3, 5));
		returnEnemySpanwTime = 0.0f;
	}
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
				RND->getFromFloatTo(5.0f, 6.0f));
		}
	}
}

void EnemyManager::collision(void)
{
	// 애너미 총알 충돌
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
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

	// 아이템 충돌
	for (_viItem = _vItem.begin(); _viItem != _vItem.end();)
	{
		RECT rc;
		
		if (IntersectRect(&rc, &(*_viItem)->getRect(), &_player->getRect()))
		{
			_viItem = _vItem.erase(_viItem);
			_player->setScore(_player->getScore() + 500);

			if (_player->getPower() < 2)
			{
				_player->setPower(_player->getPower() + 1);
			}
		}
		else  ++_viItem;
	}
}
