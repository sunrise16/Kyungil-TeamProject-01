#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define MAP_HEIGHT 256

struct CAMERA {
	float x, y;
	RECT rc;
};

// mapToolScene Ŭ����
class mapToolScene : public gameNode
{
private:
	// ��ü ����
	tagTile _tiles[MAP_TILEY][MAP_TILEX];					// �ΰ��� ȭ�鿡 ���Ǵ� Ÿ�� (�� 400��)
	tagSampleTile _sampleTile[SAMPLE_TILEX][SAMPLE_TILEY];	// ���� Ÿ�� (�� 160��)
	tagCurrentTile _currentTile;							// ���� Ÿ��

	//�巡�׿�
	int _dragIndexStartX;
	int _dragIndexStartY;
	int _dragIndexEndX;
	int _dragIndexEndY;
	int _dragRectStartLeft;
	int _dragRectStartTop;
	int _dragRectStartRight;
	int _dragRectStartBottom;
	int _dragRectWidth;
	int _dragRectHeight;

	tagSampleTile _dragTiles;
	tagSampleTile _dragTile[TILEMAPSIZEY][TILEMAPSIZEX];


	//�޴� ���� ����
	MAPTOOL_MENU _menu;

	//UI RECT
	RECT _rcSave;							// ���̺�
	RECT _rcSave1;							// ���̺�
	RECT _rcSave2;							// ���̺�
	RECT _rcSave3;							// ���̺�
	
	RECT _rcLoad;							// �ε�
	RECT _rcLoad1;							// �ε�
	RECT _rcLoad2;							// �ε�
	RECT _rcLoad3;							// �ε�
	
	RECT _rcTerrain;						// ����
	RECT _rcObject;							// ������Ʈ
	RECT _rcEraser;							// ���찳 (������Ʈ�� ����� ������ �����)
	RECT _rcReset;							// ����
	
	RECT _rcMinimap;						// �̴ϸ� ��ü RECT
	RECT _rcMinimap_C;						// �̴ϸ� �� ī�޶� RECT
	
	CAMERA _rcMCamera;//���� ī�޶� RECT
	
	// UI ICON�� RECT
	RECT _rcSaveBg;
	RECT _rcLoadBg;
	RECT _rcUIBg;		// ����UI���RECT
	RECT _rcSaveLoadBg;
	RECT _rcMapSpace;
	RECT _rcArrowLeft;
	RECT _rcArrowRight;
	RECT icon[5];		// �޴� ���� �����ܿ� RECT �迭


	RECT mouseRect;		// ���콺 �巡���ϸ� �����Ǵ� RECT
	RECT selectTiles;	// ������ Ÿ�� ǥ���ϴ� RECT

	//ȭ�� ���(�׽�Ʈ)�� �ӽ� ����
	RECT tmp;
	// �巡�׿� ���콺 ������
	POINT mouseT;

	// ������ Ÿ�� ǥ�� RECT
	RECT select_tile;

	bool upUI;			// ����UI�˾�����
	bool objectOn;		// OBJ ��ư ������ �ش� �޴��� OBJ ������� ����.
	bool eraseOn;		// ERASER �����°�
	bool saveOn;		// SAVE ��ư �������� ����
	bool loadOn;		// LOAD ��ư �������� ����
	bool tilerectOn;	// �巡�׿�
	bool dragOnSample;	
	bool dragSelectedSample;	
	bool dragOn;
	bool noSample;		// MENU_AUTO, MENU_CHAR��

	char str[128];
	int scrollX; // Ÿ�ϸ� ��ũ��
	int scrollY; // �޴�����
	int camX, camY;

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

	// ��� Update() ���� ���� ����� �ϴ� RECT�� ����
	void updateRect();

	//����UI �˾� �ִϸ��̼� �Լ�
	void mapUiAnimation();

	// ����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	// Ű�Է� (VK_LBUTTON�� ������ (�ٸ� Ű�� ����))
	void input();
	void drag();

	// ���̺� �ε��Ҷ� �����Ǵ� RECT�� ANIMATION�� �Լ�
	void saveloadRectSet();

	// ������, �Ҹ���
	mapToolScene() {}
	~mapToolScene() {}
};

