#include "stdafx.h"
#include "loadingScene.h"
#include "progressBar.h"

//��� �̴ϼȶ�����~
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

	_background = IMAGEMANAGER->addImage("���", "�κ�.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);

	//�����带 ����ϱ����� ������ �ʱ�ȭ
	CreateThread(
		NULL,			//������ ���ȼӼ�(�ڽ������찡 ������) hWnd -> �ڽ��������ΰ� �θ�������
		0,				//�������� ����ũ�� (NULL�� �ϸ� ���ξ������� ����ũ��� ����)
		ThreadFunction,	//������ ����Լ� ��
		this,			//������ �Ű����� (����� this�̹Ƿ� �� Ŭ����)
		NULL,			//�������� Ư��(NULL�� �θ� �ٷ� �����Ѵ�)
		0				//������ ���� �� �������� ID�� �Ѱ��� ���� NULL�� �д�
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

	//���Ƿ� 100���� ��������!
	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("�ΰ��Ӿ�");
	}
}

void loadingScene::render()
{
	_background->render(getMemDC(), 0, 0);
	_loadingBar->render();
}

//�ε��� �� �̱۾����尡 �����Ѵ�, �ε��� ������ �� ������� �ڵ�����ȴ�.
DWORD CALLBACK ThreadFunction(LPVOID lpParameter)
{
	loadingScene* loadHelper = (loadingScene*)lpParameter;

	//���Ƿ� �̹����� 100�� ������ �����ô�
	while (loadHelper->_currentCount != LOADINGMAX)
	{
		IMAGEMANAGER->addImage("�ΰ���", "�ΰ���.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 9, 255));
		Sleep(1);
		
		loadHelper->_currentCount++;
	}


	return 0;
}
