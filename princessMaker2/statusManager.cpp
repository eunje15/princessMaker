#include "stdafx.h"
#include "statusManager.h"
#include <algorithm>


statusManager::statusManager()
{
}


statusManager::~statusManager()
{
}

HRESULT statusManager::init()
{
	_type = STATUS_DATA_TEACH;
	loadData("dialog/teach.csv");
	_type = STATUS_DATA_WORK;
	loadWorkData("dialog/work.csv");
	_type = STATUS_DATA_FIGHT;
	setFightData();
	_type = STATUS_DATA_RELAX;
	setRelaxData();
	return S_OK;
}

void statusManager::update()
{
}

void statusManager::render()
{
}

void statusManager::release()
{
}

void statusManager::loadData(const char * dataName)
{
	vector<string> vStr = TXTDATA->txtLoadCsv(dataName);
	for (int i = 0; i < vStr.size(); i++)
	{
		char str[100000];
		strcpy(str, vStr[i].c_str());
		vector<string> temp = TXTDATA->charArraySeparation(str);
		status* tStatus = new status;
		vector<tagStatusData> property;
		for (int j = 4; j < temp.size() - 4; j += 5)
		{
			tagStatusData tagData;
			tagData.name = temp[j];
			tagData.startP = atoi(temp[j + 1].c_str());
			tagData.endP = atoi(temp[j + 2].c_str());
			tagData.plusStart = atoi(temp[j + 3].c_str());
			tagData.plusEnd = atoi(temp[j + 4].c_str());
			property.push_back(tagData);
		}

		tStatus->setStatus(temp[0], temp[1], atoi(temp[2].c_str()), atoi(temp[3].c_str()), property, i, 0);
		_vTeach.push_back(tStatus);
	}
}

void statusManager::loadWorkData(const char * dataName)
{
	vector<string> vStr = TXTDATA->txtLoadCsv(dataName);
	
	for (int i = 0; i < vStr.size(); i++)
	{
		char str[100000];
		strcpy(str, vStr[i].c_str());
		vector<string> temp = TXTDATA->charArraySeparation(str);
		workStatus* work = new workStatus;
		work->setInfo(temp[0], temp[1], atoi(temp[2].c_str()), atoi(temp[3].c_str()), atoi(temp[4].c_str()), atoi(temp[5].c_str()), atoi(temp[6].c_str()));
		vector<pair<string, pair<int, int>>> property;
		vector<pair<string, int>> success;
		for (int j = 7; j < temp.size() - 2; j+=3)
		{
			if (temp[j] == "성공")
			{
				success.push_back(make_pair(temp[j + 1], atoi(temp[j + 2].c_str())));
			}
			else
			{
				property.push_back(make_pair(temp[j], make_pair(atoi(temp[j + 1].c_str()), atoi(temp[j + 2].c_str()))));
			}
		}
		work->setVector(property, success, i);
		_vWork.push_back(work);
	}
}

void statusManager::setFightData()
{
	for (int i = 0; i < 4; i++)
	{
		fightStatus* data = new fightStatus;
		string str,str2;
		if (i == 0)
			str = "동부", str2 ="산림지대";
		else if (i == 1)
			str = "서부", str2 = "사막지대";
		else if (i == 2)
			str = "남부", str2 = "폭포지대";
		else
			str = "북부", str2 = "빙산지대";
		data->init(str, str2);
		_vFight.push_back(data);
	}
}

void statusManager::setRelaxData()
{
	for (int i = 0; i < 2; i++)
	{
		relaxStatus* temp = new relaxStatus;
		temp->setRelaxStatus(i);
		_vRelax.push_back(temp);
	}
}