#include "stdafx.h"
#include "mainGame.h"

// �ʱ�ȭ (init)
HRESULT mainGame::init()
{
	gameNode::init();

	// �� �߰�
	SCENEMANAGER->addScene("mapToolScene", new mapToolScene);

	SCENEMANAGER->addScene("ingameScene", new ingameScene);
	// ���� �� ����
	SCENEMANAGER->loadScene("ingameScene");

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
