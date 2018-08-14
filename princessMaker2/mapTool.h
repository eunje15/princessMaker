#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapTool : public gameNode
{
private:
	tagTile _tile[TILEX*TILEY];
	//tagTile _tile[100 * TILEY];
	tagTile _tiles[100 * 40];
	tagSampleTile _sampleTile[SAMPLE_TILEX*SAMPLE_TILEY];
	tagCurrentTile _currentTile;
	tagCurrentTile _dragTile[2];
	TERRAIN _terrain;
	OBJECT _obj;
	TERRAIN _tr;
	bool _isSetObj, _isDrag, _isCamera;
	vector<pair<RECT, OBJECT>> _objRect;
	vector<pair<RECT, TERRAIN>> _trRect;
	RECT _selectBox[3];
public:
	mapTool();
	~mapTool();

	HRESULT init();
	void update();
	void render();
	void release();

	void setup();
	void setObject();
	void setMap();
	void save();
	void load();
	void objLoad();
};

