#pragma once
#include "gameNode.h"

enum CUBE_TYPE { CUBE_DADTALK, CUBE_SCHEDULE };

class cube : public gameNode
{
private:
	image* _img;
	int _frameX, _frameY;
	CUBE_TYPE _type;
	vector<string> _vStr;
	float _x, _y;
	bool _dialogFin;

public:
	cube();
	~cube();

	HRESULT init();
	void update();
	void render();
	void release();

	void setXY(float x, float y) { _x = x, _y = y; }
	void setFrameX(int frameX) { _frameX = frameX; }
	void setFrameY(int frameY) { _frameY = frameY; }
	void setDialogFin(bool fin) { _dialogFin = fin; }

	bool getDialogFin() { return _dialogFin; }
	string getDialog(string cur);
};

