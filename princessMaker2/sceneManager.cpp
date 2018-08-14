#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

//스태틱으로 선언이 되어서 초기화는 전역으로 초기화
gameNode* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

void sceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode* scene)
{
	//씬이 없다면 NULL값을 반환해라
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{

	mapSceneIter find = _mSceneList.find(sceneName);

	//이터레이터 == 맵의 엔드와 같다? -> 못찾았다
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬이 현재 씬이면 냅둔다
	if (find->second == _currentScene) return S_OK;

	//성공적으로 씬이 바뀌면 init() 함수를 실행한다
	if (SUCCEEDED(find->second->init()))
	{
		//현재씬에 어떤 정보가 있으면 (미리 어떤 씬이 배정되어있으면)
		//해당 씬을 릴리즈 해주고
		if (_currentScene) _currentScene->release();

		//바꾸려는 씬을 현재 씬으로 교체한다
		_currentScene = find->second;

		//지금 이 씬 변환구조의 그나마 단점을 꽂자면
		//바뀐 씬에서 데이터를 받아온 다음 이전씬을 해제해야하는 경우는
		//먼저 릴리즈가 불러와지기 때문에 따로 처리를 해줘야한다는 불편함이
		//있다.
		//뭐 대혁이나 민경이나 은지나가 써보다 불편하면 바꾸리라 본다

		return S_OK;
	}

	return E_FAIL;
}
