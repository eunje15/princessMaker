#pragma once

#define TILESIZE 40
#define SAMPLE_TILE_SIZE 20

#define TILEX 100
#define TILEY 40

#define TILESIZEX TILESIZE*TILEX
#define TILESIZEY TILESIZE*TILEY

#define SAMPLE_TILEX 16
#define SAMPLE_TILEY 84

#define SAMPLE_SIZEX SAMPLE_TILE_SIZE * SAMPLE_TILEX
#define SAMPLE_SIZEY SAMPLE_TILE_SIZE * SAMPLE_TILEY

#define FILENAME "obj/e_obj.map"
#define MAPNAME "map/e_map.map"

enum TERRAIN
{
	TR_GROUND, TR_CASTLE, TR_WOOD 
};

//동부의 정의
enum OBJECT
{
	OBJ_NONE, OBJ_WOOD, OBJ_CASTLE, OBJ_HALL, OBJ_HALL_DOWN1, OBJ_HALL_UP1, OBJ_HALL_DOWN2, OBJ_HALL_UP2,
	OBJ_CIENAGA, OBJ_CIENAGA_DOWN, OBJ_CIENAGA_UP, OBJ_NOTICE, OBJ_STONE, OBJ_TREASURE, OBJ_ETC, OBJ_CRIMINAL
};

struct tagTile
{
	TERRAIN		terrain;
	OBJECT		object;
	RECT		rc;
	int			terrainFrameX;
	int			terrainFrameY;
	int			objFrameX;
	int			objFrameY;
};

struct tagSampleTile
{
	TERRAIN		terrain;
	OBJECT		object;
	RECT		rc;
	int			frameX;
	int			frameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};