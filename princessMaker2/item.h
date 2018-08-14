#pragma once
#include "gameNode.h"
#include "data.h"

class item : public gameNode 
{
private:
	string _name;
	int _price;
	ITEM_TYPE _type;
	int _frameX, _frameY;
	image* _img;
	vector<pair<string, float>> _property;
	bool _isWear;
	int	_clothesFrameY;
	float _x, _y;
	bool _isStore;
public:
	item();
	~item();

	HRESULT init();
	void update();
	void render();
	void release();

	void setItem(string name, int price, bool isStore, vector<pair<string, float>> property, int type, int frameX, int frameY);
	void setImage();
	void setXY(float x, float y);
	void setName(string name) { _name = name; }
	void setFrameY(int frameY) { _clothesFrameY = frameY; }
	int getFrameY() { return _clothesFrameY; }
	float getX() { return _x; }
	float getY() { return _y; }
	ITEM_TYPE getType() { return _type; }
	void setIsWear(bool isWear) { _isWear = isWear; }
	bool getIsWear() { return _isWear; }

	string getName() { return _name; }
	int getPrice() { return _price; }
	vector<pair<string, float>> getProperty() { return _property; }
	bool getIsStore() { return _isStore; }
};

