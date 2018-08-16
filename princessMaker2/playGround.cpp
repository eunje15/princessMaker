#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init(void)	
{
	gameNode::init(true);
	_cameraCenter = PointMake(WINSIZEX / 2, WINSIZEY / 2);

	image_init();
	sound_add();
	
	_princess = new princess;
	_princess->init();

	SCENEMANAGER->setPrincessAddressLink(_princess);

	SCENEMANAGER->addScene("�������Է�", new dataInput);
	SCENEMANAGER->addScene("���ѷα�", new prologueDialog);
	SCENEMANAGER->addScene("���־�", new princessScene);
	SCENEMANAGER->addScene("��ŸƮ��", new startScene);
	
	SCENEMANAGER->changeScene("���־�");
	//_str = TXTDATA->txtLoadCsv("dialog/���ڸ��ɷ�ġ.csv", "ó���ڸ�");

	/*
	SCENEMANAGER->addScene("�׽�Ʈ", new testClass);
	SCENEMANAGER->changeScene("�׽�Ʈ");
	*/

	//SCENEMANAGER->addScene("����", new mapTool);
	//SCENEMANAGER->changeScene("����");
	_type = GAME;

	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();
}

void playGround::update(void)	
{
	gameNode::update();

	SCENEMANAGER->update();

	if (_type == MAPTOOL)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_cameraCenter.y -= 50;
			if (_cameraCenter.y < WINSIZEY / 2)
				_cameraCenter.y = WINSIZEY / 2;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_cameraCenter.y += 50;
			if (_cameraCenter.y > 1600 - WINSIZEY / 2)
				_cameraCenter.y = 1600 - WINSIZEY / 2;
		}
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_cameraCenter.x -= 50;
			if (_cameraCenter.x < WINSIZEX / 2)
				_cameraCenter.x = WINSIZEX / 2;
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_cameraCenter.x += 50;
			if (_cameraCenter.x > 4000 - WINSIZEX / 2)
				_cameraCenter.x = 4000 - WINSIZEX / 2;
		}
	}
}

void playGround::render(void)
{
	//�����ȭ�� �� �� ��Ƶд�
	if (_type == MAPTOOL)
	{
		PatBlt(getMemDC(), _cameraCenter.x - WINSIZEX / 2, _cameraCenter.y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
		PatBlt(_camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	}
	else
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//////////////////////////////////////////////////////////

	//HFONT font, oldFont;
	//font = CreateFont(18, 0, 0, 0, 400, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));
	//oldFont = (HFONT)SelectObject(DC, font);

	SCENEMANAGER->render();

	//SelectObject(DC, oldFont);
	//DeleteObject(font);
	//IMAGEMANAGER->findImage("back")->render(DC);
	//IMAGEMANAGER->findImage("body10")->frameRender(DC, 50, 50, 0, 2);
	/*char str[128];
	sprintf_s(str, "%d,%d", _ptMouse.x, _ptMouse.y);
	TextOut(_camera->getMemDC(), 700, 20, str,strlen(str));*/
	//////////////////////////////////////////////////////////
	//TIMEMANAGER->render(getMemDC());
	if (_type == MAPTOOL)
	{
		GdiTransparentBlt(this->getBackBuffer()->getMemDC(), _cameraCenter.x - WINSIZEX / 2, _cameraCenter.y - WINSIZEY / 2, WINSIZEX, WINSIZEY,
			_camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(255, 255, 255));
		this->getBackBuffer()->render(getHDC(), 0, 0, _cameraCenter.x - WINSIZEX / 2, _cameraCenter.y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
	}
	else
		this->getBackBuffer()->render(getHDC(), 0, 0);
}

