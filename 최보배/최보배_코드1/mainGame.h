#pragma once
#include "gameNode.h"
#include "maptoolScene.h"
#include "ingameScene.h"

// mainGame Ŭ����
class mainGame : public gameNode
{
public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ������, �Ҹ���
	mainGame() {}
	~mainGame() {}
};

