#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

// �ʱ�ȭ �Լ�
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

	//�Ŵ����� ����Ѵٸ�
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

//�޸� ���� �Լ�
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
	//�ʱ�ȭ���ٶ� GetDC�� ��������Ƿ� DC�������ش�
	ReleaseDC(_hWnd, _hdc);
}

//����
void gameNode::update(void)	  
{
	KEYMANAGER->update();
	SOUNDMANAGER->update();
}

//�׸���
void gameNode::render(void)
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;		//���� �� �� �غ��ÿ�1
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
