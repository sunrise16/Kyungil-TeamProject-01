#include "stdafx.h"
#include "inGameScene.h"

// �ʱ�ȭ (init)
HRESULT inGameScene::init()
{
	// player Ŭ���� ���� �Ҵ� ����
	_player = new player;
	_player->init();

	// octupus Ŭ���� ���� �Ҵ� ����
	_octopus = new octopus;
	_octopus->init();

	// mushroom Ŭ���� ���� �Ҵ� ����
	_mushroom = new mushroom;
	_mushroom->init();

	// �ּҰ� ����
	_player->setOctopusAdress(_octopus);
	_octopus->setPlayerAdress(_player);
	_player->setMushroomAdress(_mushroom);
	_mushroom->setPlayerAdress(_player);

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

	// mushroom Ŭ���� ����
	_mushroom->release();
	SAFE_DELETE(_mushroom);
}

// ������Ʈ (update)
void inGameScene::update()
{
	// player Ŭ���� ������Ʈ
	_player->update();

	// octopus Ŭ���� ������Ʈ
	_octopus->update();

	// mushroom Ŭ���� ������Ʈ
	_mushroom->update();
}

// ���� (render)
void inGameScene::render()
{
	// player Ŭ���� ����
	_player->render();

	// octopus Ŭ���� ����
	_octopus->render();

	// mushroom Ŭ���� ����
	_mushroom->render();
}