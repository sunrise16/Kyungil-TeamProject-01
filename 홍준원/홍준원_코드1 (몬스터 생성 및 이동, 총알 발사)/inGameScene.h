#pragma once
#include "gameNode.h"
#include "octopus.h"
#include "mushroom.h"

class inGameScene : public gameNode
{
private:
	octopus* _octopus;
	mushroom* _mushroom;


public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	inGameScene() {}
	~inGameScene() {}
};

