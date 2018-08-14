#pragma once
#include "gameNode.h"
#include "status.h"
#include "data.h"

enum EDU_TYPE { EDU_SCHOOL, EDU_POETRY, EDU_THEOLOGY, EDU_STRATEGY, EDU_SWORDS, EDU_FIGHTING, EDU_MAGIC, EDU_SCIENCE, EDU_BALLET, EDU_ART };
enum EDU_STATUS { EDU_STUDY, EDU_SLEEP, EDU_NOSTUDY };

class princess;

class educationScene : public gameNode
{
private:
	princess * _princess;
	status* _education;
	vector<string> _vDialog;
	DIALOG_TYPE _dialogType;
	int _idx;
	int _dialogIdx;

	int _day, _dayCount, _dayIdx, _printDay;
	int _gold;
	int _startF, _endF, _count, _frameCount, _frameX, _success;
	int _teacherFrameX;
	int _dialogX, _dialogY;

	string _eduName;
	vector<string> _teachDialog;
	EDU_TYPE _type;
	EDU_STATUS _status;
	STATUS_TYPE _statusProgress;
	DAYOFWEEK _dayOfWeek;
	vector<pair<string, int>> _eduStatus;

	image* _back;
	image* _princessImg;
	vector<image*> _friends;

	bool _fin, _goldOk, _eduFin, _noGold, _resultDialog;

	tagProgress _pGold;
	vector<pair<image*, tagProgress>> _vPStatus;

public:
	educationScene();
	~educationScene();

	HRESULT init(status* education, int dayCount, int idx);
	void update();
	void render();
	void release();

	void initStatus();
	void setImage();
	void setTeachDialog();
	void setDialog(string dialog);
	void setResultDialog();

	void changeFrame();
	EDU_STATUS selectStatus();
	int changeStatus(string name, int value);

	bool dialogRender();
	void eduRender();

	bool getFin() { return _fin; }
};

