#pragma once
#include "gameNode.h"
#include "tileNode.h"

// mapToolScene Ŭ����
class mapToolScene : public gameNode
{
private:
	// ��ü ����
	tagTile _tiles[TILEX * TILEY];							// �ΰ��� ȭ�鿡 ���Ǵ� Ÿ�� (�� 400��)
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];	// ���� Ÿ�� (�� 160��)
	tagCurrentTile _currentTile;							// ���� Ÿ��
	RECT _rcSave;											// ���̺�
	RECT _rcLoad;											// �ε�
	RECT _rcTerrain;										// ����
	RECT _rcObject;											// ������Ʈ
	RECT _rcEraser;											// ���찳 (������Ʈ�� ����� ������ �����)
	
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

	// ����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	// ������, �Ҹ���
	mapToolScene() {}
	~mapToolScene() {}
};

