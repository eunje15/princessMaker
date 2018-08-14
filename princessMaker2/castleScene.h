#pragma once
#include "gameNode.h"
#include "data.h"

class princess;

enum CASTLE_TYPE { CASTLE_FIN, CASTLE_SELECT, CASTLE_DOORKEEPER, CASTLE_NONE };
class castleScene : public gameNode
{
private:
	princess * _princess;

	DIALOG_TYPE _dialogType;
	CASTLE_TYPE _type;
	tagImg _npc;
	vector<string> _vDialog;
	int _dialogIdx;
	bool _fin, _canMeet;
	tagString _chooseBox[2];
	int _doorKeeperIdx;
public:
	castleScene();
	~castleScene();

	HRESULT init();
	void update();
	void render();
	void release();

	void setDialog(string dialog);
	bool dialogRender();

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }

	void setCanMeet(bool canMeet) { _canMeet = canMeet; }
};

