#include "stdafx.h"
#include "cube.h"


cube::cube()
{
}


cube::~cube()
{
}

HRESULT cube::init()
{
	_img = IMAGEMANAGER->findImage("cube");
	_vStr = TXTDATA->txtDataLoadSlash("dialog/cube_dialog.txt");
	_frameX = _frameY = 0;
	return S_OK;
}

void cube::update()
{
}

void cube::render()
{
	_img->frameRender(DC, _x, _y, _frameX, _frameY);
}

void cube::release()
{
}

string cube::getDialog(string cur)
{
	string str = "";
	if (cur == "DADTALK")
		str = _vStr[0];
	else
	{
		for (int i = 0; i < 4; i++)
		{
			string temp = "DADTALK" + to_string(i);
			if (temp == cur)
			{
				str = _vStr[i + 1];
				break;
			}
		}
	}
	return str;
}
