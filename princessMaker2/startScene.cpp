#include "stdafx.h"
#include "startScene.h"
#include "princess.h"

startScene::startScene()
{
}

startScene::~startScene()
{
}

HRESULT startScene::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();

	_type = SAVELOAD_FIN;

	for (int i = 0; i < 2; i++)
	{
		_selectBox[i].rc = RectMake(350, 250 + i * 28, 120, 28);
		_selectBox[i].isSelected = _selectBox[i].isChoose = false;
	}
	_selectBox[0].str = "처음부터 시작";
	_selectBox[1].str = "시간을 되돌린다";


	for (int i = 9; i >= 0; i--)
	{
		_saveLoadInfo[i].img = new image;
		_saveLoadInfo[i].img->init("image/main/saveBack(560x70,1x2).bmp", 460, 70, 1, 2, false, RGB(255, 0, 255));
		_saveLoadInfo[i].data.rc = RectMake(0, WINSIZEY - (i + 1) * 35, 460, 35);
		_saveLoadInfo[i].data.str = to_string(10 - i) + ".";
	}

	setSaveTitle(false, -1);

	_fin = false;

	_dialogIdx = 0, _dialogType = DIALOG_FIN;

	return S_OK;
}

void startScene::update()
{
	if (_dialogType == DIALOG_ING) return;
	switch (_type)
	{
	case SAVELOAD_FIN:
		for (int i = 0; i < 2; i++)
		{
			_selectBox[i].isSelected = false;
			if (PtInRect(&_selectBox[i].rc, _ptMouse))
			{
				_selectBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
					{
						SCENEMANAGER->changeScene("데이터입력");
						_fin = true;
					}
					else
					{
						_type = SAVELOAD_LOAD;
						setDialog("어느 기록으로 시간을 되돌리겠습니까");
						_dialogX = WINSIZEX - 240, _dialogY = WINSIZEY - 120;
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
					}
				}
			}
		}
		break;
	case SAVELOAD_LOAD:
			for (int i = 0; i < 10; i++)
			{
				_saveLoadInfo[i].frameY = 0;
				if (PtInRect(&_saveLoadInfo[i].data.rc, _ptMouse))
				{
					_saveLoadInfo[i].frameY = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						if (!_saveLoadInfo[i].data.isChoose) break;
						loadData(i);
						_type = LOAD_SELECT;
						string str = "왕국력 " + to_string(_princess->getDate().year) + "년 " + to_string(_princess->getDate().mon) + "월 " + to_string(_princess->getDate().day) + "일로 시간을 되돌립니다.";
						setDialog(str);
						_dialogX = 20, _dialogY = WINSIZEY - 120;
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
					}
				}
			}
		break;
	case LOAD_SELECT:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_fin = true;
			SCENEMANAGER->changeScene("공주씬");
		}
		break;
	}
}

void startScene::render()
{
	if (_fin) return;

	IMAGEMANAGER->findImage("black")->render(DC);

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	switch (_type)
	{
	case SAVELOAD_FIN:
		IMAGEMANAGER->findImage("2Back")->render(DC, 340, 235);
		for (int i = 0; i < 2; i++)
		{
			if (_selectBox[i].isSelected)
			{
				HBRUSH brush, oldBrush;
				brush = CreateSolidBrush(RGB(43, 0, 0));
				oldBrush = (HBRUSH)SelectObject(DC, brush);
				FillRect(DC, &_selectBox[i].rc, brush);
				SelectObject(DC, oldBrush);
				DeleteObject(brush);
			}
			TextOut(DC, _selectBox[i].rc.left + 2, _selectBox[i].rc.top + 5, _selectBox[i].str.c_str(), strlen(_selectBox[i].str.c_str()));
		}
		break;
	case SAVELOAD_LOAD:
		IMAGEMANAGER->findImage("info3Back")->render(DC, WINSIZEX - 250, WINSIZEY - 130);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		for (int i = 0; i < 10; i++)
		{
			_saveLoadInfo[i].img->frameRender(DC, _saveLoadInfo[i].data.rc.left, _saveLoadInfo[i].data.rc.top, 0, _saveLoadInfo[i].frameY);
			TextOut(DC, _saveLoadInfo[i].data.rc.left + 10, _saveLoadInfo[i].data.rc.top + 8, _saveLoadInfo[i].data.str.c_str(), strlen(_saveLoadInfo[i].data.str.c_str()));
		}
		break;
	case LOAD_SELECT:
		IMAGEMANAGER->findImage("wideBack")->render(DC, 10, WINSIZEY - 130);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		break;
	}
}

void startScene::release()
{
}

void startScene::loadData(int idx)
{
	HANDLE file;
	DWORD load;

	tagInfo info;
	tagStatus status;
	tagBody bodyInfo;
	tagDate date;
	vector<string> name;
	int vItemSize;
	int season;
	int educationCount[10];
	int workSuccess[15];
	//name.resize(_princess->getVItem().size());

	char str[128];
	sprintf_s(str, "data/princess%d.txt", 9 - idx);

	file = CreateFile(str, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(file, &info, sizeof(tagInfo), &load, NULL);
	ReadFile(file, &status, sizeof(tagStatus), &load, NULL);
	ReadFile(file, &bodyInfo, sizeof(tagBody), &load, NULL);
	ReadFile(file, &date, sizeof(tagDate), &load, NULL);
	ReadFile(file, &season, sizeof(int), &load, NULL);
	ReadFile(file, educationCount, sizeof(int) * 10, &load, NULL);
	ReadFile(file, workSuccess, sizeof(int) * 15, &load, NULL);
	ReadFile(file, &vItemSize, sizeof(int), &load, NULL);
	char str2[100000] = "";

	/*for (int i = 0; i < vItemSize; i++)
	{
	ReadFile(file, &name[i], sizeof(_princess->getVItem()[i]->getName()), &load, NULL);
	}*/

	ReadFile(file, str2, 100000, &load, NULL);

	vector<string> vName = TXTDATA->charArraySeparation(str2);

	_princess->setInfo(info);
	_princess->setStatus(status);
	_princess->setBodyInfo(bodyInfo);
	_princess->setDate(date);
	_princess->setSeason((SEASON_TYPE)season);
	_princess->setEducationCount(educationCount);
	_princess->setWorkSuccess(workSuccess);
	/*for (int i = 0; i < _princess->getVItem().size(); i++)
	{
	_princess->setVItemName(i, name[i]);
	}*/

	_princess->setVItemName(vName);
	_princess->setDataItem(_vTotal);

	ZeroMemory(&info, sizeof(tagInfo));
	ZeroMemory(&status, sizeof(tagStatus));
	ZeroMemory(&bodyInfo, sizeof(tagBody));
	ZeroMemory(&date, sizeof(tagDate));
	name.clear();
	CloseHandle(file);
}

void startScene::setSaveTitle(bool isSave, int idx)
{
	HANDLE file;
	DWORD load;

	int count = 0;
	tagDate* date = NULL;

	file = CreateFile("data/saveTitle.txt", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &count, sizeof(int), &load, NULL);

	if (count != 0)
	{
		date = new tagDate[count];

		for (int i = 0; i < count; i++)
		{
			ReadFile(file, &date[i], sizeof(tagDate), &load, NULL);
		}
	}
	if (count == 48)
		count = 0;
	CloseHandle(file);

	tagDate temp = { idx, _princess->getInfo().name, _princess->getInfo().firstName, _princess->getDate().year, _princess->getDate().mon,_princess->getDate().day, _princess->getDate().dayOfWeek };

	if (isSave)
	{
		bool noData = true;
		for (int i = 0; i < count; i++)
		{
			if (date[i].idx == idx)
			{
				noData = false;
				date[i] = temp;
				break;
			}
		}
		file = CreateFile("data/saveTitle.txt", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (noData)
		{
			count++;
			WriteFile(file, &count, sizeof(int), &load, NULL);
			WriteFile(file, date, sizeof(tagDate)*(count - 1), &load, NULL);
			WriteFile(file, &temp, sizeof(tagDate), &load, NULL);
			count--;
		}
		else
		{
			WriteFile(file, &count, sizeof(int), &load, NULL);
			WriteFile(file, date, sizeof(tagDate)*(count), &load, NULL);
		}
		CloseHandle(file);
	}

	string str = "";

	for (int i = 0; i < count; i++)
	{
		_saveLoadInfo[date[i].idx].data.isChoose = true;
		str = date[i].name + " " + date[i].firstName + " (" + to_string(date[i].year) + "," + to_string(date[i].mon) + "," + to_string(date[i].day) + " )";
		_saveLoadInfo[date[i].idx].data.str += str;
	}
	if (isSave)
	{
		_saveLoadInfo[idx].data.isChoose = true;
		str = temp.name + " " + temp.firstName + " (" + to_string(temp.year) + "," + to_string(temp.mon) + "," + to_string(temp.day) + " )";
		_saveLoadInfo[idx].data.str += str;
	}
}

void startScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 1);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	int stringSize = 29;
	if (_type == LOAD_SELECT) stringSize = 50;
	_vDialog.clear();
	while (1)
	{
		if (strSize > stringSize)
		{
			_vDialog.push_back(str.substr(idx, stringSize));
			idx += stringSize;
			strSize -= stringSize;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

bool startScene::dialogRender()
{
	if (_dialogType != DIALOG_ING) return true;

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
					TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			TextOut(DC, _dialogX, _dialogY + _dialogIdx * 30, temp.c_str(), strlen(temp.c_str()));
		}
	}
	else
	{
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}
