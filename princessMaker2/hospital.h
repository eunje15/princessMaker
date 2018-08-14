#pragma once
#include "gameNode.h"
#include "data.h"

class princess;

enum HOSPITAL_TYPE { HOSPITAL_SICK, HOSPITAL_DEMAND, HOSPITAL_CURE, HOSPITAL_NOSICK, HOSPITAL_NONE  };


class hospital : public gameNode
{
private:
	princess* _princess;

	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx;
	HOSPITAL_TYPE _type;
	DIALOG_TYPE _dialogType;
	tagString _chooseBox[2];
	bool _fin, _isSick, _chooseNum;
	int _sickPer;
	tagProgress _pStress;
public:
	hospital();
	~hospital();

	HRESULT init();
	void update();
	void render();
	void release();

	void setDialog(string dialog);
	bool dialogRender();

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};

