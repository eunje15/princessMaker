#include "stdafx.h"
#include "saveLoadScene.h"
#include "princess.h"
#include "item.h"

saveLoadScene::saveLoadScene()
{
}


saveLoadScene::~saveLoadScene()
{
}

HRESULT saveLoadScene::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();

	setGodPhoto();
	_npc.img = IMAGEMANAGER->findImage("godFace");
	setDialog("수호성에게 기도한다");
	_dialogIdx = 0;
	_dialogType = DIALOG_FIN;
	_type = SAVELOAD_FIN;
	_fin = false;
	_selectNum = -1;

	for (int i = 0; i < 3; i++)
	{
		_chooseBox[i].rc = RectMake(610, 295 + i * 28, 120, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "시간을 기록한다";
	_chooseBox[1].str = "시간을 되돌린다";
	_chooseBox[2].str = "잠시동안의 이별";

	for (int i = 0; i < 2; i++)
	{
		_selectBox[i].rc = RectMake(490, 314 + i * 28, 120, 28);
		_selectBox[i].isSelected = _selectBox[i].isChoose = false;
	}
	_selectBox[0].str = "시간을 기록한다";
	_selectBox[1].str = "취소";


	for (int i = 9; i >= 0; i--)
	{
		_saveLoadInfo[i].img = new image;
		_saveLoadInfo[i].img->init("image/main/saveBack(560x70,1x2).bmp", 460, 70, 1, 2, false, RGB(255, 0, 255));
		_saveLoadInfo[i].data.rc = RectMake(0, WINSIZEY - (i + 1)* 35, 460, 35);
		_saveLoadInfo[i].data.str = to_string(10 - i) + ".";
	}

	setSaveTitle(false, -1);

	return S_OK;
}

void saveLoadScene::update()
{
	switch (_type)
	{
	case SAVELOAD_FIN:
		for (int i = 0; i < 3; i++)
		{
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_selectNum = -1;
					if (i == 0)
					{
						_type = SAVELOAD_SAVE;
						_selectBox[0].str = "시간을 기록한다";
					}
					else if (i == 1)
					{
						_type = SAVELOAD_LOAD;
						_selectBox[0].str = "시간을 되돌린다";
					}
					else
						PostMessage(_hWnd, WM_DESTROY, 0, 0);
				}
			}
		}
		break;
	case SAVELOAD_SAVE:
		if (_selectNum == -1)
		{
			for (int i = 0; i < 10; i++)
			{
				_saveLoadInfo[i].frameY = 0;
				if (PtInRect(&_saveLoadInfo[i].data.rc, _ptMouse))
				{
					_saveLoadInfo[i].frameY = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_selectNum = i;
					}
				}
			}
		}
		else if (_selectNum == 99)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				_fin = true;
		}
		else
		{
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
							saveData(_selectNum);
							setSaveTitle(true, _selectNum);
							_selectNum = 99;
						}
						else
							_selectNum = -1;
					}
				}
			}
		}
		break; 
	case SAVELOAD_LOAD:
		if (_selectNum == -1)
		{
			for (int i = 0; i < 10; i++)
			{
				_saveLoadInfo[i].frameY = 0;
				if (PtInRect(&_saveLoadInfo[i].data.rc, _ptMouse))
				{
					_saveLoadInfo[i].frameY = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						if (!_saveLoadInfo[i].data.isChoose) break;
						/*loadData(i);
						_fin = true;*/
						_selectNum = i;
					}
				}
			}
		}
		else if (_selectNum == 99)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				_fin = true;
		}
		else
		{
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
							loadData(_selectNum);
							_selectNum = 99;
						}
						else
							_selectNum = -1;
					}
				}
			}
		}
			break;
	case SAVELOAD_NONE:
		break;
	}
}

void saveLoadScene::render()
{
	if (dialogRender())
	{
		
		switch (_type)
		{
		case SAVELOAD_FIN:
			IMAGEMANAGER->findImage("wideBack")->render(DC, 40, 460);
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, 50, 470 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
			IMAGEMANAGER->findImage("3Back")->render(DC,590,280);
			for (int i = 0; i < 3; i++)
			{
				if (_chooseBox[i].isSelected)
				{
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(43, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_chooseBox[i].rc, brush);
					SelectObject(DC, oldBrush);
					DeleteObject(brush);
				}
				TextOut(DC, _chooseBox[i].rc.left + 2, _chooseBox[i].rc.top + 5, _chooseBox[i].str.c_str(), strlen(_chooseBox[i].str.c_str()));
			}
			break;
		case SAVELOAD_SAVE:
			IMAGEMANAGER->findImage("frame")->render(DC, WINSIZEX - 150, _saveLoadInfo[9].data.rc.top);
			_npc.img->frameRender(DC, WINSIZEX - 140, _saveLoadInfo[9].data.rc.top + 10, _npc.frameX, 0);
			IMAGEMANAGER->findImage("info2Back")->render(DC, 540, 410);
			
			if (_selectNum == -1)
			{
				TextOut(DC, 550, 420, "원하는 기록장소를 택해라", strlen("원하는 기록장소를 택해라"));
				for (int i = 0; i < 10; i++)
				{
					_saveLoadInfo[i].img->frameRender(DC, _saveLoadInfo[i].data.rc.left, _saveLoadInfo[i].data.rc.top, 0, _saveLoadInfo[i].frameY);
					TextOut(DC, _saveLoadInfo[i].data.rc.left + 10, _saveLoadInfo[i].data.rc.top + 8, _saveLoadInfo[i].data.str.c_str(), strlen(_saveLoadInfo[i].data.str.c_str()));
				}
			}
			else if (_selectNum == 99)
			{
				TextOut(DC, 550, 420, "확실히 기록되었다", strlen("확실히 기록되었다"));
			}
			else
			{
				TextOut(DC, 550, 420, "원하는 기록장소를 택해라", strlen("원하는 기록장소를 택해라"));
				_saveLoadInfo[_selectNum].img->frameRender(DC, _saveLoadInfo[_selectNum].data.rc.left, _saveLoadInfo[_selectNum].data.rc.top, 0, _saveLoadInfo[_selectNum].frameY);
				TextOut(DC, _saveLoadInfo[_selectNum].data.rc.left + 10, _saveLoadInfo[_selectNum].data.rc.top + 8, _saveLoadInfo[_selectNum].data.str.c_str(), strlen(_saveLoadInfo[_selectNum].data.str.c_str()));

				IMAGEMANAGER->findImage("2Back")->render(DC, 485, 300);
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
			}
			break;
		case SAVELOAD_LOAD:
			IMAGEMANAGER->findImage("frame")->render(DC, WINSIZEX - 150, _saveLoadInfo[9].data.rc.top);
			_npc.img->frameRender(DC, WINSIZEX - 140, _saveLoadInfo[9].data.rc.top + 10, _npc.frameX, 0);
			IMAGEMANAGER->findImage("info2Back")->render(DC, 540, 410);

			if (_selectNum == -1)
			{
				TextOut(DC, 550, 420, "언제로 돌아갈 것인가", strlen("언제로 돌아갈 것인가"));
				for (int i = 0; i < 10; i++)
				{
					_saveLoadInfo[i].img->frameRender(DC, _saveLoadInfo[i].data.rc.left, _saveLoadInfo[i].data.rc.top, 0, _saveLoadInfo[i].frameY);
					TextOut(DC, _saveLoadInfo[i].data.rc.left + 10, _saveLoadInfo[i].data.rc.top + 8, _saveLoadInfo[i].data.str.c_str(), strlen(_saveLoadInfo[i].data.str.c_str()));
				}
			}
			else if (_selectNum == 99)
			{
				TextOut(DC, 550, 420, "확실히 되돌렸다", strlen("확실히 되돌렸다"));
			}
			else
			{
				TextOut(DC, 550, 420, "언제로 돌아갈 것인가", strlen("언제로 돌아갈 것인가"));
				_saveLoadInfo[_selectNum].img->frameRender(DC, _saveLoadInfo[_selectNum].data.rc.left, _saveLoadInfo[_selectNum].data.rc.top, 0, _saveLoadInfo[_selectNum].frameY);
				TextOut(DC, _saveLoadInfo[_selectNum].data.rc.left + 10, _saveLoadInfo[_selectNum].data.rc.top + 8, _saveLoadInfo[_selectNum].data.str.c_str(), strlen(_saveLoadInfo[_selectNum].data.str.c_str()));

				IMAGEMANAGER->findImage("2Back")->render(DC, 485, 300);
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
			}
			break;
		case SAVELOAD_NONE:
			break;
		}
	}
}

void saveLoadScene::release()
{
}

void saveLoadScene::saveData(int idx)
{
	HANDLE file;
	DWORD save;

	int season = (int)_princess->getSeason();
	char str[128];
	sprintf_s(str, "data/princess%d.txt", 9 - idx);

	file = CreateFile(str, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &_princess->getInfo(), sizeof(tagInfo), &save, NULL);
	WriteFile(file, &_princess->getStatus(), sizeof(tagStatus), &save, NULL);
	WriteFile(file, &_princess->getBodyInfo(), sizeof(tagBody), &save, NULL);
	WriteFile(file, &_princess->getDate(), sizeof(tagDate), &save, NULL);
	WriteFile(file, &season, sizeof(int), &save, NULL);
	WriteFile(file, _princess->getEducationCount(), sizeof(int)*10, &save, NULL);
	WriteFile(file, _princess->getWorkSuccess(), sizeof(int) * 15, &save, NULL);
	int vItemSize = _princess->getVItem().size();
	WriteFile(file, &vItemSize, sizeof(int), &save, NULL);
	vector<string> vItemName;
	for (int i = 0; i < _princess->getVItem().size(); i++)
	{
		//WriteFile(file, &_princess->getVItem()[i]->getName(), sizeof(_princess->getVItem()[i]->getName()), &save, NULL);
		vItemName.push_back(_princess->getVItem()[i]->getName());
	}
	char* temp = TXTDATA->vectorArrayCombine(vItemName);
	WriteFile(file, temp, 100000, &save, NULL);

	CloseHandle(file);
}

void saveLoadScene::loadData(int idx)
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
	

void saveLoadScene::setSaveTitle(bool isSave, int idx)
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
		str = date[i].name +  " " + date[i].firstName + " (" + to_string(date[i].year) + "," + to_string(date[i].mon) + "," + to_string(date[i].day) + " )";
		_saveLoadInfo[date[i].idx].data.str += str;
	}
	if (isSave)
	{
		_saveLoadInfo[idx].data.isChoose = true;
		str = temp.name + " " + temp.firstName + " (" + to_string(temp.year) + "," + to_string(temp.mon) + "," + to_string(temp.day) + " )";
		_saveLoadInfo[idx].data.str += str;
	}
}

void saveLoadScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	while (1)
	{
		if (strSize > 29)
		{
			_vDialog.push_back(str.substr(idx, 29));
			idx += 29;
			strSize -= 29;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

bool saveLoadScene::dialogRender()
{
	if (_dialogType != DIALOG_ING) return true;

	IMAGEMANAGER->findImage("wideBack")->render(DC, 40, 460);

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
					TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			TextOut(DC, 180, 310 + _dialogIdx * 30, temp.c_str(), strlen(temp.c_str()));
		}
	}
	else
	{
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}

void saveLoadScene::setGodPhoto()
{
	_godName = _princess->getStatus().god.name;
	_godPlanet = _princess->getStatus().god.planet;

	if (_godName == "새턴")
		_npc.frameX = 0;
	else if (_godName == "우라누스")
		_npc.frameX = 1;
	else if (_godName == "넵튠")
		_npc.frameX = 2;
	else if (_godName == "마스")
		_npc.frameX = 3;
	else if (_godName == "비너스")
		_npc.frameX = 4;
	else if (_godName == "머큐리")
		_npc.frameX = 5;
	else if (_godName == "더 문")
		_npc.frameX = 6;
	else if (_godName == "솔")
		_npc.frameX = 7;
	else if (_godName == "하데스")
		_npc.frameX = 8;
	else if (_godName == "주피터")
		_npc.frameX = 9;
}