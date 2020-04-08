#include "inGameScene.h"

HRESULT inGameScene::init()
{
	//문어 초기화
	_octopus = new octopus;
	_octopus->init();

	return S_OK;
}

void inGameScene::release()
{

	_octopus->release();
	//SAFE_DELETE(_octopus);
	//문어 소멸
}

void inGameScene::update()
{
	
	//문어 업데이트
	_octopus->update();
}

void inGameScene::render()
{

	//문어 렌더
	_octopus->render();
}
