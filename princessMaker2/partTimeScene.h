#pragma once
#include "gameNode.h"
#include"data.h"
#include "workStatus.h"

enum WORK_TYPE { WORK_HOUSE, WORK_NURSERY, WORK_INN, WORK_FARM, WORK_CHURCH, WORK_RESTAURANT, WORK_WOOD, WORK_HAIR, WORK_PLASTERER, WORK_HUNTER, WORK_GRAVE, WORK_COACH, WORK_DRINK, WORK_NIGHT_DRINK, WORK_NIGHT_CLUB };
enum WORK_STATUS { WORK_HARD, WORK_SLEEP, WORK_NOHARD };

class princess;

class partTimeScene : public gameNode
{
private:
	princess* _princess;
	workStatus* _work;
	vector<string> _vDialog;
	DIALOG_TYPE _dialogType;
	int _dialogIdx;
	int _idx;

	int _day, _dayCount, _dayIdx, _printDay;
	int _gold;
	workStatus _curStatus;
	int _startF, _endF, _count, _frameCount, _frameX, _success;
	int _teacherFrameX;
	int _dialogX, _dialogY;

	string _workName;
	vector<string> _teachDialog;
	WORK_TYPE _type;
	WORK_STATUS _status;
	STATUS_TYPE _progress;
	DAYOFWEEK _dayOfWeek;
	vector<pair<string, int>> _workStatus;

	image* _back;
	image* _princessImg;
	vector<image*> _friends;

	bool _fin, _goldOk, _workFin, _workStart;

	tagProgress _pGold;
	vector<pair<image*, tagProgress>> _vPStatus;

public:
	partTimeScene();
	~partTimeScene();

	HRESULT init(workStatus* work, int dayCount, int idx);
	void update();
	void render();
	void release();

	void initStatus();
	void setImage();
	void setTeachDialog();
	void setDialog(string dialog);
	void setResultDialog();

	void changeFrame();
	WORK_STATUS selectStatus();
	int changeStatus(string name, int value);

	bool dialogRender();
	void workRender();

	bool getFin() { return _fin; }
};

