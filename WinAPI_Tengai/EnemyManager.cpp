#include "Stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::init(void)
{
	for (int i = 0; i < 5; i++)
	{
		Enemy* _enemy;
		_enemy = new Enemy;
		_enemy->init("Enemy1", PointMake(WINSIZE_X + (i * 200), WINSIZE_Y_HALF), 5.0f, 3.141592f);
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
}

void EnemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
}

void EnemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
}

void EnemyManager::setMinion(const char* imageName, int count, float speed)
{
}

void EnemyManager::removeMinion(int arrNum)
{
}

void EnemyManager::minionBulletFire(void)
{
}

void EnemyManager::collision(void)
{
}
