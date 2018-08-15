#pragma once
#include "gameNode.h"
#include "data.h"

class princess;
class item;

class startScene : public gameNode
{
private:
	enum SAVELOAD_TYPE { SAVELOAD_FIN, SAVELOAD_LOAD, LOAD_SELECT };
private:
	princess* _princess;
	vector<string> _vDialog;
	int _dialogIdx;
	DIALOG_TYPE _dialogType;
	SAVELOAD_TYPE _type;
	tagString _selectBox[2];
	tagImg _saveLoadInfo[10];
	int _selectNum, _dialogX, _dialogY;
	vector<item*> _vTotal;
	bool _fin;
public:
	startScene();
	~startScene();

	HRESULT init();
	void update();
	void render();
	void release();

	void loadData(int idx);

	void setSaveTitle(bool isSave, int idx);

	void setDialog(string dialog);
	bool dialogRender();

	void setVTotalItem(vector<item*> vTotal) { _vTotal = vTotal; }
};

