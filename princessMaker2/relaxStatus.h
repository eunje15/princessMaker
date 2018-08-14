#pragma once
#include "gameNode.h"
#include "data.h"

class princess;

class relaxStatus : public gameNode
{
private:
	enum RELAX_TYPE { RELAX_FREE, RELAX_VACATION };

private:
	princess* _princess;
	string _name;
	int _season;
	int _gold;
	RELAX_TYPE _type;
	tagRelax _relaxInfo[8];
public:
	relaxStatus();
	~relaxStatus();
	HRESULT init();
	void update();
	void render();
	void release();

	void setRelaxStatus(int type);

	string getName() { return _name; }
	int getGold() { return _gold; }

	tagRelax getRelaxIdx(int idx);
};

