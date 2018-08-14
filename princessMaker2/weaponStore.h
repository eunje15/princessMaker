#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum WEAPON_TYPE { WEAPON_FIN, WEAPON_SELECT, WEAPON_CLICK, WEAPON_NONE };

class princess;

class weaponStore : public gameNode
{
private:
	vector<item*> _vItem;
	
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx, _selectNumber;
	WEAPON_TYPE _type;
	DIALOG_TYPE _dialogType;
	tagString _chooseBox[2], _buyBox[3];
	tagImg _itemImg[12];
	tagImg _quitImg;
	bool _fin, _selectItem;

	princess* _princess;

public:
	weaponStore();
	~weaponStore();

	HRESULT init(vector<item*> vWeapon, vector<item*> vArmor);
	void update();
	void render();
	void release();

	void setItem(vector<item*> vWeapon, vector<item*> vArmor);
	void setDialog(string dialog);
	bool dialogRender();

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};

