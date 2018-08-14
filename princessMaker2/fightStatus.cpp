#include "stdafx.h"
#include "fightStatus.h"


fightStatus::fightStatus()
{
}


fightStatus::~fightStatus()
{
}

HRESULT fightStatus::init(string direction, string where)
{
	_direction = direction;
	_where = where;
	return S_OK;
}

void fightStatus::update()
{
}

void fightStatus::render()
{
}

void fightStatus::release()
{
}
