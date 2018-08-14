#pragma once
#include "singletonBase.h"
#include <map>

//씬을 위한 게임노드 전방선언
class gameNode;
class princess;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>				mapSceneList;
	typedef map<string, gameNode*>::iterator	mapSceneIter;

private:
	static gameNode*	_currentScene;	//현재 씬
	mapSceneList		_mSceneList;

	princess* _princess;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//씬 추가 함수
	gameNode* addScene(string sceneName, gameNode* scene);

	//씬 변경
	HRESULT changeScene(string sceneName);

	void setPrincessAddressLink(princess* princess) { _princess = princess; }
	princess* getPrincessAddress() { return _princess; }
};

