#pragma once
#include "gameNode.h"
#include "data.h"
#include "item.h"

class princess : public gameNode
{
private:
	tagInfo _info;
	tagStatus _status;
	tagBody _bodyInfo;
	tagImg _face, _body;
	tagDate _date;
	vector<item*> _vInven;
	vector<string> _vItemName;
	SEASON_TYPE _season;
	int* _educationCount;
	int* _workSuccess;

public:
	princess();
	~princess();

	HRESULT init();
	void update();
	void render();
	void release();

	void setStatus();

	void setInfo(tagInfo info){	_info = info; }
	void setStatus(tagStatus status) { _status = status; }
	void setBodyInfo(tagBody bodyInfo) { _bodyInfo = bodyInfo; }
	void setDadName(string dadName) { _info.firstName = dadName; }

	tagInfo getInfo() { return _info; }
	tagInfo* getInfoP() { return &_info; }

	tagStatus getStatus() { return _status; }
	tagStatus* getStatusP() { return &_status; }

	tagBody getBodyInfo() { return _bodyInfo; }
	tagBody* getBodyInfoP() { return &_bodyInfo; }

	tagDate getDate() { return _date; }
	tagDate* getDateP() { return &_date; }

	string getDadName() { return _info.firstName; }

	void setGold(int gold) { _info.gold += gold; }
	int getGold() { return _info.gold; }

	void setSeason(int season) { _season = (SEASON_TYPE)season; }
	SEASON_TYPE getSeason() { return _season; }

	void setDietType(string type) { _info.dietType = type; }
	void setStress(int stress);

	vector<item*> getVItem() { return _vInven; }
	//void setVItemName(int idx, string name) { _vInven[idx]->setName(name); }

	void setVItemName(vector<string> vName) { _vItemName = vName; }
	bool setItem(item* newItem);
	void setDataItem(vector<item*> vTotal);
	void deleteVItem(int idx);

	void changeStatus(string name, float value);

	int getDayOfWeek() { return _date.dayOfWeek; }
	int getDay() { return _date.day; }

	void setDate(tagDate date) { _date = date; }
	void setAge(int age);
	void setYear(int year) { _date.year = year; }
	void setMonth(int mon) { _date.mon = mon; }
	void setDayOfWeek(int dayOfWeek) { _date.dayOfWeek = dayOfWeek; }
	void setDay(int day) { _date.day = day; }
	
	void setEducationCountIdx(int idx) { _educationCount[idx] += 1; }
	void setWorkSuccessIdx(int idx) { _workSuccess[idx] += 1; }
	void setEducationCount(int* education) { _educationCount = education; }
	void setWorkSuccess(int* workSuccess) { _workSuccess = workSuccess; }

	int* getEducationCount() { return _educationCount; }
	int* getWorkSuccess() { return _workSuccess; }
};

