#include "stdafx.h"
#include "relaxStatus.h"
#include "princess.h"

relaxStatus::relaxStatus()
{
}


relaxStatus::~relaxStatus()
{
}

HRESULT relaxStatus::init()
{
	return S_OK;
}

void relaxStatus::update()
{
}

void relaxStatus::render()
{
}

void relaxStatus::release()
{
}

void relaxStatus::setRelaxStatus(int type)
{
	_type = (RELAX_TYPE)type;
	switch (_type)
	{
	case RELAX_FREE:
		_name = "자유행동";
		_relaxInfo[0].sensitivity = 0;
		_relaxInfo[0].stress = -1;
		_relaxInfo[0].weight = 0;
		
		_relaxInfo[1].sensitivity = 0;
		_relaxInfo[1].stress = -2;
		_relaxInfo[1].weight = 0;
		_gold = 10;
		break;
	case RELAX_VACATION:
		_name = "바캉스";
		_gold = 10;

		for (int i = 0; i < 8; i++)
		{
			_relaxInfo[i].stress = -3;
			_relaxInfo[i].sensitivity = 0;
			_relaxInfo[i].weight = 0;
		}

		_relaxInfo[1].stress = -6;
		_relaxInfo[1].weight = -0.1;

		_relaxInfo[3].stress = -2;

		_relaxInfo[4].sensitivity = 1;

		_relaxInfo[5].sensitivity = 1;

		_relaxInfo[6].sensitivity = 2;
		_relaxInfo[6].stress = -6;
		_relaxInfo[6].weight = 0.1;

		_relaxInfo[7].sensitivity = 1;
		break;
	}
}

tagRelax relaxStatus::getRelaxIdx(int idx)
{
	_princess = SCENEMANAGER->getPrincessAddress();
	if (_name == "바캉스")
	{
		if (idx == 0) //산
			return _relaxInfo[4 + (int)_princess->getSeason()];
		else //바다
			return _relaxInfo[(int)_princess->getSeason()];
	}
	return _relaxInfo[idx];
}
