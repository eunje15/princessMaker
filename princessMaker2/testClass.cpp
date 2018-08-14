#include "stdafx.h"
#include "testClass.h"


testClass::testClass()
{
}


testClass::~testClass()
{
}

HRESULT testClass::init()
{
	vector<string> vStr = TXTDATA->txtLoad("dialog/workStart.txt");
	vStr = TXTDATA->txtLoadCsv("dialog/workTeach.csv");
	char cStr[100000];
	strcpy(cStr, vStr[(int)7].c_str());
	_teachDialog = TXTDATA->charArraySeparation(cStr);
	_nextIdx = 1;
	setDialog(_teachDialog[_nextIdx]);
	return S_OK;
}

void testClass::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_nextIdx++;
		if (_nextIdx > 0 && _nextIdx < _teachDialog.size())
		{
			setDialog(_teachDialog[_nextIdx]);
			_dialogIdx = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_nextIdx--;
		if (_nextIdx > 0 && _nextIdx < _teachDialog.size())
		{
			setDialog(_teachDialog[_nextIdx]);
			_dialogIdx = 0;
		}
	}
}

void testClass::render()
{
	IMAGEMANAGER->findImage("dialogFrame")->render(DC, 180, 225);
	for (int i = 0; i < _vDialog.size(); i++)
	{
		TextOut(DC, 190, 235 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
	}
}

void testClass::release()
{
}

void testClass::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	if (_vDialog.size() > 0)
		_vDialog.clear();
	int strLength = 28;
	while (1)
	{
		if (strSize > strLength)
		{
			_vDialog.push_back(str.substr(idx, strLength));
			idx += strLength;
			strSize -= strLength;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 1);
}

bool testClass::dialogRender()
{
	if (_dialogIdx < _vDialog.size())
	{
		string temp = DIALOG->getCurrentDialog();
		if (temp == "end")
		{
			_dialogIdx++;
			if (_dialogIdx < _vDialog.size())
				DIALOG->setDialog(_vDialog[_dialogIdx], 5);
		}
		else
		{
			if (_dialogIdx > 0)
			{
				for (int i = 0; i < _dialogIdx; i++)
				{
					TextOut(DC, 190, 235 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			TextOut(DC, 190, 235 + _dialogIdx * 30, temp.c_str(), strlen(temp.c_str()));
		}
	}
	else
	{
		return true;
	}
	return false;
}