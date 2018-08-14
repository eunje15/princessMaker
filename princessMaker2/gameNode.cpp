#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

// 초기화 함수
HRESULT gameNode::init(void)  
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	//매니져를 사용한다면
	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		TXTDATA->init();
		INIDATA->init();
		DIALOG->init();
	}


	return S_OK;
}

//메모리 해제 함수
void gameNode::release(void)  
{

	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();

		INIDATA->releaseSingleton();

		DIALOG->release();
		DIALOG->releaseSingleton();
	}
	//초기화해줄때 GetDC를 사용했으므로 DC해제해준다
	ReleaseDC(_hWnd, _hdc);
}

//연산
void gameNode::update(void)	  
{
	KEYMANAGER->update();
	SOUNDMANAGER->update();
}

//그리기
void gameNode::render(void)
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;		//조사 한 번 해보시요1
	HDC hdc;
	static TCHAR str[256];
	static bool dadOrDaughter = _dadOrDaughter;
	int len;

	switch (iMessage)
	{
	    case WM_CHAR:
			if (!_isInput) break;
			switch (wParam)
			{
			case  VK_BACK:
				if (_inputData.size())
				{
					_inputData.pop_back();
					_inputData.pop_back();
				}
				break;
			case VK_RETURN:
				break;
			default:
				if (dadOrDaughter != _dadOrDaughter)
				{
					_inputData.clear();
					dadOrDaughter = _dadOrDaughter;
				}
				if (wParam > 127)
				{
					if(_inputData.size() < 8)
						_inputData.push_back((TCHAR)wParam);
				}
				break;
			}
	    	InvalidateRect(hWnd, NULL, false);
	    break;
		
	    case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, 100, 100, str, lstrlen(str));
			EndPaint(hWnd, &ps);
	    break;

		case WM_LBUTTONDOWN:
			_leftButtonDown = true;
			
		break;
		case WM_LBUTTONUP:
			_leftButtonDown = false;
		break;
		
		case WM_MOUSEMOVE:
			_ptMouse.x = LOWORD(lParam);
			_ptMouse.y = HIWORD(lParam);
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
