#pragma once
#include "gameNode.h"
#include "octopus.h"

class inGameScene :	public gameNode
{
private:
	octopus* _octopus;


public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	inGameScene() {}
	~inGameScene() {}
};

