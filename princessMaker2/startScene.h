#pragma once
#include "gameNode.h"
#include "princessScene.h"
#include "prologueDialog.h"

class princess;

class startScene : public gameNode
{
private:
	enum SAVELOAD_TYPE { SAVELOAD_FIN, SAVELOAD_SAVE, SAVELOAD_LOAD, SAVELOAD_NONE };
private:
	princess* _princess;

public:
	startScene();
	~startScene();

	HRESULT init();
	void update();
	void render();
	void release();
};

