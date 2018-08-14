#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum CLOTHES_TYPE { CLOTHES_FIN, CLOTHES_SELECT, CLOTHES_CLICK, CLOTHES_NONE };

class princess;

class clothesStore : public gameNode
{
private:
	princess* _princess;

	vector<item*> _vItem;
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx;
	CLOTHES_TYPE _type;
	DIALOG_TYPE _dialogType;
	tagString _chooseBox[2], _buyBox[3];
	tagImg _itemImg[6];
	tagImg _quitImg;
	bool _fin, _selectItem;
	int _selectNumber;

public:
	clothesStore();
	~clothesStore();

	HRESULT init(vector<item*> vItem);
	void update();
	void render();
	void release();

	void setItem(vector<item*> vItem);
	void setDialog(string dialog);
	bool dialogRender();

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};

