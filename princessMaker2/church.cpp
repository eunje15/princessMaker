#include "stdafx.h"
#include "church.h"
#include "princess.h"

church::church()
{
}


church::~church()
{
}

HRESULT church::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();

	_npc.img = IMAGEMANAGER->findImage("peopleFace");
	_npc.frameX = 2, _npc.frameY = 0;
	setDialog("「교회에 잘 오셨습니다. 교회에서는 한번에 100G를 기부 받고 있습니다」");
	_dialogIdx = 0;
	_type = CHURCH_NONE;
	_dialogType = DIALOG_ING;
	_fin = false;

	for (int i = 0; i < 2; i++)
	{
		_chooseBox[i].rc = RectMake(610, 295 + i * 28, 120, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "기부한다";
	_chooseBox[1].str = "안한다";

	_pKarma.str = "인과", _pKarma.data = _princess->getStatus().karma;
	_pKarma.strRc = RectMake(510, 340, 80, 20);
	_pKarma.dataRc = RectMake(590, 340, 30, 20);

	_pKarma.progressBar = new progressBar;
	_pKarma.progressBar->init(620, 340, 110, 20);
	_pKarma.progressBar->setGauge(_pKarma.data, 500);

	_haveMoney = false;

	return S_OK;
}

void church::update()
{
	if (_dialogType == DIALOG_ING) return;

	switch (_type)
	{
	case CHURCH_FIN:
		for (int i = 0; i < 2; i++)
		{
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
					{
						string str;
						if (_princess->getGold() >= 100)
						{
							str = "「감사합니다.당신들 부녀에게 신의 은총이 함께하기를」";
							_haveMoney = true;
						}
						else
							str = "「돈이 없습니다」";
						setDialog(str);
						_type = CHURCH_SELECT;
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
					}
					else if (i == 1)
					{
						string str = "「그렇습니까, 아쉽군요」";
						setDialog(str);
						_type = CHURCH_NO_SELECT;
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
					}
				}
			}
		}
		break;
		case CHURCH_SELECT:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				_fin = true;
		break;
		case CHURCH_NO_SELECT:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				_fin = true;
		break;
	}
}

void church::render()
{
	IMAGEMANAGER->findImage("frame")->render(DC, 20, 295);
	_npc.img->frameRender(DC, 30, 305, _npc.frameX, _npc.frameY);
	IMAGEMANAGER->findImage("status4Back")->render(DC, 170, 300);
	if (dialogRender())
	{
		for (int i = 0; i < _vDialog.size(); i++)
		{
			TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
		}
		switch (_type)
		{
		case CHURCH_FIN:
			IMAGEMANAGER->findImage("2Back")->render(DC, 600, 280);
			for (int i = 0; i < 2; i++)
			{
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
		case CHURCH_SELECT:
			if (!_haveMoney) break;
			IMAGEMANAGER->findImage("progress1Back")->render(DC, 500, 330);
			HBRUSH brush, oldBrush;
			brush = CreateSolidBrush(RGB(111, 17, 17));
			oldBrush = (HBRUSH)SelectObject(DC, brush);
			FillRect(DC, &_pKarma.strRc, brush);
			Rectangle(DC, _pKarma.strRc.left, _pKarma.strRc.top, _pKarma.strRc.right, _pKarma.strRc.bottom);
			TextOut(DC, _pKarma.strRc.left, _pKarma.strRc.top + 2, _pKarma.str.c_str(), strlen(_pKarma.str.c_str()));
			SelectObject(DC, oldBrush);
			DeleteObject(brush);
			brush = CreateSolidBrush(RGB(0, 0, 0));
			oldBrush = (HBRUSH)SelectObject(DC, brush);
			Rectangle(DC, _pKarma.dataRc.left, _pKarma.dataRc.top, _pKarma.dataRc.right, _pKarma.dataRc.bottom);
			char str[128];
			sprintf_s(str, "%3d", _pKarma.data);
			TextOut(DC, _pKarma.dataRc.left + 2, _pKarma.dataRc.top + 2, str, strlen(str));
			SelectObject(DC, oldBrush);
			DeleteObject(brush);
			_pKarma.progressBar->render();
		break;
		}
	}
}

void church::release()
{
}

void church::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	_vDialog.push_back("시스터 리이");
	while (1)
	{
		if (strSize > 28)
		{
			_vDialog.push_back(str.substr(idx, 28));
			idx += 28;
			strSize -= 28;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

bool church::dialogRender()
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
		if (_type == CHURCH_NONE) _type = CHURCH_FIN;
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}
