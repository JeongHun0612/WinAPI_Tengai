#pragma once
#include "SingletonBase.h"

// ���� ����
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*>			 mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	GameNode* _currentScene;			// ���� ��
	mapSceneList _mSceneList;			// �� ���

public:
	HRESULT init();
	void release();
	void update();
	void render();

	GameNode* getCurScene() { return _currentScene; }
	GameNode* addScene(string sceneName, GameNode* scene);

	HRESULT changeScene(string sceneName);

	SceneManager() : _currentScene(nullptr) {}
	~SceneManager() {}
};