#pragma once
#include "gameNode.h"
#include "data.h"

enum PROLOGUE_MODE { PROLOGUE_DADNAME, PROLOGUE_DADCAL, PROLOGUE_DADAGE, PROLOGUE_NAME, PROLOGUE_CAL, PROLOGUE_BLOOD };

class princess;

class dataInput :public gameNode
{
private:
	princess* _princess;
	tagInfo _princessInfo;
	tagStatus _princessStatus;

	image* _back;
	tagObj _okBtn;
	tagObj _backBtn;

	PROLOGUE_MODE _mode;

	string _dadName;
	string _princessName;

	tagObj _cal[12][42];
	image* _img;
	
	tagObj _dadAgeArr[10];
	list<int> _lDadAge;
	list<int>::iterator _lDadAgeIter;
	int	_dadAge, _dadYear;

	tagObj _blood[4];

	int _count;
public:
	dataInput();
	~dataInput();

	HRESULT init();
	void update();
	void render();
	void release();

	void changeMode();
	void setDadName();
	void setPrincessName();
	void setCal();
	void setStatus();
	void clickCal();
	void setDadAge();
	void setDadCal();
	void setBlood();

	void dadNameRender();
	void princessNameRender();
	void dadAgeRender();
	void CalRender();
	void checkRender();
	void dadCalRender();
	void bloodRender();
};

