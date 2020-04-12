#include "stdafx.h"
#include "inGameScene.h"

// �ʱ�ȭ (init)
HRESULT inGameScene::init()
{
	IMAGEMANAGER->addImage("test" ,"Images/Source/����_������4028x2756.bmp", 4028, 2756);
	// player Ŭ���� ���� �Ҵ� ����
	_player = new player;
	_player->init();

	// octupus Ŭ���� ���� �Ҵ� ����
	_octopus = new octopus;
	_octopus->init();

	// �ּҰ� ����
	_player->setOctopusAdress(_octopus);
	_octopus->setPlayerAdress(_player);

	return S_OK;
}

// ���� (release)
void inGameScene::release()
{
	// player Ŭ���� ����
	_player->release();
	SAFE_DELETE(_player);

	// octopus Ŭ���� ����
	_octopus->release();
	SAFE_DELETE(_octopus);
}

// ������Ʈ (update)
void inGameScene::update()
{
	// player Ŭ���� ������Ʈ
	_player->update();

	// octopus Ŭ���� ������Ʈ
	_octopus->update();
}

// ���� (render)
void inGameScene::render()
{
	IMAGEMANAGER->findImage("test")->render(getMemDC());
	// player Ŭ���� ����
	_player->render();

	// octopus Ŭ���� ����
	_octopus->render();
}