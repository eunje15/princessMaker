#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	IMAGEMANAGER->addFrameImage("sampleMap", "image/field/e_samplemap(320x1680,16x84).bmp", 320, 1680, 16, 84, false, RGB(255, 0, 255));
	

	_isSetObj = false;
	_isDrag = false;

	if (!_isSetObj)
		objLoad();
	setup();
	load();
	return S_OK;
}

void mapTool::update()
{
	if (_isSetObj)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) setObject();
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			for (int i = 0; i < SAMPLE_TILEX*SAMPLE_TILEY; i++)
			{
				POINT ptMouse = PointMake(_ptMouse.x + _cameraCenter.x - WINSIZEX / 2, _ptMouse.y + _cameraCenter.y - WINSIZEY / 2);

				if (PtInRect(&_sampleTile[i].rc, ptMouse))
				{
					_sampleTile[i].terrain = TR_GROUND;
					_sampleTile[i].object = OBJ_NONE;
					InvalidateRect(_hWnd, NULL, false);
					break;
				}
			}
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_isCamera)
			{
				for (int i = 0; i < SAMPLE_TILEX*SAMPLE_TILEY; i++)
				{
					POINT ptMouse = PointMake(_ptMouse.x + _cameraCenter.x - WINSIZEX / 2, _ptMouse.y + _cameraCenter.y - WINSIZEY / 2);
					if (PtInRect(&_sampleTile[i].rc, ptMouse))
					{
						_isDrag = false;
						_dragTile[0].x = _sampleTile[i].frameX;
						_dragTile[0].y = _sampleTile[i].frameY;
						break;
					}
				}
			}
			else if(_isDrag)
			{
				for (int i = 0; i < TILEX*TILEY; i++)
				{
					POINT ptMouse = PointMake(_ptMouse.x + _cameraCenter.x - WINSIZEX / 2, _ptMouse.y + _cameraCenter.y - WINSIZEY / 2);
					if (PtInRect(&_tile[i].rc, ptMouse))
					{
						_isDrag = false;
						int idX = i % TILEX, idY = i / TILEX;
						for (int j = _dragTile[0].y; j <= _dragTile[1].y; j++)
						{
							for (int k = _dragTile[0].x; k <= _dragTile[1].x; k++)
							{
								_tile[(idY + (j - _dragTile[0].y))*TILEX + ((k - _dragTile[0].x) + idX)].terrain = _sampleTile[(j)*SAMPLE_TILEX + (k)].terrain;
								_tile[(idY + (j - _dragTile[0].y))*TILEX + ((k - _dragTile[0].x) + idX)].object = _sampleTile[(j)*SAMPLE_TILEX + (k)].object;
								_tile[(idY + (j - _dragTile[0].y))*TILEX + ((k - _dragTile[0].x) + idX)].terrainFrameX = _tile[(idY + (j - _dragTile[0].y))*TILEX + ((k - _dragTile[0].x) + idX)].objFrameX = _sampleTile[j*SAMPLE_TILEX + k].frameX;
								_tile[(idY + (j - _dragTile[0].y))*TILEX + ((k - _dragTile[0].x) + idX)].terrainFrameY = _tile[(idY + (j - _dragTile[0].y))*TILEX + ((k - _dragTile[0].x) + idX)].objFrameY = _sampleTile[j*SAMPLE_TILEX + k].frameY;
							}
						}
						InvalidateRect(_hWnd, NULL, false);
						break;
					}
				}
				
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (_isCamera)
			{
				for (int i = 0; i < SAMPLE_TILEX*SAMPLE_TILEY; i++)
				{
					POINT ptMouse = PointMake(_ptMouse.x + _cameraCenter.x - WINSIZEX / 2, _ptMouse.y + _cameraCenter.y - WINSIZEY / 2);
					if (PtInRect(&_sampleTile[i].rc, ptMouse))
					{
						if (_sampleTile[i].frameX != _dragTile[0].x && _sampleTile[i].frameY != _dragTile[0].y)
						{
							_isDrag = true;
							_dragTile[1].x = _sampleTile[i].frameX;
							_dragTile[1].y = _sampleTile[i].frameY;
						}
						break;
					}
				}
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) setMap();
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			for (int i = 0; i < TILEX*TILEY; i++)
			{
				POINT ptMouse = PointMake(_ptMouse.x + _cameraCenter.x - WINSIZEX / 2, _ptMouse.y + _cameraCenter.y - WINSIZEY / 2);

				if (PtInRect(&_tile[i].rc, ptMouse))
				{
					_tile[i].terrain = TR_GROUND;
					_tile[i].object = OBJ_NONE;
					InvalidateRect(_hWnd, NULL, false);
					break;
				}
			}
		}
	}
}

void mapTool::render()
{
	SetTextColor(_camera->getMemDC(), RGB(0, 255, 0));
	if (_isSetObj)
	{
		for (int i = 0; i < 2; i++)
		{
			Rectangle(_camera->getMemDC(), _selectBox[i].left, _selectBox[i].top, _selectBox[i].right, _selectBox[i].bottom);
		}

		DrawText(_camera->getMemDC(), TEXT("save"), strlen("save"), &_selectBox[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		DrawText(_camera->getMemDC(), TEXT("oLoad"), strlen("oLoad"), &_selectBox[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		for (int i = 0; i < SAMPLE_TILEY * SAMPLE_TILEX; i++)
		{
			IMAGEMANAGER->findImage("sampleMap")->frameRender(DC, _sampleTile[i].rc.left, _sampleTile[i].rc.top, _sampleTile[i].frameX, _sampleTile[i].frameY);
		}

		for (int i = 0; i < _objRect.size(); i++)
		{
			Rectangle(_camera->getMemDC(), _objRect[i].first.left, _objRect[i].first.top, _objRect[i].first.right, _objRect[i].first.bottom);
			switch (_objRect[i].second)
			{
			case OBJ_WOOD:
				DrawText(_camera->getMemDC(), TEXT("OBJ_WOOD"), strlen("OBJ_WOOD"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_CASTLE:
				DrawText(_camera->getMemDC(), TEXT("OBJ_CASTLE"), strlen("OBJ_CASTLE"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_HALL:
				DrawText(_camera->getMemDC(), TEXT("OBJ_HALL"), strlen("OBJ_HALL"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_HALL_DOWN1:
				DrawText(_camera->getMemDC(), TEXT("OBJ_HALL_DOWN1"), strlen("OBJ_HALL_DOWN1"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_HALL_UP1:
				DrawText(_camera->getMemDC(), TEXT("OBJ_HALL_UP1"), strlen("OBJ_HALL_UP1"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_HALL_DOWN2:
				DrawText(_camera->getMemDC(), TEXT("OBJ_HALL_DOWN2"), strlen("OBJ_HALL_DOWN2"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_HALL_UP2:
				DrawText(_camera->getMemDC(), TEXT("OBJ_HALL_UP2"), strlen("OBJ_HALL_UP2"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_CIENAGA:
				DrawText(_camera->getMemDC(), TEXT("OBJ_CIENAGA"), strlen("OBJ_CIENAGA"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_CIENAGA_DOWN:
				DrawText(_camera->getMemDC(), TEXT("OBJ_CIENAGA_DOWN"), strlen("OBJ_CIENAGA_DOWN"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_CIENAGA_UP:
				DrawText(_camera->getMemDC(), TEXT("OBJ_CIENAGA_UP"), strlen("OBJ_CIENAGA_UP"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_NOTICE:
				DrawText(_camera->getMemDC(), TEXT("OBJ_NOTICE"), strlen("OBJ_NOTICE"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_STONE:
				DrawText(_camera->getMemDC(), TEXT("OBJ_STONE"), strlen("OBJ_STONE"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_TREASURE:
				DrawText(_camera->getMemDC(), TEXT("OBJ_TREASURE"), strlen("OBJ_TREASURE"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_ETC:
				DrawText(_camera->getMemDC(), TEXT("OBJ_ETC"), strlen("OBJ_ETC"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_CRIMINAL:
				DrawText(_camera->getMemDC(), TEXT("OBJ_CRIMINAL"), strlen("OBJ_CRIMINAL"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
		}

		for (int i = 0; i < _trRect.size(); i++)
		{
			Rectangle(_camera->getMemDC(), _trRect[i].first.left, _trRect[i].first.top, _trRect[i].first.right, _trRect[i].first.bottom);
			switch (_trRect[i].second)
			{
			case TR_GROUND:
				DrawText(_camera->getMemDC(), TEXT("TR_GROUND"), strlen("TR_GROUND"), &_trRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case TR_CASTLE:
				DrawText(_camera->getMemDC(), TEXT("TR_CASTLE"), strlen("TR_CASTLE"), &_trRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case TR_WOOD:
				DrawText(_camera->getMemDC(), TEXT("TR_WOOD"), strlen("TR_WOOD"), &_trRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
		}

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = 0; i < SAMPLE_TILEY * SAMPLE_TILEX; i++)
			{
					Rectangle(DC, _sampleTile[i].rc.left, _sampleTile[i].rc.top, _sampleTile[i].rc.right, _sampleTile[i].rc.bottom);
					char str[128];
					sprintf_s(str, "[%d/%d]", (int)_sampleTile[i].object,(int)_sampleTile[i].terrain);
				//	sprintf_s(str, "[%d]", (int)_sampleTile[i].object);
					TextOut(DC, _sampleTile[i].rc.left, _sampleTile[i].rc.top, str, strlen(str));
			}
		}
	}
	else
	{
		int x1 = (_cameraCenter.x - WINSIZEX / 2) / TILESIZE;
		int y1 = (_cameraCenter.y - WINSIZEY / 2) / TILESIZE;
		int x2 = (_cameraCenter.x + WINSIZEX / 2) / TILESIZE + 1;
		int y2 = (_cameraCenter.y + WINSIZEY / 2) / TILESIZE + 1;

		for (int i = y1; i < y2; i++)
		{
			for (int j = x1; j < x2; j++)
			{
				IMAGEMANAGER->findImage("map")->frameRender(DC, _tile[i*TILEX + j].rc.left, _tile[i*TILEX + j].rc.top, _tile[i*TILEX + j].terrainFrameX, _tile[i*TILEX+j].terrainFrameY);
			}
		}
		/*for (int i = 0; i < TILEX*TILEY; i++)
		{
			IMAGEMANAGER->findImage("map")->frameRender(DC, _tile[i].rc.left, _tile[i].rc.top, _tile[i].terrainFrameX, _tile[i].terrainFrameY);
		}
*/

		for (int i = y1; i < y2; i++)
		{
			for (int j = x1; j < x2; j++)
			{
				if (_tile[i*TILEX + j].object == OBJ_NONE) continue;
				IMAGEMANAGER->findImage("map")->frameRender(DC, _tile[i*TILEX + j].rc.left, _tile[i*TILEX + j].rc.top, _tile[i*TILEX + j].objFrameX, _tile[i*TILEX + j].objFrameY);
			}
		}

		//for (int i = 0; i < TILEX*TILEY; i++)
		//{
		//	if (_tile[i].object == OBJ_NONE) continue;
		//	IMAGEMANAGER->findImage("map")->frameRender(DC, _tile[i].rc.left, _tile[i].rc.top, _tile[i].objFrameX, _tile[i].objFrameY);
		//}

		if (KEYMANAGER->isToggleKey(VK_LSHIFT))
		{
			_isCamera = true;
			HPEN pen, oldPen;
			pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(_camera->getMemDC(), pen);
			for (int i = 0; i < 2; i++)
			{
				if(i == 0)
					Rectangle(_camera->getMemDC(), _selectBox[i].left, _selectBox[i].top, _selectBox[i].right, _selectBox[i].bottom);
				else
				{
					pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
					oldPen = (HPEN)SelectObject(_camera->getMemDC(), pen);
					Rectangle(_camera->getMemDC(), _selectBox[i].left, _selectBox[i].top, _selectBox[i].right, _selectBox[i].bottom);
				}
				SelectObject(_camera->getMemDC(), oldPen);
				DeleteObject(pen);
			}
			DrawText(_camera->getMemDC(), TEXT("save"), strlen("save"), &_selectBox[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			DrawText(_camera->getMemDC(), TEXT("load"), strlen("load"), &_selectBox[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
			for (int i = 0; i < SAMPLE_TILEY * SAMPLE_TILEX; i++)
			{
				IMAGEMANAGER->findImage("sampleMap")->frameRender(DC, _sampleTile[i].rc.left, _sampleTile[i].rc.top, _sampleTile[i].frameX, _sampleTile[i].frameY);
			}
			
		}
		else
			_isCamera = false;

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = y1; i < y2; i++)
			{
				for (int j = x1; j < x2; j++)
				{
					Rectangle(DC, _tile[i*TILEX + j].rc.left, _tile[i*TILEX + j].rc.top, _tile[i*TILEX + j].rc.right, _tile[i*TILEX + j].rc.bottom);
					char str[128];
					sprintf_s(str, "[%d/%d/%d]", i*TILEX+j,_tile[i*TILEX + j].object, _tile[i*TILEX + j].terrain);
					TextOut(DC, _tile[i*TILEX + j].rc.left, _tile[i*TILEX + j].rc.top, str, strlen(str));
				}
			}

			if (_isCamera)
			{
				for (int i = 0; i < SAMPLE_TILEX*SAMPLE_TILEY; i++)
				{
					Rectangle(DC, _sampleTile[i].rc.left, _sampleTile[i].rc.top, _sampleTile[i].rc.right, _sampleTile[i].rc.bottom);
				}
			}
		}
	}
	SetTextColor(_camera->getMemDC(), RGB(0, 0, 0));
}

void mapTool::release()
{
}

void mapTool::setup()
{
	if (_isSetObj)
	{
		for (int i = 0; i < SAMPLE_TILEY; i++)
		{
			for (int j = 0; j < SAMPLE_TILEX; j++)
			{
				_sampleTile[i * SAMPLE_TILEX + j].frameX = j;
				_sampleTile[i * SAMPLE_TILEX + j].frameY = i;

				_sampleTile[i*SAMPLE_TILEX + j].terrain = TR_GROUND;
				_sampleTile[i*SAMPLE_TILEX + j].object = OBJ_NONE;

				SetRect(&_sampleTile[i*SAMPLE_TILEX + j].rc, j*SAMPLE_TILE_SIZE, i*SAMPLE_TILE_SIZE, 
					SAMPLE_TILE_SIZE + j * SAMPLE_TILE_SIZE, SAMPLE_TILE_SIZE + i * SAMPLE_TILE_SIZE);
			}
		}

		for (int i = 0; i < 2; i++)
		{
			_selectBox[i] = RectMake(500 + i * 50, 50, 40, 20);
		}

		for (int i = 1; i < 15; i++)
		{
			RECT rc = RectMake(450 + (i % 2) * 160, 100 + (i / 2) * 50, 150, 30);
			_objRect.push_back(make_pair(rc, (OBJECT)i));
		}

		for (int i = 0; i < 3; i++)
		{
			RECT rc = RectMake(450 + (i % 2) * 160, 500 + (i / 2) * 50, 150, 30);
			_trRect.push_back(make_pair(rc, (TERRAIN)i));
		}
	}
	else
	{
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				SetRect(&_tile[i*TILEX + j].rc, j*TILESIZE, i*TILESIZE, TILESIZE + j * TILESIZE, TILESIZE + i * TILESIZE);
			}
		}

		for (int i = 0; i < SAMPLE_TILEY; i++)
		{
			for (int j = 0; j < SAMPLE_TILEX; j++)
			{
				SetRect(&_sampleTile[i*SAMPLE_TILEX + j].rc, (WINSIZEX - IMAGEMANAGER->findImage("sampleMap")->getWidth()) + j*SAMPLE_TILE_SIZE, i*SAMPLE_TILE_SIZE,
					(WINSIZEX - IMAGEMANAGER->findImage("sampleMap")->getWidth()) + SAMPLE_TILE_SIZE + j * SAMPLE_TILE_SIZE, SAMPLE_TILE_SIZE + i * SAMPLE_TILE_SIZE);
			}
		}
		for (int i = 0; i < 2; i++)
		{
			_selectBox[i] = RectMake(420, 450 + i*30, 40, 20);
		}
	}
}

void mapTool::setObject()
{
		for (int i = 0; i < 2; i++)
		{
			if (PtInRect(&_selectBox[i], _ptMouse))
			{
				if (i == 0)
				{
					if(_isDrag)
						save();
					break;
				}
				if (i == 1)
				{
					load();
					_isDrag = true;
					break;
				}
			}
		}

		if (!_isDrag) return;

		for (int i = 0; i < _objRect.size(); i++)
		{
			if (PtInRect(&_objRect[i].first, _ptMouse))
			{
				_obj = _objRect[i].second;
				break;
			}
		}

		for (int i = 0; i < _trRect.size(); i++)
		{
			if (PtInRect(&_trRect[i].first, _ptMouse))
			{
				_tr = _trRect[i].second;
				break;
			}
		}

	for (int i = 0; i < SAMPLE_TILEX * SAMPLE_TILEY; i++)
	{
		POINT ptMouse = PointMake(_ptMouse.x + _cameraCenter.x - WINSIZEX / 2, _ptMouse.y + _cameraCenter.y - WINSIZEY / 2);
		if (PtInRect(&_sampleTile[i].rc, ptMouse))
		{
				_sampleTile[i].terrain = _tr;
		//		_sampleTile[i].object = _obj;
			InvalidateRect(_hWnd, NULL, false);
			break;
		}
	}
}

void mapTool::setMap()
{
	if (_isCamera)
	{
		for (int i = 0; i < 2; i++)
		{
			if (PtInRect(&_selectBox[i], _ptMouse))
			{
				if (i == 0)
				{
				//	if (_isDrag)
					save();
					break;
				}
				if (i == 1)
				{
					load();
				//_isDrag = true;
					break;
				}
			}
		}
		
		for (int i = 0; i < SAMPLE_TILEX*SAMPLE_TILEY; i++)
		{
			POINT ptMouse = PointMake(_ptMouse.x + _cameraCenter.x - WINSIZEX / 2, _ptMouse.y + _cameraCenter.y - WINSIZEY / 2);
			if (PtInRect(&_sampleTile[i].rc, ptMouse))
			{
				_currentTile.x = _sampleTile[i].frameX;
				_currentTile.y = _sampleTile[i].frameY;
				_terrain = _sampleTile[i].terrain;
				_obj = _sampleTile[i].object;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < TILEX*TILEY; i++)
		{
			POINT ptMouse = PointMake(_ptMouse.x + _cameraCenter.x - WINSIZEX / 2, _ptMouse.y + _cameraCenter.y - WINSIZEY / 2);
			if (PtInRect(&_tile[i].rc, ptMouse))
			{
				_tile[i].terrain = _terrain;
				_tile[i].object = _obj;
				_tile[i].terrainFrameX = _tile[i].objFrameX = _currentTile.x;
				_tile[i].terrainFrameY = _tile[i].objFrameY = _currentTile.y;

				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
	}
}


void mapTool::save()
{
	HANDLE	file;
	DWORD	save;

	if (_isSetObj)
	{
		file = CreateFile(FILENAME, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(file, _sampleTile, sizeof(tagSampleTile) * SAMPLE_TILEX * SAMPLE_TILEY, &save, NULL);
	}
	else
	{
		file = CreateFile(MAPNAME, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(file, _tile, sizeof(tagTile) * TILEX * TILEY, &save, NULL);
	}

	CloseHandle(file);
}

void mapTool::load()
{
	HANDLE	file;
	DWORD	load;
	if (_isSetObj)
	{
		file = CreateFile(FILENAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _sampleTile, sizeof(tagSampleTile) * SAMPLE_TILEX * SAMPLE_TILEY, &load, NULL);
	}
	else
	{
		file = CreateFile(MAPNAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _tile, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

		/*for (int i = 0; i < 40; ++i)
		{
			for (int j = 0; j < 40; ++j)
			{
				_tiles[i * 100 + j] = _tile[i * 40 + j];
			}
		}
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 40; j < 100; j++)
			{
				SetRect(&_tiles[i*100 + j].rc, j*TILESIZE, i*TILESIZE, TILESIZE + j * TILESIZE, TILESIZE + i * TILESIZE);
			}
		}*/
	}
	CloseHandle(file);
}

void mapTool::objLoad()
{
	HANDLE	file;
	DWORD	load;

	file = CreateFile(FILENAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _sampleTile, sizeof(tagSampleTile) * SAMPLE_TILEX * SAMPLE_TILEY, &load, NULL);

	CloseHandle(file);
}