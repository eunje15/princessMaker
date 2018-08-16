#include "stdafx.h"
#include "princess.h"


princess::princess()
{
}


princess::~princess()
{
}

HRESULT princess::init()
{
		//임시로 넣어놓음
		_info.firstName = "윤";
		_info.name = "딸래미";
		_info.year = 1200, _info.mon = 1, _info.day = 1, _info.dayOfWeek = 0;
		_info.blood = BLOOD_A;
		_info.strBlood = "A";
		_info.age = 12;
		_info.dietType = "무리하지 않는다";
		_info.gold = 1000000;

		_bodyInfo.height = 149.16;
		_bodyInfo.weight = 41.90;
		_bodyInfo.bast = 74.57;
		_bodyInfo.waist = 55.82;
		_bodyInfo.hip = 77.71;
		_bodyInfo.clothesType = 0; //평상복

		_date.name = _info.name;
		_date.firstName = _info.firstName;
		_date.year = _info.year;
		_date.mon = _info.mon;
		_date.day = _info.day;
		_date.dayOfWeek = _info.dayOfWeek;
		_date.faceType = PRINCESS_NORMAL;

		if (3 <= _info.mon && _info.mon < 6)
			_season = SPRING;
		if (6 <= _info.mon && _info.mon < 9)
			_season = SUMMER;
		if (9 <= _info.mon && _info.mon < 12)
			_season = AUTUMN;
		if (_info.mon == 12 || _info.mon == 1 || _info.mon == 2)
			_season = WINTER;

		//여기까지 임시로

		setStatus();
	

	char str[128];
	sprintf_s(str, "body%d", _info.age);
	_body.img = IMAGEMANAGER->findImage(str);
	_body.x = 100;
	_body.y = WINSIZEY - _body.img->getFrameHeight();
	
	sprintf_s(str, "face%d", _info.age);
	_face.img = IMAGEMANAGER->findImage(str);
	_face.x = 100;
	_face.y = _body.y - _face.img->getFrameHeight() + 2;

	_educationCount = new int[10];
	_workSuccess = new int[15];

	_educationCount[5] = 7;
	_workSuccess[7] = 19;

	return S_OK;
}

void princess::update()
{
}

void princess::render()
{
	_body.img->frameRender(DC, _body.x, _body.y, 0, _bodyInfo.clothesType);
	_face.img->frameRender(DC, _face.x, _face.y, (int)_date.faceType, _bodyInfo.clothesType);
}

void princess::release()
{
}

void princess::setStatus()
{
	switch (_info.mon)
	{
	case 1:
		if (_info.day <= 19)
			_status.god.constellation = "염소자리", _status.god.idx = 0;
		else
			_status.god.constellation = "물병자리", _status.god.idx = 1;
		break;
	case 2:
		if (_info.day <= 18)
			_status.god.constellation = "물병자리", _status.god.idx = 1;
		else
			_status.god.constellation = "물고기자리", _status.god.idx = 2;
		break;
	case 3:
		if (_info.day <= 20)
			_status.god.constellation = "물고기자리", _status.god.idx = 2;
		else
			_status.god.constellation = "양자리", _status.god.idx = 3;
		break;
	case 4:
		if (_info.day <= 19)
			_status.god.constellation = "양자리", _status.god.idx = 3;
		else
			_status.god.constellation = "황소자리", _status.god.idx = 4;
		break;
	case 5:
		if (_info.day <= 20)
			_status.god.constellation = "황소자리", _status.god.idx = 4;
		else
			_status.god.constellation = "쌍둥이자리", _status.god.idx = 5;
		break;
	case 6:
		if (_info.day <= 21)
			_status.god.constellation = "쌍둥이자리", _status.god.idx = 5;
		else
			_status.god.constellation = "게자리", _status.god.idx = 6;
		break;
	case 7:
		if (_info.day <= 22)
			_status.god.constellation = "게자리", _status.god.idx = 6;
		else
			_status.god.constellation = "사자자리", _status.god.idx = 7;
		break;
	case 8:
		if (_info.day <= 22)
			_status.god.constellation = "사자자리", _status.god.idx = 7;
		else
			_status.god.constellation = "처녀자리", _status.god.idx = 5;
		break;
	case 9:
		if (_info.day <= 22)
			_status.god.constellation = "처녀자리", _status.god.idx = 5;
		else
			_status.god.constellation = "천칭자리", _status.god.idx = 4;
		break;
	case 10:
		if (_info.day <= 23)
			_status.god.constellation = "천칭자리", _status.god.idx = 4;
		else
			_status.god.constellation = "전갈자리", _status.god.idx = 8;
		break;
	case 11:
		if (_info.day <= 22)
			_status.god.constellation = "전갈자리", _status.god.idx = 8;
		else
			_status.god.constellation = "사수자리", _status.god.idx = 9;
		break;
	case 12:
		if (_info.day <= 21)
			_status.god.constellation = "사수자리", _status.god.idx = 9;
		else
			_status.god.constellation = "염소자리", _status.god.idx = 0;
		break;
	}
	vector<string> vStr = TXTDATA->txtLoadCsv("dialog/별자리능력치.csv", _status.god.constellation.c_str());

	_status.god.planet = vStr[0];
	_status.god.name = vStr[1];

	_status.hp = atoi(vStr[3].c_str());
	_status.physical = atoi(vStr[4].c_str());
	_status.intelligence = atoi(vStr[5].c_str());
	_status.elegance = atoi(vStr[6].c_str());
	_status.sexual = atoi(vStr[7].c_str());
	_status.morality = atoi(vStr[8].c_str());
	_status.faith = atoi(vStr[9].c_str());
	_status.sensitivity = atoi(vStr[10].c_str());
	_status.warrior = atoi(vStr[11].c_str());
	_status.warriorSkill = atoi(vStr[12].c_str());
	_status.power = atoi(vStr[13].c_str());
	_status.magic = atoi(vStr[14].c_str());
	_status.magicSkill = atoi(vStr[15].c_str());
	_status.spell = atoi(vStr[16].c_str());
	_status.spellDefence = atoi(vStr[17].c_str());
	_status.sociality = atoi(vStr[18].c_str());
	_status.manner = atoi(vStr[19].c_str());
	_status.art = atoi(vStr[20].c_str());
	_status.conversation = atoi(vStr[21].c_str());
	_status.housework = atoi(vStr[22].c_str());
	_status.cooking = atoi(vStr[23].c_str());
	_status.cleaning = atoi(vStr[24].c_str());
	_status.personality = atoi(vStr[25].c_str());
	_status.total = atoi(vStr[26].c_str());
	_status.plusNorth = vStr[27];
}

void princess::setStress(int stress)
{
	_status.stress -= stress; 
	if (_status.stress < 0) _status.stress = 0;
}


bool princess::setItem(item* newItem)
{
	if (_vInven.size() > 50) return false;
	_vInven.push_back(newItem);
}

void princess::setDataItem(vector<item*> vTotal)
{
	for (int i = 0; i < _vItemName.size(); i++)
	{
		for (int j = 0; j < vTotal.size(); j++)
		{
			if (_vItemName[i] == vTotal[j]->getName())
			{
				_vInven.push_back(vTotal[j]);
				break;
			}
		}
	}
}

void princess::deleteVItem(int idx)
{
	vector<item*>::iterator vIter;
	vIter = _vInven.begin() + idx;
	for (int i = 0; i < (*vIter)->getProperty().size(); i++)
	{
		changeStatus((*vIter)->getProperty()[i].first, -(*vIter)->getProperty()[i].second);
	}
	_vInven.erase(vIter);
}

void princess::changeStatus(string name, float value)
{
	if (name == "공격력")
	{
		_status.power += value;
		if (_status.power < 0)
			_status.power = 0;
	}
	else if (name == "전투기술")
	{
		_status.warriorSkill += value;
		if (_status.warriorSkill < 0)
			_status.warriorSkill = 0;
	}
	else if (name == "방어력")
	{
		_status.defPower += value;
		if (_status.defPower < 0)
			_status.defPower = 0;
	}
	else if (name == "기품")
	{
		_status.elegance += value;
		if (_status.elegance < 0)
			_status.elegance = 0;
	}
	else if (name == "항마력")
	{
		_status.spellDefence += value;
		if (_status.spellDefence < 0)
			_status.spellDefence = 0;
	}
	else if (name == "매력")
	{
		_status.sexual += value;
		if (_status.sexual < 0)
			_status.sexual = 0;
	}
	else if (name == "도덕성")
	{
		_status.morality += value;
		if (_status.morality < 0)
			_status.morality = 0;
	}
	else if (name == "감수성")
	{
		_status.sensitivity += value;
		if (_status.sensitivity < 0)
			_status.sensitivity = 0;
	}
	else if (name == "지능")
	{
		_status.intelligence += value;
		if (_status.intelligence < 0)
			_status.intelligence = 0;
	}
	else if (name == "전사평가")
	{
		_status.warrior += value;
		if (_status.warrior < 0)
			_status.warrior = 0;
	}
	else if (name == "체중")
	{
		_bodyInfo.weight += value;
	}
	else if (name == "키")
	{
		_bodyInfo.height += value;
	}
	else if (name == "예술")
	{
		_status.art += value;
		if (_status.art < 0)
			_status.art = 0;
	}
	else if (name == "마력")
	{
		_status.spell += value;
		if (_status.spell < 0)
			_status.spell = 0;
	}
}

void princess::setAge(int age)
{
	_info.age = age;

	char str[128];
	sprintf_s(str, "body%d", _info.age);
	_body.img = IMAGEMANAGER->findImage(str);
	_body.x = 100;
	_body.y = WINSIZEY - _body.img->getFrameHeight();

	sprintf_s(str, "face%d", _info.age);
	_face.img = IMAGEMANAGER->findImage(str);
	_face.x = 100;
	_face.y = _body.y - _face.img->getFrameHeight() + 2;
}
