#include "stdafx.h"
#include "dialogManager.h"


dialogManager::dialogManager()
{
}


dialogManager::~dialogManager()
{
}

HRESULT dialogManager::init()
{
	
	return S_OK;
}

void dialogManager::release()
{
}

void dialogManager::update()
{
}

void dialogManager::render()
{
}

void dialogManager::setDialog(string str, int speed)
{
	_str.clear();
	_str = str;
	_idx = _count = 0;
	_speed = speed;
}

string dialogManager::getCurrentDialog()
{
	string temp = "";
	_count++;
	if (!(_count % _speed))
	{
		if (_idx < _str.size() + 1)
		{
			if (_str[_idx] < 0)
				_idx += 2;
			else
				_idx++;
			_count = 0;
		}
		else return "end";
	}
	
	temp = _str.substr(0, _idx);
	return temp;
}

string dialogManager::getTotalDialog()
{
	return _str;
}
