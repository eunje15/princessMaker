#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum COOK_TYPE { COOK_FIN, COOK_SELECT, COOK_CLICK, COOK_NONE };

class princess;

class cookStore : public gameNode
{
private:
	princess* _princess;
	vector<item*> _vItem;
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx, _selectNumber;
	COOK_TYPE _type;
	DIALOG_TYPE _dialogType;
	tagString _chooseBox[2], _buyBox[3];
	tagImg _itemImg[3];
	tagImg _quitImg;
	bool _fin, _selectItem;

public:
	cookStore();
	~cookStore();

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

