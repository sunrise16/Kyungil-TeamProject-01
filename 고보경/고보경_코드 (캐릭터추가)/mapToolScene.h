#pragma once
#include "gameNode.h"
#include "player.h"
#include "octopus.h"
#include "mushroom.h"
#include "boss.h"
#include "tileNode.h"

#define MAP_HEIGHT 256			// ���� ����

// ī�޶� ����ü
struct CAMERA
{
	float x, y;
	RECT rc;
};

//===========================================================================//
//
// < �� �� �� Ʈ >
// 1. �巡�׷� ���ý� �ش� ���� Ÿ�� �̹��� ���̰� ó��
// 2. ����, ĳ����, �� �߰� ����
// 3. ĳ���� �����ϰ� ���� �ٽ� ��ġ ���ϴµ� Y������ �ٽ� ����� (�ٽ� ��ġ�� �� ������ ���� ���� ����)
// 4. gameStart�� ĳ���� �����ϰ� ENTERŰ ������ ���� ��ŸƮ �Ǹ鼭 ĳ���Ͱ� �����̰� �ٽ� ������ ����ϴ�.
//
//--------------------------------------------------------------------------//
//
//	TAB Ű : ���� UI �ö���� �������� ó��
//	EŰ : ERASERŰ (������Ʈ ����� Ű)		==> Ű�� ������ ��� ����
//	RŰ : ERASERŰ (Ÿ�� ����� Ű)		==> Ű�� ������ ��� ����
//	W, A, S, D : ȭ�� �̵�Ű
//	
// ***** ���� Ÿ�Ͽ��� �巡�� �� �Ŀ� ��� Ŭ���ؼ� ���� ���� (ptMouse �������� ������)
// ***** �巡�� Ǫ�� Ű : SPACE Ű
//
// Ÿ��(_tiles)���� �巡�� �ϸ� �� ������ ������ ���� Ÿ�� 1���� �巡�� ������ �����.
// ���� Ÿ��(_sampleTile)���� �巡�� �ϸ� �� ������ŭ Ÿ�Ͽ� ���� �� �ִ�.
//
//===========================================================================//

// mapToolScene Ŭ����
class mapToolScene : public gameNode
{
private:
	// ��ü ����
	player* _player;			// player Ŭ���� ����
	octopus* _octopus;			// octopus Ŭ���� ����
	mushroom* _mushroom;		// mushroom Ŭ���� ����
	boss* _boss;

	// Ÿ�� ����
	tagTile _tiles[MAP_TILEY][MAP_TILEX];					// �ΰ��� ȭ�鿡 ���Ǵ� Ÿ�� (�� 400��)
	tagSampleTile _sampleTile[SAMPLE_TILEX][SAMPLE_TILEY];	// ���� Ÿ�� (�� 160��)
	tagCurrentTile _currentTile;							// ���� Ÿ��
	// �巡�� ����
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
	vector<tagSampleTile> _dragT;			// �巡���� ���� Ÿ�� �̹��� ��ǥ�� �����ϴ� ����
	RECT _drag;								// �巡�׿� ��Ʈ (���� Ÿ�� �巡���ϸ� �� ��Ʈ�� ���콺 ��ǥ�� ����)
	// UI ����
	RECT _rcSave;							// ���̺� �޴�ĭ
	RECT _rcSave1;							// ���̺� ����� 1
	RECT _rcSave2;							// ���̺� ����� 2
	RECT _rcSave3;							// ���̺� ����� 3
	RECT _rcLoad;							// �ε� �޴�ĭ
	RECT _rcLoad1;							// �ε� ����� 1
	RECT _rcLoad2;							// �ε� ����� 2
	RECT _rcLoad3;							// �ε� ����� 3
	RECT _rcTerrain;						// ����
	RECT _rcObject;							// ������Ʈ
	RECT _rcEraser;							// ���찳 (������Ʈ�� ����� ������ ���� ����)
	RECT _rcReset;							// ����
	RECT _rcMinimap;						// �̴ϸ� ��ü RECT
	RECT _rcMinimap_C;						// �̴ϸ� �� ī�޶� RECT
	CAMERA _rcMCamera;						// ���� ī�޶� RECT
	// UI ���� (������)
	RECT _rcSaveBg;
	RECT _rcLoadBg;
	RECT _rcUIBg;							// ���� UI ��� RECT
	RECT _rcSaveLoadBg;
	RECT _rcMapSpace;
	RECT _rcArrowLeft;
	RECT _rcArrowRight;
	RECT icon[5];							// �޴� ���� �����ܿ� RECT �迭
	RECT mouseRect;							// ���콺 �巡���ϸ� �����Ǵ� RECT
	RECT selectTiles;						// ������ Ÿ�� ǥ���ϴ� RECT
	RECT tmp;								// ȭ�� ���(�׽�Ʈ)�� �ӽ� ����
	POINT mouseT;							// �巡�׿� ���콺 ������
	RECT select_tile;						// ������ Ÿ�� ǥ�� RECT

	//ĳ���� ���ÿ�
	RECT _rcPlayer;
	RECT _rcOctopus;
	RECT _rcMushroom;
	RECT _rcBoss;

	// ���� ����
	MAPTOOL_MENU _menu;						// �޴� ����
	CTRL currentCtrl;						// ���� ��Ʈ�� ����
	CTRL _ctrlSelect;						// ���� ��Ʈ�� ���� �Ǻ�
	bool upUI;								// ���� UI �˾� ����
	bool objectOn;							// OBJ ��ư ������ �ش� �޴��� OBJ ������� ����.
	bool eraseOn;							// ERASER �����°�
	bool saveOn;							// SAVE ��ư �������� ����
	bool loadOn;							// LOAD ��ư �������� ����
	bool tilerectOn;						// �巡�׿�
	bool dragOnSample;						// ���� Ÿ�� �巡�� üũ
	bool dragSelectedSample;				// ���� Ÿ�� �巡�� ����
	bool dragOn;							// ���� Ÿ�� �巡�� ���� �׸��¿�
	bool noSample;							// MENU_AUTO, MENU_CHAR��

	// ĳ���� ���ú���
	bool playerOn;
	bool playerSet;
	bool OctopusOn;
	bool octopusSet;
	bool MushroomOn;
	bool mushroomSet;
	bool BossOn;
	bool bossSet;

	bool gameStart;

	char str[1024];							// ���ڿ�
	int scrollX;							// Ÿ�ϸ� ��ũ��
	int scrollY;							// �޴�����
	int camX, camY;							// ī�޶� X, Y ��ǥ��
	float tmpX, tmpY;

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

	// ��� ������Ʈ �� RECT�� ����
	void updateRect();

	// ���� UI �˾� �ִϸ��̼�
	void mapUiAnimation();

	// ����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	// Ű�Է� (VK_LBUTTON�� ������ (�ٸ� Ű�� ����))
	void input();
	void drag();

	// ���̺� �ε��Ҷ� �����Ǵ� RECT �ִϸ��̼�
	void saveloadRectSet();

	// ������, �Ҹ���
	mapToolScene() {}
	~mapToolScene() {}
};