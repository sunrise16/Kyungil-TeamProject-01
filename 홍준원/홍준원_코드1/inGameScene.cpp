#include "inGameScene.h"

HRESULT inGameScene::init()
{
	//���� �ʱ�ȭ
	_octopus = new octopus;
	_octopus->init();

	return S_OK;
}

void inGameScene::release()
{

	_octopus->release();
	//SAFE_DELETE(_octopus);
	//���� �Ҹ�
}

void inGameScene::update()
{

	//���� ������Ʈ
	_octopus->update();
}

void inGameScene::render()
{

	//���� ����
	_octopus->render();
}
