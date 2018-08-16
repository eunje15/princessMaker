#pragma once
#include "gameNode.h"
#include "data.h"
#include "statusManager.h"
#include "educationScene.h"
#include "partTimeScene.h"
#include "relaxScene.h"

enum SCHEDULE_TYPE { SCHEDULE_NONE, SCHEDULE_TEACH, SCHEDULE_WORK, SCHEDULE_FIGHT, SCHEDULE_RELAX, SCHEDULE_OK, SCHEDULE_GO };
enum SCHEDULE_PROGRESS { SCHEDULE_START, SCHEDULE_ING, SCHEDULE_FIN };

class princess;

class scheduleScene : public gameNode
{
private:
	princess * _princess;
	bool _fin, _select, _scheduleStart;
	int _year, _mon, _gold;
	SCHEDULE_TYPE _type;
	SCHEDULE_PROGRESS _progress;
	DIALOG_TYPE _dialogType;
	tagImg _calImg[42];
	tagImg _teachImg[10], _workImg[15], _fightImg[4], _relaxImg[2];
	vector<string> _vDialog;
	tagString _chooseBox[4], _selectBox[2];
	string _scheduleWeek[4];
	int _itemIdx[4];

	int _dialogIdx, _scheduleIdx, _selectNum, _startDay, _countDay;

	statusManager* _sm;
	educationScene* _education;
	partTimeScene* _work;
	relaxScene* _relax;

	string _curSound;

public:
	scheduleScene();
	~scheduleScene();

	HRESULT init(int year, int mon, string curSound);
	void update();
	void render();
	void release();

	void setSchedule();

	void setDialog(string dialog);

	void setScheduleImage();

	bool dialogRender();

	bool getFin() { return _fin; }

	int getProgess() { return (int)_progress; }
	void setProgess(int idx) { _progress = (SCHEDULE_PROGRESS)idx; }

	void setStatusManagerAddressLink(statusManager* sm) { _sm = sm; }
};

