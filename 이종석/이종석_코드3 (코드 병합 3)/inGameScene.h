#pragma once
#include "gameNode.h"
#include "player.h"
#include "octopus.h"
#include "mushroom.h"
#include "tileNode.h"

// inGameScene Ŭ����
class inGameScene : public gameNode
{
private:
	// Ŭ���� ����
	player* _player;			// player Ŭ���� ����
	octopus* _octopus;			// octopus Ŭ���� ����
	mushroom* _mushroom;		// mushroom Ŭ���� ����

	// �ӽ�
	tagTile _tiles[MAP_TILEY * MAP_TILEX];					// �ΰ��� ȭ�鿡 ���Ǵ� Ÿ�� (�� 400��)
	int camX, camY;

public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// Ÿ�� ��ġ
	void updateRect();
	void load();
	void mapRender();
};