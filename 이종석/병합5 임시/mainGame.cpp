#include "stdafx.h"
#include "mainGame.h"

// �ʱ�ȭ (init)
HRESULT mainGame::init()
{
	// gameNode �ʱ�ȭ
	gameNode::init();

	// mapToolScene Ŭ���� ���� �Ҵ� ����
	_mapToolScene = new mapToolScene;
	_mapToolScene->init();

	// inGameScene Ŭ���� ���� �Ҵ� ����
	_inGameScene = new inGameScene;
	_inGameScene->init();

	// �ּҰ� ����
	_mapToolScene->setInGameSceneAdress(_inGameScene);
	_inGameScene->setMapToolSceneAdress(_mapToolScene);

	// �� �߰�
	SCENEMANAGER->addScene("mapToolScene", _mapToolScene);
	SCENEMANAGER->addScene("inGameScene", _inGameScene);

	// ���� �� ����
	SCENEMANAGER->loadScene("mapToolScene");

	// �ʱ�ȭ ����
	return S_OK;
}

// ���� (release)
void mainGame::release()
{
	// gameNode ����
	gameNode::release();
}

// ������Ʈ (update)
void mainGame::update()
{
	// gameNode ������Ʈ
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