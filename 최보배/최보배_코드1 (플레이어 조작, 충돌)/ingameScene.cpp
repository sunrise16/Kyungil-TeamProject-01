#include "stdafx.h"
#include "ingameScene.h"

HRESULT ingameScene::init()
{

	_player = new player;
	_player->init();

	return S_OK;
}

void ingameScene::release()
{
	_player->release();
	SAFE_DELETE(_player);
}

void ingameScene::update()
{
	_player->update();
}

void ingameScene::render()
{
	_player->render();
}
