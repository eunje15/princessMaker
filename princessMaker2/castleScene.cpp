#include "stdafx.h"
#include "castleScene.h"
#include "princess.h"

castleScene::castleScene()
{
}


castleScene::~castleScene()
{
}

HRESULT castleScene::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();
	SOUNDMANAGER->play("town");
	_npc.img = IMAGEMANAGER->findImage("peopleFace");
	_npc.frameX = 12, _npc.frameY = 1;
	_dialogIdx = 0;
	_dialogType = DIALOG_ING;
	_type = CASTLE_NONE;
	_fin = false;
	setDialog("성에 왔습니다");

	for (int i = 0; i < 2; i++)
	{
		_chooseBox[i].rc = RectMake(580, 310 + i * 28, 120, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "문지기";
	_chooseBox[1].str = "청년 무관";

	_canMeet = true;
	_doorKeeperIdx = 0;
	return S_OK;
}

void castleScene::update()
{
	if (_dialogType == DIALOG_ING) return;
	switch (_type)
	{
	case CASTLE_FIN:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_type = CASTLE_SELECT;
			setDialog("어 왔구나. 이번엔 누굴 만나려고 하는데?");
			_dialogIdx = 0;
			_dialogType = DIALOG_ING;
			_type = CASTLE_SELECT;
		}
	break;
	case CASTLE_SELECT:
		for (int i = 0; i < 2; i++)
		{
			if (!_canMeet && i == 1) break;
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
					{
						setDialog("나같은 녀석하고 친해져봐야 별 볼일 없을텐데");
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
						_type = CASTLE_DOORKEEPER;
					}
				}
			}
		}
	break;
	case CASTLE_DOORKEEPER:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_doorKeeperIdx++;
			if (_doorKeeperIdx == 2)
			{
				setDialog("여성에게 가장 중요한 것은 기품이라고 생각해");
				_dialogIdx = 0;
				_dialogType = DIALOG_ING;
			}
			else if (_doorKeeperIdx == 3)
				_fin = true;
		}
	break;
	case CASTLE_NONE:
	break;
	}
}

void castleScene::render()
{
	IMAGEMANAGER->findImage("wideBack")->render(DC, 170, 300);
	if (dialogRender())
	{
		for (int i = 0; i < _vDialog.size(); i++)
		{
			TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
		}
	}
	
	switch (_type)
	{
	case CASTLE_FIN:
		break;
	case CASTLE_SELECT:
		IMAGEMANAGER->findImage("frame")->render(DC, 20, 295);
		_npc.img->frameRender(DC, 30, 305, _npc.frameX, _npc.frameY);

		IMAGEMANAGER->findImage("2Back")->render(DC, 570, 300);
		for (int i = 0; i < 2; i++)
		{
			if (!_canMeet && i == 1) break;
			if (_chooseBox[i].isSelected)
			{
				HBRUSH brush, oldBrush;
				brush = CreateSolidBrush(RGB(43, 0, 0));
				oldBrush = (HBRUSH)SelectObject(DC, brush);
				FillRect(DC, &_chooseBox[i].rc, brush);
				SelectObject(DC, oldBrush);
				DeleteObject(brush);
			}
			TextOut(DC, _chooseBox[i].rc.left + 2, _chooseBox[i].rc.top + 5, _chooseBox[i].str.c_str(), strlen(_chooseBox[i].str.c_str()));
		}
		break;
	case CASTLE_DOORKEEPER:
		IMAGEMANAGER->findImage("frame")->render(DC, 20, 295);
		_npc.img->frameRender(DC, 30, 305, _npc.frameX, _npc.frameY);
		if (_doorKeeperIdx == 1)
		{
			IMAGEMANAGER->findImage("wideBack")->render(DC, 230, 360);
			string str = "딸래미은(는) 문지기와 여러가지 얘기를 했다...";
			TextOut(DC, 240, 370, str.c_str(), strlen(str.c_str()));
		}
		break;
	case CASTLE_NONE:
		break;
	}
	
}

void castleScene::release()
{
}

void castleScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	while (1)
	{
		if (strSize > 50)
		{
			_vDialog.push_back(str.substr(idx, 50));
			idx += 50;
			strSize -= 50;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

bool castleScene::dialogRender()
{
	if (_dialogType != DIALOG_ING) return true;

	if (_dialogIdx < _vDialog.size())
	{
		string temp = DIALOG->getCurrentDialog();
		if (temp == "end")
		{
			_dialogIdx++;
			if (_dialogIdx < _vDialog.size())
				DIALOG->setDialog(_vDialog[_dialogIdx], 5);
		}
		else
		{
			if (_dialogIdx > 0)
			{
				for (int i = 0; i < _dialogIdx; i++)
				{
					TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			TextOut(DC, 180, 310 + _dialogIdx * 30, temp.c_str(), strlen(temp.c_str()));
		}
	}
	else
	{
		if (_type == CASTLE_NONE) _type = CASTLE_FIN;
		//if (_type == CASTLE_DOORKEEPER) _doorKeeperIdx++;
		_dialogType = DIALOG_FIN;

		return true;
	}
	return false;
}
