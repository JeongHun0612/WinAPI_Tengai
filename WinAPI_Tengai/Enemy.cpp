#include "Stdafx.h"
#include "Enemy.h"

Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)),
					 _x(0.0f),
					 _y(0.0f),
					 _speed(0.0f),
					 _angle(0.0f),
					 _rndFirecount(0.0f),
					 _bulletFireCount(0.0f)
{}

HRESULT Enemy::init(void)
{
	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position, float speed, float angle)
{
	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_anim = new Animation;
	_anim->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
	_anim->setFPS(0.1f);
	_anim->AniStart();

	_maxHP = 1;
	_curHP = _maxHP;

	_x = position.x;
	_y = position.y;

	_speed = speed;
	_angle = angle;

	_rc = RectMakeCenter(_x, _y, _anim->getFrameWidth(), _anim->getFrameHeight());

	return S_OK;
}

void Enemy::release(void)
{
	// ! Do Nothing;
}

void Enemy::update(void)
{
	move();

	_anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_rc = RectMakeCenter(_x, _y, _anim->getFrameWidth(), _anim->getFrameHeight());
}

void Enemy::render(void)
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
}

void Enemy::move(void)
{
	//! Do Nothing
}

bool Enemy::bulletCountFire(void)
{
	//! Do Nothing
	return false;
}