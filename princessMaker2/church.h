#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

class princess;

enum CHURCH_TYPE { CHURCH_FIN, CHURCH_SELECT, CHURCH_NO_SELECT, CHURCH_NONE };
class church : public gameNode
{	
private:
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx;
	CHURCH_TYPE _type;
	DIALOG_TYPE _dialogType;
	tagString _chooseBox[2];
	tagProgress _pKarma;
	bool _fin,_haveMoney;
	
	princess* _princess;

public:
	church();
	~church();

	HRESULT init();
	void update();
	void render();
	void release();

	void setDialog(string dialog);
	bool dialogRender();

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};

