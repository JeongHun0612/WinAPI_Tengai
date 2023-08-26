#pragma once
#include "GameNode.h"
#include "Animation.h"

class Player;

class UI : public GameNode
{
private:
	GImage* _bombImg;
	Animation* _bombAnim;

	GImage* _lifeImg;
	GImage* _scoreImg;

	Player* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void setPlayerMemoryAddress(Player* player) { _player = player; }

	UI() {}
	~UI() {}
};

