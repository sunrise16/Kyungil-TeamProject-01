#pragma once

// ���� ȭ�� Ÿ��
#define TILESIZE 64
#define MAP_TILEX 50
#define MAP_TILEY 50
#define TILESIZEX (MAP_TILEX * TILESIZE)
#define TILESIZEY (MAP_TILEY * TILESIZE)

#define TILEMAPSIZEX 11
#define TILEMAPSIZEY 4

#define CAMERA_TILEX WINSIZEX/TILESIZE
#define CAMERA_TILEY WINSIZEY/TILESIZE

// �̹��� Ÿ�� (ȭ�� ���� ��ܿ� �ٿ� ���� ���� Ÿ��)
//X SIZE ���� 6 (384pixel)

#define SAMPLE_TILEX 47
#define SAMPLE_TILEY 24

// �������� ����� ��Ʈ�ѵ�
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAIN, CTRL_OBJECT, CTRL_ERASER,
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};

// ����
enum TERRAIN
{
	TR_WALL, TR_GROUND, TR_GRASS, TR_WATER, TR_END
};

// ������Ʈ
enum OBJECT
{
	OBJ_CARPET,
	OBJ_BLOCK1, OBJ_BLOCK2, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_LINK, OBJ_BOSS, OBJ_MOB1, OBJ_MOB2,
	OBJ_NONE
};

enum MAPTOOL_MENU
{
	MENU_HOUSE,
	MENU_TOWN,
	MENU_BOSS,
	MENU_HOME,
	MENU_CHAR
};

// Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

	int x, y;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	//�巡�׿�
	bool isSelect;
};

// �̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

// ���� Ÿ�� ����ü
struct tagCurrentTile
{
	int x, y;
};

struct tagTileData
{
	tagTile tile[MAP_TILEY][MAP_TILEX];
};