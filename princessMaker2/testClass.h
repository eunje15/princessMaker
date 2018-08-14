#pragma once
#include "gameNode.h"
#include "data.h"

class testClass : public gameNode
{
private:
	vector<string>	_vDialog, _teachDialog;
	int				_dialogIdx;
	int				_nextIdx;
public:
	testClass();
	~testClass();

	HRESULT init();
	void update();
	void render();
	void release();
	void setDialog(string dialog);
	bool dialogRender();
};

