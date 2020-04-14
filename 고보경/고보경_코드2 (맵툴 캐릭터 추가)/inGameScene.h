#pragma once
#include "gameNode.h"
#include "player.h"
#include "octopus.h"
#include "mushroom.h"
#include "boss.h"
#include "tileNode.h"

// inGameScene Ŭ����
class inGameScene : public gameNode
{
private:
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
	int camX, camY;
	char str[100];
	char str2[30];
	char str3[100];

public:
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