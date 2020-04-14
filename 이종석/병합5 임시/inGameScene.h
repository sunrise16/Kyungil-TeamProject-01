#pragma once
#include "gameNode.h"
#include "player.h"
#include "octopus.h"
#include "mushroom.h"
#include "boss.h"
#include "tileNode.h"

// Ŭ���� ���� ����
class mapToolScene;

// inGameScene Ŭ����
class inGameScene : public gameNode
{
private:
	// �ּҰ� ����
	mapToolScene* _mapToolSceneAdress;

	// Ŭ���� ����
	player* _player;			// player Ŭ���� ����
	octopus* _octopus;			// octopus Ŭ���� ����
	mushroom* _mushroom;		// mushroom Ŭ���� ����
	boss* _boss;				// boss Ŭ���� ����

	// �ӽ�
	tagTile _tiles[MAP_TILEY * MAP_TILEX];		// �ΰ��� ȭ�鿡 ���Ǵ� Ÿ�� (�� 400��)
	RECT empty;									// IntersectRect�� ��Ʈ
	RECT _bgRc;
	RECT _cameraRc;
	int cameraX, cameraY;
	POINT bgcenter;
	image* _country;
	char str[100];
	char str2[30];
	char str3[100];
	POINT playerPt;
	float octopusPt_x;
	float octopusPt_y;
	float mushroomPt_x;
	float mushroomPt_y;
	float bossPt_x;
	float bossPt_y;

public:
	// GET, SET �Լ�
	void setPlayerPt(POINT _playerPt) { playerPt = _playerPt; }
	void setOctopusPtX(float _octopusPtX) { octopusPt_x = _octopusPtX; }
	void setOctopusPtY(float _octopusPtY) { octopusPt_y = _octopusPtY; }
	void setMushroomPtX(float _mushroomPtX) { mushroomPt_x = _mushroomPtX; }
	void setMushroomPtY(float _mushroomPtY) { mushroomPt_y = _mushroomPtY; }
	void setBossPtX(float _bossPtX) { bossPt_x = _bossPtX; }
	void setBossPtY(float _bossPtY) { bossPt_y = _bossPtY; }
	// �ּҰ� �ޱ�
	void setMapToolSceneAdress(mapToolScene* mapToolSceneAdress) { _mapToolSceneAdress = mapToolSceneAdress; }

	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// Ÿ�� �ε�
	void load();

	// Ÿ�� ������Ʈ
	void updateRect();

	// Ÿ�� ����
	void mapRender();
};