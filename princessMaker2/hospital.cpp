#include "stdafx.h"
#include "hospital.h"
#include "princess.h"

hospital::hospital()
{
}


hospital::~hospital()
{
}

HRESULT hospital::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();

	_npc.img = IMAGEMANAGER->findImage("peopleFace");
	_npc.frameX = 9, _npc.frameY = 1;
	_sickPer = _princess->getStatus().stress - _princess->getStatus().hp;
	//_sickPer = 30;
	if (_sickPer >= 10)
		_isSick = true;
	else
		_isSick = false;

	if (_isSick)
		setDialog("「어디어디,내가 진찰해보지」");
	else
		setDialog("「여기는 병원이다. 아프면 오라구.」");

	_dialogIdx = 0;
	_dialogType = DIALOG_ING;
	_type = HOSPITAL_NONE;
	_fin = false;

	for (int i = 0; i < 2; i++)
	{
		_chooseBox[i].rc = RectMake(610, 295 + i * 28, 120, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "예";
	_chooseBox[1].str = "아니오";

	_pStress.str = "스트레스", _pStress.data = _princess->getStatus().stress;
	_pStress.strRc = RectMake(510, 340, 80, 20);
	_pStress.dataRc = RectMake(590, 340, 30, 20);

	_pStress.progressBar = new progressBar;
	_pStress.progressBar->init(620, 340, 110, 20);
	_pStress.progressBar->setGauge(_pStress.data, 500);

	return S_OK;
}

void hospital::update()
{
	if (_dialogType == DIALOG_ING) return;

	switch (_type)
	{
		case HOSPITAL_SICK:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				string str = "「음,이건 진찰료가 이만큼 드는데, 괜찮은가? 진찰료 " + to_string(_sickPer*2) + "G」";
				setDialog(str);
				_type = HOSPITAL_DEMAND;
				_dialogIdx = 0;
				_dialogType = DIALOG_ING;
			}
		 break;
		case HOSPITAL_DEMAND:
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
							if (_princess->getGold() >= _sickPer * 2)
							{
								_chooseNum = 0;
								string str = "「잘 치료됐네, 건강관리 잘하게.」";
								setDialog(str);
								_dialogIdx = 0;
								_dialogType = DIALOG_ING;
								_type = HOSPITAL_CURE;
								_princess->setStress(_sickPer);
							}
							else
							{
								_chooseNum = 1;
								string str = "「돈이 없다면 돌아가게.」";
								setDialog(str);
								_type = HOSPITAL_NOSICK;
								_dialogIdx = 0;
								_dialogType = DIALOG_ING;
							}
						}
						else
						{
							string str = "「이거 이거.그럼 몸조리 잘하도록...」";
							setDialog(str);
							_type = HOSPITAL_NOSICK;
							_dialogIdx = 0;
							_dialogType = DIALOG_ING;
						}
					}
				}
			}
		break;
		case HOSPITAL_NOSICK:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				_fin = true;
		case HOSPITAL_CURE:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				_fin = true;
		 break;
	}
}

void hospital::render()
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
			case HOSPITAL_DEMAND:
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
			case HOSPITAL_CURE:
				IMAGEMANAGER->findImage("progress1Back")->render(DC, 500, 330);
				HBRUSH brush, oldBrush;
				brush = CreateSolidBrush(RGB(111, 17, 17));
				oldBrush = (HBRUSH)SelectObject(DC, brush);
				FillRect(DC, &_pStress.strRc, brush);
				Rectangle(DC, _pStress.strRc.left, _pStress.strRc.top, _pStress.strRc.right, _pStress.strRc.bottom);
				TextOut(DC, _pStress.strRc.left, _pStress.strRc.top + 2, _pStress.str.c_str(), strlen(_pStress.str.c_str()));
				SelectObject(DC, oldBrush);
				DeleteObject(brush);
				brush = CreateSolidBrush(RGB(0, 0, 0));
				oldBrush = (HBRUSH)SelectObject(DC, brush);
				Rectangle(DC, _pStress.dataRc.left, _pStress.dataRc.top, _pStress.dataRc.right, _pStress.dataRc.bottom);
				char str[128];
				sprintf_s(str, "%3d", _pStress.data);
				TextOut(DC, _pStress.dataRc.left + 2, _pStress.dataRc.top + 2, str, strlen(str));
				SelectObject(DC, oldBrush);
				DeleteObject(brush);
				_pStress.progressBar->render();
				break;
		}
	}
}

void hospital::release()
{
}

void hospital::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	_vDialog.push_back("롱바르디니 의사");
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

bool hospital::dialogRender()
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
		if (_type == HOSPITAL_NONE)
		{
			if (_isSick)
				_type = HOSPITAL_SICK;
			else
				_type = HOSPITAL_NOSICK;
		}
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}
