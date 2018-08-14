#pragma once
#include "gameNode.h"
#include "data.h"

class princess;

class eastBattleScene : public gameNode
{
private:
	enum DAY_TYPE { DAY, NIGHT };
	enum STATE_TYPE { STATE_WORK, STATE_MEET, STATE_MEET_MONSTER, STATE_MEET_PEOPLE };

private:
	princess* _princess;
	int _day, _time;
public:
	eastBattleScene();
	~eastBattleScene();

	HRESULT init();
	void update();
	void render();
	void release();
};

