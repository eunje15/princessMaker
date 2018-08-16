#include "stdafx.h"
#include "goodsStore.h"
#include "princess.h"


goodsStore::goodsStore()
{
}


goodsStore::~goodsStore()
{
}

HRESULT goodsStore::init(vector<item*> vItem)
{
	_princess = SCENEMANAGER->getPrincessAddress();

	setItem(vItem);
	_npc.img = IMAGEMANAGER->findImage("peopleFace");
	_npc.frameX = 8, _npc.frameY = 1;
	setDialog("「예, 이곳은 잡화점 입니다」");
	_dialogIdx = 0;
	_dialogType = DIALOG_ING;
	_type = GOODS_FIN;
	_fin = _isSell = false;

	for (int i = 0; i < 3; i++)
	{
		_chooseBox[i].rc = RectMake(610, 295 + i * 28, 150, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "물건을 산다";
	_chooseBox[1].str = "쓸모 없는 것을 판다";
	_chooseBox[2].str = "가게를 나선다";

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

	_buyBox[0].str = "산다";
	_buyBox[1].str = "그만 둔다";
	_buyBox[2].str = "가게를 나선다";

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
					{
						_type = GOODS_SELECT;
						_isSell = false;
					}
					else if (i == 1)
					{
						setPrincessItem();
						_type = GOODS_SELL;
						_isSell = true;
						//플레이어 인벤토리를 해야해!
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
						_selectNumber = i;
						_itemImg[i].data.isChoose = true;
						_itemImg[i].frameX = 0;
						string str = "「" + _vItem[i]->getName() + "은/는 " + to_string(_vItem[i]->getPrice()) + "G 입니다.」";
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
	case GOODS_SELL:
		if (!_selectItem)
		{
			for (int i = 0; i < _vInvenImg.size(); i++)
			{
				_vInvenImg[i].frameX = 0;
				if (PtInRect(&_vInvenImg[i].data.rc, _ptMouse))
				{
					_vInvenImg[i].frameX = 1;
					_vInvenImg[i].data.isChoose = false;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_selectItem = true;
						_selectNumber = i;
						_vInvenImg[i].data.isChoose = true;
						_vInvenImg[i].frameX = 0;
						string str = "「그거라면 이 가격에 사주지.」";
						str += _vInven[i]->getName() + "의 판매 가격 " + to_string(_vInven[i]->getPrice() / 2) + "G";
						setDialog(str);
						_type = GOODS_CLICK;
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
						_buyBox[0].str = "판다";
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
						if (!_isSell)
						{
							if (_princess->getGold() >= _vItem[_selectNumber]->getPrice())
							{
								if (_princess->setItem(_vItem[_selectNumber]))
								{
									_princess->setGold(-_vItem[_selectNumber]->getPrice());
									string str = "「감사합니다.」";
									setDialog(str);
									_type = GOODS_SELECT;
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
									_type = GOODS_NONE;
									_dialogIdx = 0;
									_dialogType = DIALOG_ING;
								}
							}
							else
							{
								string str = "「돈이 없다면 돌아가.」";
								setDialog(str);
								_type = GOODS_SELECT;
								_selectItem = false;
								_dialogIdx = 0;
								_dialogType = DIALOG_ING;
							}
						}
						else
						{
							string str = "「예. 감사합니다.」";
							_princess->setGold(_vInven[_selectNumber]->getPrice() / 2);
							_princess->deleteVItem(_selectNumber);
							setPrincessItem();
							setDialog(str);
							_type = GOODS_SELL;
							_dialogIdx = 0;
							_dialogType = DIALOG_FIN;
							for (int i = 0; i < _vInvenImg.size(); i++)
							{
								_vInvenImg[i].data.isChoose = _vInvenImg[i].data.isSelected = false;
							}
							_selectItem = false;
						}

					}
					else if (i == 1)
					{
						_selectItem = false;
						if (!_isSell)
						{
							setDialog("허허. 안사신다니.");
							_type = GOODS_SELECT;
						}
						else
						{
							setDialog("안파시나요?");
							_type = GOODS_SELL;
						}
						_dialogIdx = 0;
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
	
		switch (_type)
		{
		case GOODS_FIN:
			if (dialogRender())
			{
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
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
			}
			break;
		case GOODS_SELECT:
			if (dialogRender())
			{
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
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
						if (vTemp[j].first == "HP회복" || vTemp[j].first == "공격용") continue;
						if (vTemp[j].second > 0)
							TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size() * 8 + j * 80, _vItem[i]->getY() + 45, "+", strlen("+"));
						char stat[128];
						sprintf_s(stat, "%d", (int)vTemp[j].second);
						TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size() * 8 + 10 + j * 80, _vItem[i]->getY() + 45, stat, strlen(stat));
					}

					if (!_selectItem)
					{
						_quitImg.img->frameRender(DC, 444, 393, _quitImg.frameX, 0);

						TextOut(DC, _quitImg.data.rc.left + 30, _quitImg.data.rc.top + 10, "관둔다", strlen("관둔다"));
					}
				}
			}
			break;
		case GOODS_SELL:
			if (dialogRender())
			{
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
				for (int i = 0; i < _vInvenImg.size(); i++)
				{
					if (_selectItem && !_vInvenImg[i].data.isChoose) continue;

					_vInvenImg[i].img->frameRender(DC, _vInvenImg[i].data.rc.left, _vInvenImg[i].data.rc.top, _vInvenImg[i].frameX, 0);
					_vInven[i]->render();
					TextOut(DC, _vInven[i]->getX() + 45, _vInven[i]->getY() + 5, _vInven[i]->getName().c_str(), strlen(_vInven[i]->getName().c_str()));
					string gold = to_string(_vInven[i]->getPrice()) + "G";
					TextOut(DC, _vInven[i]->getX() + 45, _vInven[i]->getY() + 25, gold.c_str(), strlen(gold.c_str()));

					vector<pair<string, float>> vTemp = _vInven[i]->getProperty();
					for (int j = 0; j < vTemp.size(); j++)
					{
						if (vTemp[j].first == "나이" || vTemp[j].first == "비만") continue;
						TextOut(DC, _vInven[i]->getX() + j * 80, _vInven[i]->getY() + 45, vTemp[j].first.c_str(), strlen(vTemp[j].first.c_str()));
						if (vTemp[j].second > 0)
							TextOut(DC, _vInven[i]->getX() + vTemp[j].first.size() * 8 + j * 80, _vInven[i]->getY() + 45, "+", strlen("+"));
						char stat[128];
						sprintf_s(stat, "%d ", (int)vTemp[j].second);
						TextOut(DC, _vInven[i]->getX() + vTemp[j].first.size() * 8 + 10 + j * 80, _vInven[i]->getY() + 45, stat, strlen(stat));
					}
				}

				if (!_selectItem)
				{
					_quitImg.img->frameRender(DC, 444, 393, _quitImg.frameX, 0);

					TextOut(DC, _quitImg.data.rc.left + 30, _quitImg.data.rc.top + 10, "관둔다", strlen("관둔다"));
				}
			}
			break;
		case GOODS_CLICK:
			if (!_isSell)
			{
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
						if (vTemp[j].first == "HP회복" || vTemp[j].first == "공격용") continue;
						if (vTemp[j].second > 0)
							TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size() * 8 + j * 80, _vItem[i]->getY() + 45, "+", strlen("+"));
						char stat[128];
						sprintf_s(stat, "%d", (int)vTemp[j].second);
						TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size() * 8 + 10 + j * 80, _vItem[i]->getY() + 45, stat, strlen(stat));
					}
				}
			}
			else
			{
				for (int i = 0; i < _vInvenImg.size(); i++)
				{
					if (_selectItem && !_vInvenImg[i].data.isChoose) continue;

					_vInvenImg[i].img->frameRender(DC, _vInvenImg[i].data.rc.left, _vInvenImg[i].data.rc.top, _vInvenImg[i].frameX, 0);
					_vInven[i]->render();
					TextOut(DC, _vInven[i]->getX() + 45, _vInven[i]->getY() + 5, _vInven[i]->getName().c_str(), strlen(_vInven[i]->getName().c_str()));
					string gold = to_string(_vInven[i]->getPrice()) + "G";
					TextOut(DC, _vInven[i]->getX() + 45, _vInven[i]->getY() + 25, gold.c_str(), strlen(gold.c_str()));

					vector<pair<string, float>> vTemp = _vInven[i]->getProperty();
					for (int j = 0; j < vTemp.size(); j++)
					{
						if (vTemp[j].first == "나이" || vTemp[j].first == "비만") continue;
						TextOut(DC, _vInven[i]->getX() + j * 80, _vInven[i]->getY() + 45, vTemp[j].first.c_str(), strlen(vTemp[j].first.c_str()));
						if (vTemp[j].second > 0)
							TextOut(DC, _vInven[i]->getX() + vTemp[j].first.size() * 8 + j * 80, _vInven[i]->getY() + 45, "+", strlen("+"));
						char stat[128];
						sprintf_s(stat, "%d ", (int)vTemp[j].second);
						TextOut(DC, _vInven[i]->getX() + vTemp[j].first.size() * 8 + 10 + j * 80, _vInven[i]->getY() + 45, stat, strlen(stat));
					}
				}
			}
			if (dialogRender())
			{
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
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

void goodsStore::setPrincessItem()
{
	_vInven = _princess->getVItem();
	_vInvenImg.resize(_vInven.size());

	for (int i = 0; i < _vInven.size(); i++)
	{
		_vInvenImg[i].img = new image;
		_vInvenImg[i].img->init("image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, true, RGB(255, 0, 255));
		if ((i % 12) < 8)
			_vInvenImg[i].data.rc = RectMake(20 + (i % 4) * 190, 450 + (i / 4) * 76, 190, 76);
		else
			_vInvenImg[i].data.rc = RectMake(590, 374 - ((i % 8) - 8) * 76, 190, 76);
	}

	for (int i = 0; i < _vInven.size(); i++)
	{
		_vInven[i]->setXY(_vInvenImg[i].data.rc.left + 7, _vInvenImg[i].data.rc.top + 5);
	}
}

void goodsStore::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	_vDialog.push_back("잡화점 샤롬");
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
