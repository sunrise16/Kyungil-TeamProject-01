#pragma once
#include "gameNode.h"
#include "inGameScene.h"

// mainGame Ŭ����
class mainGame : public gameNode
{
private:
	// Ŭ���� ����
	inGameScene* _inGameScene;		// inGameScene Ŭ���� ����

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