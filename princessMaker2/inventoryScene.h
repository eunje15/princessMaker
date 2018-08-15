#pragma once
#include "gameNode.h"
#include "data.h"
#include "item.h"

class princess;

class inventoryScene : public gameNode
{
private:
	princess* _princess;

	bool _fin, _noAge;
	vector<tagImg> _vInvenImg;
	vector<item*> _vInven;
	tagImg _chooseBox[2];
	vector<string> _vDialog;
	int _dialogIdx;
	DIALOG_TYPE _dialogType;
public:
	inventoryScene();
	~inventoryScene();

	HRESULT init();
	void update();
	void render();
	void release();

	void setItem();

	void setDialog(string dialog);

	bool dialogRender();

	void setFin(bool fin) { _fin = fin; }
	bool getFin() { return _fin; }
};

