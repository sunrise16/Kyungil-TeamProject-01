#include "stdafx.h"
#include "mainGame.h"

// �ʱ�ȭ (init)
HRESULT mainGame::init()
{
	gameNode::init();

	// inGameScene Ŭ���� ���� �Ҵ� ����
	_inGameScene = new inGameScene;
	_inGameScene->init();

	// mapToolScene Ŭ���� ���� �Ҵ� ����
	_mapToolScene = new mapToolScene;
	_mapToolScene->init();

	// �� �߰�
	SCENEMANAGER->addScene("inGameScene", _inGameScene);
	SCENEMANAGER->addScene("mapToolScene", _mapToolScene);

	// ���� �� ����
	SCENEMANAGER->loadScene("mapToolScene");

	return S_OK;
}

// ���� (release)
void mainGame::release()
{
	gameNode::release();
}

// ������Ʈ (update)
void mainGame::update()
{
	gameNode::update();
	
	// �� �Ŵ��� ������Ʈ
	SCENEMANAGER->update();
}

// ���� (render)
void mainGame::render()
{
	// ��� �� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	// ���ڻ� ��� ���ֱ�
	SetBkMode(getMemDC(), TRANSPARENT);

	// �� �Ŵ��� ����
	SCENEMANAGER->render();

	// ����� ������ ȭ�� DC�� �׸���
	this->getBackBuffer()->render(getHDC());
}