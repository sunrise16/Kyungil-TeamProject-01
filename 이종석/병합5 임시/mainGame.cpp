#include "stdafx.h"
#include "mainGame.h"

// 초기화 (init)
HRESULT mainGame::init()
{
	// gameNode 초기화
	gameNode::init();

	// mapToolScene 클래스 동적 할당 생성
	_mapToolScene = new mapToolScene;
	_mapToolScene->init();

	// inGameScene 클래스 동적 할당 생성
	_inGameScene = new inGameScene;
	_inGameScene->init();

	// 주소값 전달
	_mapToolScene->setInGameSceneAdress(_inGameScene);
	_inGameScene->setMapToolSceneAdress(_mapToolScene);

	// 씬 추가
	SCENEMANAGER->addScene("mapToolScene", _mapToolScene);
	SCENEMANAGER->addScene("inGameScene", _inGameScene);

	// 현재 씬 설정
	SCENEMANAGER->loadScene("mapToolScene");

	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void mainGame::release()
{
	// gameNode 해제
	gameNode::release();
}

// 업데이트 (update)
void mainGame::update()
{
	// gameNode 업데이트
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