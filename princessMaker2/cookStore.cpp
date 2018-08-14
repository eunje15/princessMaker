#include "stdafx.h"
#include "cookStore.h"
#include "princess.h"


cookStore::cookStore()
{
}


cookStore::~cookStore()
{
}

HRESULT cookStore::init(vector<item*> vItem)
{
	_princess = SCENEMANAGER->getPrincessAddress();

	setItem(vItem);
	_npc.img = IMAGEMANAGER->findImage("peopleFace");
	_npc.frameX = 13, _npc.frameY = 0;
	setDialog("「어서와. 맛있는 요리를 먹고 가라고!」");
	_dialogIdx = 0;
	_type = COOK_NONE;
	_dialogType = DIALOG_ING;
	_fin = false;

	for (int i = 0; i < 2; i++)
	{
		_chooseBox[i].rc = RectMake(610, 295 + i * 28, 120, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "물건을 산다";
	_chooseBox[1].str = "가게를 나선다";

	for (int i = 0; i < 3; i++)
		{
			_itemImg[i].img = new image;
			_itemImg[i].img->init("image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, true, RGB(255, 0, 255));
			_itemImg[i].data.rc = RectMake(20 + i * 190, 445, 190, 76);
		}

	for (int i = 0; i < 3; i++)
	{
		_vItem[i]->setXY(_itemImg[i].data.rc.left + 7, _itemImg[i].data.rc.top + 5);
	}

	_quitImg.data.rc = RectMake(600, 445, 120, 40);
	_quitImg.img = IMAGEMANAGER->findImage("storeQuit");

	_selectItem = false;

	for (int i = 0; i < 3; i++)
	{
		_buyBox[i].rc = RectMake(610, 295 + i * 28, 150, 28);
		_buyBox[i].isSelected = _buyBox[i].isChoose = false;
	}

	_buyBox[0].str = "먹는다";
	_buyBox[1].str = "그만 둔다";
	_buyBox[2].str = "가게를 나선다";

	return S_OK;
}

void cookStore::update()
{
	if (_dialogType == DIALOG_ING) return;

	switch (_type)
	{
	case COOK_FIN:
		for (int i = 0; i < 2; i++)
		{
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
						_type = COOK_SELECT;
					else if (i == 1)
						_fin = true;
				}
			}
		}
		break;
	case COOK_SELECT:
		if (!_selectItem)
		{
			for (int i = 0; i < 3; i++)
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
						string str = "「 " + _vItem[i]->getName() + "은/는 " + to_string(_vItem[i]->getPrice()) + "G 입니다.」";
						setDialog(str);
						_type = COOK_CLICK;
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
					}
				}
			}
		}
		_quitImg.frameX = 0;
		if (PtInRect(&_quitImg.data.rc, _ptMouse))
		{
			_quitImg.frameX = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_fin = true;
			}
		}
		break;
	case COOK_CLICK:
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

						}
						else
						{
							string str = "「돈이 없으니 돌아가세요.」";
							setDialog(str);
							_type = COOK_SELECT;
							_selectItem = false;
							_dialogIdx = 0;
							_dialogType = DIALOG_ING;
						}
					}
					else if (i == 1)
					{
						_type = COOK_SELECT;
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
	case COOK_NONE:
		break;
	}
}

void cookStore::render()
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
		case COOK_FIN:
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
		case COOK_SELECT:
			for (int i = 0; i < 3; i++)
			{
				if (_selectItem && !_itemImg[i].data.isChoose) continue;
				//Rectangle(DC, _itemImg[i].data.rc.left, _itemImg[i].data.rc.top, _itemImg[i].data.rc.right, _itemImg[i].data.rc.bottom);
				_itemImg[i].img->frameRender(DC, _itemImg[i].data.rc.left, _itemImg[i].data.rc.top, _itemImg[i].frameX, 0);
				_vItem[i]->render();
				TextOut(DC, _vItem[i]->getX() + 45, _vItem[i]->getY() + 5, _vItem[i]->getName().c_str(), strlen(_vItem[i]->getName().c_str()));
				string gold = to_string(_vItem[i]->getPrice()) + "G";
				TextOut(DC, _vItem[i]->getX() + 45, _vItem[i]->getY() + 25, gold.c_str(), strlen(gold.c_str()));

				vector<pair<string, float>> vTemp = _vItem[i]->getProperty();
				for (int j = 0; j < vTemp.size(); j++)
				{
					TextOut(DC, _vItem[i]->getX() + j * 80, _vItem[i]->getY() + 45, vTemp[j].first.c_str(), strlen(vTemp[j].first.c_str()));
					if (vTemp[j].second > 0)
						TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size() * 8 + j * 80, _vItem[i]->getY() + 45, "+", strlen("+"));
					char stat[128];
					sprintf_s(stat, "%.1f", vTemp[j].second);
					TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size() * 8 + 10 + j * 80, _vItem[i]->getY() + 45, stat, strlen(stat));
				}

				_quitImg.img->frameRender(DC, _quitImg.data.rc.left, _quitImg.data.rc.top, _quitImg.frameX, 0);

				TextOut(DC, _quitImg.data.rc.left + 30, _quitImg.data.rc.top + 10, "관둔다", strlen("관둔다"));
			}
			break;
		case COOK_CLICK:
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

void cookStore::release()
{
}

void cookStore::setItem(vector<item*> vItem)
{
	for (int i = 0; i < vItem.size(); i++)
	{
		if (!vItem[i]->getIsStore()) continue;
		_vItem.push_back(vItem[i]);
	}
}

void cookStore::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	_vDialog.push_back("요리점의 발본");
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

bool cookStore::dialogRender()
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
		if(_type == COOK_NONE) _type = COOK_FIN;
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}
