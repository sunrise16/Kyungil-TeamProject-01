#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{
	//���� �ʱ�ȭ
	_octopus = new octopus;
	_octopus->init();
	//���� �ʱ�ȭ
	_mushroom = new mushroom;
	_mushroom->init();

	return S_OK;
}

void inGameScene::release()
{
	//���� �Ҹ�
	_octopus->release();
	SAFE_DELETE(_octopus);
	//���� �Ҹ�
	_mushroom->release();
	SAFE_DELETE(_mushroom);
	
}

void inGameScene::update()
{

	//���� ������Ʈ
	_octopus->update();
	//���� ������Ʈ
	_mushroom->update();
}

void inGameScene::render()
{

	//���� ����
	_octopus->render();
	//���� ����
	_mushroom->render();
}
