#include "stdafx.h"
#include "inGameScene.h"

// 초기화 (init)
HRESULT inGameScene::init()
{
	// player 클래스 동적 할당 생성
	_player = new player;
	_player->init();

	// octupus 클래스 동적 할당 생성
	_octopus = new octopus;
	_octopus->init();

	// mushroom 클래스 동적 할당 생성
	_mushroom = new mushroom;
	_mushroom->init();

	// 주소값 전달
	_player->setOctopusAdress(_octopus);
	_octopus->setPlayerAdress(_player);
	_player->setMushroomAdress(_mushroom);
	_mushroom->setPlayerAdress(_player);

	return S_OK;
}

// 해제 (release)
void inGameScene::release()
{
	// player 클래스 해제
	_player->release();
	SAFE_DELETE(_player);

	// octopus 클래스 해제
	_octopus->release();
	SAFE_DELETE(_octopus);

	// mushroom 클래스 해제
	_mushroom->release();
	SAFE_DELETE(_mushroom);
}

// 업데이트 (update)
void inGameScene::update()
{
	// player 클래스 업데이트
	_player->update();

	// octopus 클래스 업데이트
	_octopus->update();

	// mushroom 클래스 업데이트
	_mushroom->update();
}

// 렌더 (render)
void inGameScene::render()
{
	// player 클래스 렌더
	_player->render();

	// octopus 클래스 렌더
	_octopus->render();

	// mushroom 클래스 렌더
	_mushroom->render();
}