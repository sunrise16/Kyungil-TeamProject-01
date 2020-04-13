#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define MAP_HEIGHT 256

// mapToolScene Ŭ����
class mapToolScene : public gameNode
{
private:
	// ��ü ����
	tagTile _tiles[MAP_TILEX * MAP_TILEY];							// �ΰ��� ȭ�鿡 ���Ǵ� Ÿ�� (�� 400��)
	tagSampleTile _sampleTile[SAMPLE_TILEX * SAMPLE_TILEY];	// ���� Ÿ�� (�� 160��)
	tagCurrentTile _currentTile;							// ���� Ÿ��
	
	//�޴� ���� ����
	MAPTOOL_MENU _menu;

	//UI RECT
	RECT _rcSave;											// ���̺�
	RECT _rcLoad;											// �ε�
	RECT _rcTerrain;										// ����
	RECT _rcObject;											// ������Ʈ
	RECT _rcEraser;							// ���찳 (������Ʈ�� ����� ������ �����)
	RECT _rcReset;							// ���찳 (������Ʈ�� ����� ������ �����)
	RECT _rcMCamera;//���� ī�޶� RECT
	
	RECT _rcUIBg;	// ����UI���RECT
	RECT _rcSaveLoadBg;
	RECT _rcMapSpace;
	RECT _rcArrowLeft;
	RECT _rcArrowRight;
	RECT _rcObjectMap;
	RECT icon[5];

	//���콺�� ������ ��ǥ
	POINT mouseCoord;

	// ������ Ÿ�� ǥ�� RECT
	RECT select_tile;

	bool upUI;	// ����UI�˾�����
	bool tileSelect;
	bool objectOn;
	bool eraseOn;

	char str[128];
	int scrollX; // Ÿ�ϸ� ��ũ��
	int scrollY; // �޴�����

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

	void cameraScroll();
	//����UI �˾� �ִϸ��̼� �Լ�
	void mapUiAnimation();

	// ��ǥ�� WINDOW��ǥ���� ��ü�̹����� ��ǥ�� �ٲ��ֱ�
	POINT setMapCoord(POINT mouseP);

	// ����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	void input();
	//����ó����(ex > UI��� �ڿ� Ÿ�� �׷����ų� UI icon �ڿ� Rect �׷����� ���� ����ó��)


	// ������, �Ҹ���
	mapToolScene() {}
	~mapToolScene() {}
};

