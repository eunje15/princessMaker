#pragma once
#include "image.h"

//����� ����
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", 4000, 3360);
static image* _camera = IMAGEMANAGER->addImage("CAMERA", WINSIZEX, WINSIZEY);


class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;	//�Ŵ����� �ʱ�ȭ �Ҳ��� ����

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//Interface ���������Լ��� �������̵带 �ؼ� ���� ����
	//virtual void move() = 0;
	//virtual void jump() = 0;

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	image* getBackBuffer() { return _backBuffer; }

	//DC ������
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	gameNode();
	virtual ~gameNode();
};

