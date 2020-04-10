#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{
	//¹®¾î ÃÊ±âÈ­
	_octopus = new octopus;
	_octopus->init();
	//¹ö¼¸ ÃÊ±âÈ­
	_mushroom = new mushroom;
	_mushroom->init();

	return S_OK;
}

void inGameScene::release()
{
	//¹®¾î ¼Ò¸ê
	_octopus->release();
	SAFE_DELETE(_octopus);
	//¹ö¼¸ ¼Ò¸ê
	_mushroom->release();
	SAFE_DELETE(_mushroom);
	
}

void inGameScene::update()
{

	//¹®¾î ¾÷µ¥ÀÌÆ®
	_octopus->update();
	//¹ö¼¸ ¾÷µ¥ÀÌÆ®
	_mushroom->update();
}

void inGameScene::render()
{

	//¹®¾î ·»´õ
	_octopus->render();
	//¹ö¼¸ ·»´õ
	_mushroom->render();
}
