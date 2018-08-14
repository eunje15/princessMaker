#pragma once
#include "gameNode.h"
#include "data.h"

class dadTalkScene : public gameNode
{
private:

public:
	dadTalkScene();
	~dadTalkScene();

	HRESULT init();
	void update();
	void render();
	void release();
};

