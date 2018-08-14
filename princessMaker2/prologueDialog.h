#pragma once
#include "gameNode.h"
#include "princess.h"


enum PRO_DIALOG_TYPE { PRO_DIALOG_DEVIL, PRO_DIALOG_KING, PRO_DIALOG_GOD, PRO_DIALOG_NONE };
enum PRO_DIALOG_PROGRESS { PRO_DIALOG_START, PRO_DIALOG_ING, PRO_DIALOG_FIN, PRO_FRAME_START, PRO_FRAME_FIN };
class prologueDialog :	public gameNode
{
private:
	enum SCENE_TYPE { SCENE_PROLOGUE, SCENE_WAR, SCENE_PRINCESS };

private:
	princess* _princess;

	float _loop;
	SCENE_TYPE _scene;
	PRO_DIALOG_TYPE _whoDialog;
	PRO_DIALOG_PROGRESS _progress;

	int _frameY, _count, _strCount;
	bool _isRender;
	vector<string> _vDialog;

	string _printDialog[2];
	bool _isAlpha;
	int _alpha, _alpha2;
	string _godPlanet,_godName, _dadName;
	int _godIndex;

public:
	prologueDialog();
	~prologueDialog();

	HRESULT init();
	void update();
	void render();
	void release();

	void changeMode();
	void changePrintDialog();

	void setGodPhoto();
	void setWar();
	void setDialog();

	void prologueRender();
	void warRender();
	void dialogRender();

	void setDadName(string dadName) { _dadName = dadName; }
};

