#pragma once
#include "gameNode.h"
#include "data.h"
#include "relaxStatus.h"

class princess;

class relaxScene : public gameNode
{
private:
	enum RELAX_STATUS { RELAX_SELECT, RELAX_ING, RELAX_OK, RELAX_FAIL, RELAX_FIN, RELAX_NONE };
	enum RELAX_TYPE { RELAX_FREE, RELAX_VACATION };

private:
	princess* _princess;
	relaxStatus* _relax;
	tagRelax _relaxInfo;

	image* _back;
	RELAX_STATUS _status;
	RELAX_TYPE _type;
	DIALOG_TYPE _dialogType;
	vector<string> _vDialog;
	int _day, _dayOfWeek, _dayIdx, _dialogIdx, _dayCount;
	tagImg _yearImg, _monImg, _dayImg, _dayOfWeekImg;
	vector<pair<image*, tagProgress>> _vPStatus;
	tagString _selectBox[2], _clickHome;
	vector<pair<string, float>> _relaxStatus;
	bool _fin, _moneyOk;
	int _princessAnswer, _count;
	int _dialogX, _dialogY, _princessFrameX;
public:
	relaxScene();
	~relaxScene();

	HRESULT init(relaxStatus* relax, int dayCount, int idx);
	void update();
	void render();
	void release();
	void setRelax(int idx);
	void initStatus(int idx);
	float changeStatus(string name, float value);
	void changeDay();
	void setDialog(string dialog);
	bool dialogRender();
	void setFin(bool fin) { _fin = fin; }
	bool getFin() { return _fin; }
};

