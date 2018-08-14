#pragma once
#include "gameNode.h"
#include "data.h"
#include "item.h"

class princess;

class inventoryScene : public gameNode
{
private:
	princess* _princess;

	bool _fin;
	vector<tagImg> _vInvenImg;
	vector<item*> _vInven;
	tagImg _chooseBox[2];

public:
	inventoryScene();
	~inventoryScene();

	HRESULT init();
	void update();
	void render();
	void release();

	void setItem();

	void setFin(bool fin) { _fin = fin; }
	bool getFin() { return _fin; }
};

