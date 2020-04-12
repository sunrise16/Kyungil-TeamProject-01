#include "stdafx.h"
#include "mainGame.h"

// 초기화 (init)
HRESULT mainGame::init()
{
	gameNode::init();

	// inGameScene 클래스 동적 할당 생성
	_inGameScene = new inGameScene;
	_inGameScene->init();

	// mapToolScene 클래스 동적 할당 생성
	_mapToolScene = new mapToolScene;
	_mapToolScene->init();

	// 씬 추가
	SCENEMANAGER->addScene("inGameScene", _inGameScene);
	SCENEMANAGER->addScene("mapToolScene", _mapToolScene);

	// 현재 씬 설정
	SCENEMANAGER->loadScene("mapToolScene");

	return S_OK;
}

// 해제 (release)
void mainGame::release()
{
	gameNode::release();
}

// 업데이트 (update)
void mainGame::update()
{
	gameNode::update();
	
	// 씬 매니저 업데이트
	SCENEMANAGER->update();
}

// 렌더 (render)
void mainGame::render()
{
	// 흰색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	// 글자색 배경 없애기
	SetBkMode(getMemDC(), TRANSPARENT);

	// 씬 매니저 렌더
	SCENEMANAGER->render();

	// 백버퍼 내용을 화면 DC에 그리기
	this->getBackBuffer()->render(getHDC());
}