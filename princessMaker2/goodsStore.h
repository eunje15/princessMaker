#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum GOODS_TYPE { GOODS_FIN, GOODS_SELECT, GOODS_CLICK, GOODS_SELL, GOODS_NONE };

class princess;

class goodsStore : public gameNode
{
private:
	princess* _princess;
	vector<item*> _vItem;
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx, _selectNumber;
	GOODS_TYPE _type;
	DIALOG_TYPE _dialogType;
	tagString _chooseBox[3], _buyBox[3];
	tagImg _itemImg[6];
	tagImg _quitImg;
	bool _fin, _selectItem, _isSell;

	vector<tagImg> _vInvenImg;
	vector<item*> _vInven;
public:
	goodsStore();
	~goodsStore();

	HRESULT init(vector<item*> vItem);
	void update();
	void render();
	void release();

	void setItem(vector<item*> vItem);
	void setPrincessItem();
	void setDialog(string dialog);
	bool dialogRender();

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};

