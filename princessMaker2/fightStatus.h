#pragma once
#include "gameNode.h"
class fightStatus : public gameNode
{
private:
	string _direction;
	string _where;

public:
	fightStatus();
	~fightStatus();

	HRESULT init(string direction, string where);
	void update();
	void render();
	void release();

	string getDirection() { return _direction; }
	string getWhere() { return _where; }
};

