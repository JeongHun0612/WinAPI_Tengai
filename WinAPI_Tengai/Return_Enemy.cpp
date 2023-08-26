#include "Stdafx.h"
#include "Return_Enemy.h"

Return_Enemy::Return_Enemy() {
	// ! Do Nothing;
}

Return_Enemy::~Return_Enemy() {
	// ! Do Nothing;
}

void Return_Enemy::move()
{ 
	_x -= _speed;

	_speed -= 0.02f;
}