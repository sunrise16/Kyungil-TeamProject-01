#pragma once
#include "gameNode.h"
#include "player.h"
#include "octopus.h"

// inGameScene Ŭ����
class inGameScene : public gameNode
{
private:
	// Ŭ���� ����
	player* _player;			// player Ŭ���� ����
	octopus* _octopus;			// octopus Ŭ���� ����

public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();
};