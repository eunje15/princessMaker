#pragma once
#include "image.h"

//백버퍼 선언
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", 4000, 3360);
static image* _camera = IMAGEMANAGER->addImage("CAMERA", WINSIZEX, WINSIZEY);


class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;	//매니져들 초기화 할껀지 여부

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//Interface 순수가상함수로 오버라이드를 해서 찍어내는 개념
	//virtual void move() = 0;
	//virtual void jump() = 0;

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	image* getBackBuffer() { return _backBuffer; }

	//DC 접근자
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	gameNode();
	virtual ~gameNode();
};

