#include "Stdafx.h"
#include "PowerItem.h"

HRESULT PowerItem::init(void)
{
    _img = IMAGEMANAGER->findImage("Power_Item");
    _anim = new Animation;
    _anim->init(_img->getWidth(), _img->getHeight(), _img->getFrameWidth(), _img->getFrameHeight());
    _anim->setFPS(0.5f);
    _anim->AniStart();

    _x = WINSIZE_X_HALF;
    _y = WINSIZE_Y_HALF;
    _rc = RectMakeCenter(_x, _y, _anim->getFrameWidth(), _anim->getFrameHeight());

    _angle = 45;

    return S_OK;
}

void PowerItem::release(void)
{
    SAFE_DELETE(_anim);
}

void PowerItem::update(void)
{
    _anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

    _x += cosf(DEGREE_RADIAN(_angle)) * ITEM_SPEED;
    _y -= sinf(DEGREE_RADIAN(_angle)) * ITEM_SPEED;

    if (_rc.left <= 0)
    {
        _x = _anim->getFrameWidth();
        _angle = 180 - _angle;
    }

    if (_rc.right >= WINSIZE_X)
    {
        _x = WINSIZE_X - _anim->getFrameWidth();
        _angle = 180 - _angle;
    }

    if (_rc.top <= 0)
    {
        _y = _anim->getFrameHeight();
        _angle = 360 - _angle;
    }

    if (_rc.bottom >= WINSIZE_Y)
    {
        _y = WINSIZE_Y - _anim->getFrameHeight();
        _angle = 360 - _angle;
    }

    _rc = RectMakeCenter(_x, _y, _anim->getFrameWidth(), _anim->getFrameHeight());
}

void PowerItem::render(void)
{
    _img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
}
