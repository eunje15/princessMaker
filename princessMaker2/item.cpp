#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init()
{
	return S_OK;
}

void item::update()
{
}

void item::render()
{
	_img->frameRender(DC, _x, _y, _frameX, _frameY);
}

void item::release()
{
}

void item::setItem(string name, int price, bool isStore, vector<pair<string, float>> property, int type, int frameX, int frameY)
{
	_name = name;
	_price = price;
	_isStore = isStore;
	_property = property;
	_type = (ITEM_TYPE)type;
	_frameX = frameX;
	_frameY = frameY;
	setImage();
}

void item::setImage()
{
	switch (_type)
	{
	case ITEM_WEAPON: case ITEM_ARMOR:
		_img = IMAGEMANAGER->findImage("weapon");
	break;
	case ITEM_CLOTHES:
		_img = IMAGEMANAGER->findImage("clothes");
	break;
	case ITEM_COOK:
		_img = IMAGEMANAGER->findImage("cook");
	break;
	case ITEM_GOODS:
		_img = IMAGEMANAGER->findImage("goods");
		break;
	}
}

void item::setXY(float x, float y)
{
	_x = x, _y = y;
}
