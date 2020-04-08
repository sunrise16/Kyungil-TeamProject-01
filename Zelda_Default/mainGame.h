#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "maptoolScene.h"

// mainGame 클래스
class mainGame : public gameNode
{
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

