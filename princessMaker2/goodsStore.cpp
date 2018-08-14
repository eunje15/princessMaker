#include "stdafx.h"
#include "goodsStore.h"


goodsStore::goodsStore()
{
}


goodsStore::~goodsStore()
{
}

HRESULT goodsStore::init(vector<item*> vItem)
{
	setItem(vItem);
	_npc.img = IMAGEMANAGER->findImage("peopleFace");
	_npc.frameX = 8, _npc.frameY = 1;
	setDialog("����, �̰��� ��ȭ�� �Դϴ١�");
	_dialogIdx = 0;
	_dialogType = DIALOG_ING;
	_type = GOODS_NONE;
	_fin = false;

	for (int i = 0; i < 3; i++)
	{
		_chooseBox[i].rc = RectMake(610, 295 + i * 28, 150, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "������ ���";
	_chooseBox[1].str = "���� ���� ���� �Ǵ�";
	_chooseBox[2].str = "���Ը� ������";

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((i * 4 + j) > 5) break;

			_itemImg[i * 4 + j].img = new image;
			_itemImg[i * 4 + j].img->init("image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, true, RGB(255, 0, 255));
			_itemImg[i * 4 + j].data.rc = RectMake(20 + j * 190, 445 + i * 76, 190, 76);
		}
	}

	for (int i = 0; i < 6; i++)
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

	_buyBox[0].str = "���";
	_buyBox[1].str = "�׸� �д�";
	_buyBox[2].str = "���Ը� ������";

	return S_OK;
}

void goodsStore::update()
{
	if (_dialogType == DIALOG_ING) return;

	switch (_type)
	{
	case GOODS_FIN:
		for (int i = 0; i < 3; i++)
		{
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
						_type = GOODS_SELECT;
					else if (i == 1)
					{
						//�÷��̾� �κ��丮�� �ؾ���!
					}
					else if (i == 2)
						_fin = true;
				}
			}
		}
		break;
	case GOODS_SELECT:
		if (!_selectItem)
		{
			for (int i = 0; i < 6; i++)
			{
				_itemImg[i].frameX = 0;
				if (PtInRect(&_itemImg[i].data.rc, _ptMouse))
				{
					_itemImg[i].frameX = 1;
					_itemImg[i].data.isChoose = false;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_selectItem = true;
						_itemImg[i].data.isChoose = true;
						_itemImg[i].frameX = 0;
						string str = "��" + _vItem[i]->getName() + "��/�� " + to_string(_vItem[i]->getPrice()) + "G �Դϴ�.��";
						setDialog(str);
						_type = GOODS_CLICK;
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
	case GOODS_CLICK:
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
						//�÷��̾�� �������Ѿ���~
					}
					else if (i == 1)
					{
						_type = GOODS_SELECT;
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
	}
}

void goodsStore::render()
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
		case GOODS_FIN:
			IMAGEMANAGER->findImage("3Back")->render(DC, 600, 280);
			for (int i = 0; i < 3; i++)
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
		case GOODS_SELECT:
			for (int i = 0; i < 6; i++)
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
					if (vTemp[j].first == "HPȸ��" || vTemp[j].first == "���ݿ�") continue;
					if (vTemp[j].second > 0)
						TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size() * 8 + j * 80, _vItem[i]->getY() + 45, "+", strlen("+"));
					char stat[128];
					sprintf_s(stat, "%d", (int)vTemp[j].second);
					TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size() * 8 + 10 + j * 80, _vItem[i]->getY() + 45, stat, strlen(stat));
				}

				_quitImg.img->frameRender(DC, 444, 393, _quitImg.frameX, 0);

				TextOut(DC, _quitImg.data.rc.left + 30, _quitImg.data.rc.top + 10, "���д�", strlen("���д�"));
			}
			break;
		case GOODS_CLICK:
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

void goodsStore::release()
{
}

void goodsStore::setItem(vector<item*> vItem)
{
	for (int i = 0; i < vItem.size(); i++)
	{
		if (!vItem[i]->getIsStore()) continue;
		_vItem.push_back(vItem[i]);
	}
}

void goodsStore::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	_vDialog.push_back("��ȭ�� ����");
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

bool goodsStore::dialogRender()
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
		if(_type == GOODS_NONE) _type = GOODS_FIN;
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}
