#include "stdafx.h"
#include "inGameScene.h"

// 초기화 (init)
HRESULT inGameScene::init()
{
	IMAGEMANAGER->addImage("test" ,"Images/Source/젤다_마을맵4028x2756.bmp", 4028, 2756);
	// player 클래스 동적 할당 생성
	_player = new player;
	_player->init();

	// octupus 클래스 동적 할당 생성
	_octopus = new octopus;
	_octopus->init();

	// 주소값 전달
	_player->setOctopusAdress(_octopus);
	_octopus->setPlayerAdress(_player);

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
}

// 업데이트 (update)
void inGameScene::update()
{
	// player 클래스 업데이트
	_player->update();

	// octopus 클래스 업데이트
	_octopus->update();
}

// 렌더 (render)
void inGameScene::render()
{
	IMAGEMANAGER->findImage("test")->render(getMemDC());
	// player 클래스 렌더
	_player->render();

	// octopus 클래스 렌더
	_octopus->render();
}