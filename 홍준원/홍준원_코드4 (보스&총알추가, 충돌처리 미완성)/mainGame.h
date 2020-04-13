#pragma once
#include "gameNode.h"
#include "inGameScene.h"
#include "mapToolScene.h"

// mainGame 클래스
class mainGame : public gameNode
{
private:
	// 클래스 관련
	inGameScene* _inGameScene;		// inGameScene 클래스 선언
	mapToolScene* _mapToolScene;	// mapToolScene 클래스 선언

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	mainGame() {}
	~mainGame() {}
};