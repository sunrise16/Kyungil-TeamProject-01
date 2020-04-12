#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define MAP_HEIGHT 256

struct CAMERA
{
	float x, y;
	RECT rc;
};

// mapToolScene Ŭ����
class mapToolScene : public gameNode
{
private:
	// ��ü ����
	tagTile _tiles[MAP_TILEY * MAP_TILEX];					// �ΰ��� ȭ�鿡 ���Ǵ� Ÿ�� (�� 400��)
	tagSampleTile _sampleTile[SAMPLE_TILEX][SAMPLE_TILEY];	// ���� Ÿ�� (�� 160��)
	tagCurrentTile _currentTile;							// ���� Ÿ��
	
	//�巡�׿�
	int _dragIndexStartX;
	int _dragIndexStartY;
	int _dragIndexEndX;
	int _dragIndexEndY;
	int _dragRectWidth;
	int _dragRectHeight;


	//�޴� ���� ����
	MAPTOOL_MENU _menu;

	//UI RECT
	RECT _rcSave;											// ���̺�
	RECT _rcSave1;											// ���̺�
	RECT _rcSave2;											// ���̺�
	RECT _rcSave3;											// ���̺�
	
	RECT _rcLoad;											// �ε�
	RECT _rcLoad1;											// �ε�
	RECT _rcLoad2;											// �ε�
	RECT _rcLoad3;											// �ε�
	
	RECT _rcTerrain;										// ����
	RECT _rcObject;											// ������Ʈ
	RECT _rcEraser;							// ���찳 (������Ʈ�� ����� ������ �����)
	RECT _rcReset;							// ���찳 (������Ʈ�� ����� ������ �����)
	
	RECT _rcMinimap;
	RECT _rcMinimap_C;
	
	CAMERA _rcMCamera;//���� ī�޶� RECT
	
	RECT _BG;
	RECT _rcSaveBg;
	RECT _rcLoadBg;
	RECT _rcUIBg;	// ����UI���RECT
	RECT _rcSaveLoadBg;
	RECT _rcMapSpace;
	RECT _rcArrowLeft;
	RECT _rcArrowRight;
	RECT icon[5];

	RECT mouseRect;
	RECT selectTiles;

	//BRUSH
	HBRUSH water;
	HBRUSH grass;
	HBRUSH block;
	HBRUSH ground;


	//���콺�� ������ ��ǥ
	POINT mouseCoord;
	
	// UI��� �ű� �ӽ� ���콺 ����Ʈ
	POINT tmp;
	POINT mouseT;

	// ������ Ÿ�� ǥ�� RECT
	RECT select_tile;

	bool upUI;	// ����UI�˾�����
	bool tileSelect;
	bool objectOn;
	bool eraseOn;
	bool saveOn;
	bool loadOn;
	bool tilerectOn;
	bool dragOnSample;

	char str[128];
	int scrollX; // Ÿ�ϸ� ��ũ��
	int scrollY; // �޴�����
	int camX, camY;
	int idX, idY;

	CTRL currentCtrl;

	// ���� ����
	CTRL _ctrlSelect;										// ���� � ��Ʈ�� �������� �Ǻ�

public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ���� ����
	void mapToolSetup();
	void setMap();
	void save();
	void load();
	void reset();

	void updateRect();
	//����UI �˾� �ִϸ��̼� �Լ�
	void mapUiAnimation();

	// ����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	void input();
	//����ó����(ex > UI��� �ڿ� Ÿ�� �׷����ų� UI icon �ڿ� Rect �׷����� ���� ����ó��)

	void setSampleTile(int indexX, int indexY);

	void saveloadRectSet();

	// ������, �Ҹ���
	mapToolScene() {}
	~mapToolScene() {}
};

