#pragma once
#include "gameNode.h"
#include "data.h"
#include "item.h"

class princess;

class inventoryScene : public gameNode
{
private:
	princess* _princess;

	bool _fin, _noAge, _weaponOk[2];
	vector<tagImg> _vInvenImg;
	vector<item*> _vInven;
	item* _selectItem[2];
	tagImg _chooseBox[2];
	vector<string> _vDialog;
	int _dialogIdx;
	DIALOG_TYPE _dialogType;
	int _weaponFrameX[2], _cubeFrameX;
public:
	inventoryScene();
	~inventoryScene();

	HRESULT init();
	void update();
	void render();
	void release();

	void setItem();

	void setDialog(string dialog);

	void changeStatus(string name, int value);

	bool dialogRender();

	void setFin(bool fin) { _fin = fin; }
	bool getFin() { return _fin; }
	
	bool getWeaponOk(int idx) { return _weaponOk[idx]; }
	int getWeaponFrameX(int idx) { return _weaponFrameX[idx]; }
};

