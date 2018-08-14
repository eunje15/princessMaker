#include "stdafx.h"
#include "weaponStore.h"
#include "princess.h"


weaponStore::weaponStore()
{
}


weaponStore::~weaponStore()
{
}

HRESULT weaponStore::init(vector<item*> vWeapon, vector<item*> vArmor)
{
	_princess = SCENEMANAGER->getPrincessAddress();

	setItem(vWeapon, vArmor);
	_npc.img = IMAGEMANAGER->findImage("peopleFace");
	_npc.frameX = 6, _npc.frameY = 1;
	setDialog("「어서오세요. 무기도 방어구도 좋은 것들만 모여 있습니다」");
	_dialogIdx = 0;
	_dialogType = DIALOG_ING;
	_type = WEAPON_NONE;
	_fin = false;

	for (int i = 0; i < 2; i++)
	{
		_chooseBox[i].rc = RectMake(610, 295 + i * 28, 120, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "물건을 산다";
	_chooseBox[1].str = "가게를 나선다";

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_itemImg[i * 4 + j].img = new image;
			_itemImg[i * 4 + j].img->init("image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, true, RGB(255, 0, 255));
			_itemImg[i * 4 + j].data.rc = RectMake(20 + j*190, 521 - i*76, 190, 76);
		}
	}

	for (int i = 8; i < 12; i++)
	{
		_itemImg[i].img = new image;
		_itemImg[i].img->init("image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, true, RGB(255, 0, 255));
		_itemImg[i].data.rc = RectMake(590, 369 - (i - 8) * 76, 190, 76);
	}

	for (int i = 0; i < 12; i++)
	{
		_vItem[i]->setXY(_itemImg[i].data.rc.left + 7, _itemImg[i].data.rc.top + 5);
	}

	_quitImg.data.rc = RectMake(444, 393, 120, 40);
	_quitImg.img = IMAGEMANAGER->findImage("storeQuit");

	_selectItem = false;

	for (int i = 0; i < 3; i++)
	{
		_buyBox[i].rc = RectMake(610, 295 + i * 28, 150, 28);
		_buyBox[i].isSelected = _buyBox[i].isChoose = false;
	}

	_buyBox[0].str = "산다";
	_buyBox[1].str = "그만 둔다";
	_buyBox[2].str = "가게를 나선다";

	return S_OK;
}

void weaponStore::update()
{
	if (_dialogType == DIALOG_ING) return;

	switch (_type)
	{
	case WEAPON_FIN:
		for (int i = 0; i < 2; i++)
		{
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
						_type = WEAPON_SELECT;
					else if (i == 1)
						_fin = true;
				}
			}
		}
		break;
	case WEAPON_SELECT:
		if (!_selectItem)
		{
			for (int i = 0; i < 12; i++)
			{
				_itemImg[i].frameX = 0;
				if (PtInRect(&_itemImg[i].data.rc, _ptMouse))
				{
					_itemImg[i].frameX = 1;
					_itemImg[i].data.isChoose = false;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_selectNumber = i;
						_selectItem = true;
						_itemImg[i].data.isChoose = true;
						_itemImg[i].frameX = 0;
						string str = "「" + _vItem[i]->getName() + "은/는 " + to_string(_vItem[i]->getPrice()) + "G 입니다.」";
						setDialog(str);
						_type = WEAPON_CLICK;
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
					}
				}
			}
		}
		_quitImg.frameX = 0;
		if(PtInRect(&_quitImg.data.rc, _ptMouse))
		{
			_quitImg.frameX = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_fin = true;
			}
		}
		break;
	case WEAPON_CLICK:
		for (int i = 0; i < 3; i++)
		{
			_buyBox[i].isSelected = false;
			if (PtInRect(&_buyBox[i].rc, _ptMouse))
			{
				_buyBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
					{
						if (_princess->getGold() >= _vItem[_selectNumber]->getPrice())
						{
							if (_princess->setItem(_vItem[_selectNumber]))
							{
								_princess->setGold(-_vItem[_selectNumber]->getPrice());
								string str = "「감사합니다.」";
								setDialog(str);
								_type = WEAPON_SELECT;
								_dialogIdx = 0;
								_dialogType = DIALOG_FIN;
								for (int i = 0; i < 12; i++)
								{
									_itemImg[i].data.isChoose = _itemImg[i].data.isSelected = false;
								}
								_selectItem = false;
							}
							else
							{
								string str = "「인벤토리창이 꽉 차서 물건을 구입할 수 없습니다.」";
								setDialog(str);
								_type = WEAPON_NONE;
								_dialogIdx = 0;
								_dialogType = DIALOG_ING;
							}
						}
						else
						{
							string str = "「돈이 없다면 돌아가.」";
							setDialog(str);
							_type = WEAPON_SELECT;
							_selectItem = false;
							_dialogIdx = 0;
							_dialogType = DIALOG_ING;
						}
					}
					else if (i == 1)
					{
						_type = WEAPON_SELECT;
						_selectItem = false;
					}
					else
					{
						_fin = true;
					}
				}
			}
		}
		break;
	case WEAPON_NONE:
		break;
	}
}

void weaponStore::render()
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
		case WEAPON_FIN:
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
		case WEAPON_SELECT:
			for (int i = 0; i < 12; i++)
			{
				if (_selectItem && !_itemImg[i].data.isChoose) continue;
				//Rectangle(DC, _itemImg[i].data.rc.left, _itemImg[i].data.rc.top, _itemImg[i].data.rc.right, _itemImg[i].data.rc.bottom);
				_itemImg[i].img->frameRender(DC, _itemImg[i].data.rc.left, _itemImg[i].data.rc.top,_itemImg[i].frameX, 0);
				_vItem[i]->render();
				TextOut(DC, _vItem[i]->getX() + 45, _vItem[i]->getY() + 5, _vItem[i]->getName().c_str(), strlen(_vItem[i]->getName().c_str()));
				string gold = to_string(_vItem[i]->getPrice()) + "G";
				TextOut(DC, _vItem[i]->getX() + 45, _vItem[i]->getY() + 25, gold.c_str(), strlen(gold.c_str()));

				vector<pair<string, float>> vTemp = _vItem[i]->getProperty();
				for (int j = 0; j < vTemp.size(); j++)
				{
					TextOut(DC, _vItem[i]->getX() + j * 80, _vItem[i]->getY() + 45, vTemp[j].first.c_str(), strlen(vTemp[j].first.c_str()));
					if(vTemp[j].second > 0)
						TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size()*8 + j * 80, _vItem[i]->getY() + 45, "+", strlen("+"));
					char stat[128];
					sprintf_s(stat, "%d", (int)vTemp[j].second);
					TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size() * 8 + 10 + j * 80, _vItem[i]->getY() + 45, stat, strlen(stat));
				}

				_quitImg.img->frameRender(DC, 444, 393, _quitImg.frameX, 0);

				TextOut(DC, _quitImg.data.rc.left + 30, _quitImg.data.rc.top + 10, "관둔다", strlen("관둔다"));
			}
			break;
		case WEAPON_CLICK:
			IMAGEMANAGER->findImage("3Back")->render(DC, 600, 280);
			for (int i = 0; i < 3; i++)
			{
				//Rectangle(DC, _buyBox[i].rc.left, _buyBox[i].rc.top, _buyBox[i].rc.right, _buyBox[i].rc.bottom);
				if (_buyBox[i].isSelected)
				{
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(43, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_buyBox[i].rc, brush);
					SelectObject(DC, oldBrush);
					DeleteObject(brush);
				}
				TextOut(DC, _buyBox[i].rc.left + 10, _buyBox[i].rc.top + 5, _buyBox[i].str.c_str(), strlen(_buyBox[i].str.c_str()));
			}
			break;
		}
	}
}

void weaponStore::release()
{
}

void weaponStore::setItem(vector<item*> vWeapon, vector<item*> vArmor)
{
	for (int i = 0; i < vWeapon.size(); i++)
	{
		if (!vWeapon[i]->getIsStore()) continue;
		_vItem.push_back(vWeapon[i]);
	}
	for (int i = 0; i < vArmor.size(); i++)
	{
		if (!vArmor[i]->getIsStore()) continue;
		_vItem.push_back(vArmor[i]);
	}
}


void weaponStore::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	_vDialog.push_back("무기점의 제노");
	while (1)
	{
		if (strSize > 29)
		{
			_vDialog.push_back(str.substr(idx, 29));
			idx += 29;
			strSize -= 29;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

bool weaponStore::dialogRender()
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
		if(_type == WEAPON_NONE)_type = WEAPON_FIN;
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}