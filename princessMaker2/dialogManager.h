#pragma once
#include "singletonBase.h"
class dialogManager : public singletonBase<dialogManager>
{
private:
	string _str;
	int _count, _idx, _speed;
public:
	dialogManager();
	~dialogManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setDialog(string str, int speed);
	string getCurrentDialog();
	string getTotalDialog();

	int getDialogSize() { return _str.size(); }
};

