#pragma once
#include "gameNode.h"
#include "player.h"

class ingameScene : public gameNode
{

private:


	player* _player;

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

