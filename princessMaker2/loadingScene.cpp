#include "stdafx.h"
#include "loadingScene.h"
#include "progressBar.h"

//멤버 이니셜라이즈~
loadingScene::loadingScene()
	: _background(nullptr),
	_loadingBar(nullptr),
	_currentCount(0)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{

	_background = IMAGEMANAGER->addImage("배그", "로비.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);

	//쓰레드를 사용하기위한 쓰레드 초기화
	CreateThread(
		NULL,			//스레드 보안속성(자식윈도우가 있을때) hWnd -> 자식윈도우인가 부모윈도우
		0,				//스레드의 스택크기 (NULL로 하면 메인쓰레드의 스택크기와 동일)
		ThreadFunction,	//스레드 사용함수 명
		this,			//스레드 매개변수 (현재는 this이므로 본 클래스)
		NULL,			//스레드의 특성(NULL로 두면 바로 실행한다)
		0				//스레드 생성 후 스레드의 ID를 넘겨줌 보통 NULL로 둔다
	);

	return S_OK;

}

void loadingScene::release()
{
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->setGauge(_currentCount, LOADINGMAX);

	//임의로 100개만 돌려보자!
	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("인게임씬");
	}
}

void loadingScene::render()
{
	_background->render(getMemDC(), 0, 0);
	_loadingBar->render();
}

//로딩은 이 싱글쓰레드가 전담한다, 로딩이 끝나면 이 쓰레드는 자동종료된다.
DWORD CALLBACK ThreadFunction(LPVOID lpParameter)
{
	loadingScene* loadHelper = (loadingScene*)lpParameter;

	//임의로 이미지는 100개 정도만 돌립시다
	while (loadHelper->_currentCount != LOADINGMAX)
	{
		IMAGEMANAGER->addImage("인게임", "인게임.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 9, 255));
		Sleep(1);
		
		loadHelper->_currentCount++;
	}


	return 0;
}
