#pragma once
#include "gameNode.h"
#include "player.h"
#include "octopus.h"

// inGameScene 클래스
class inGameScene : public gameNode
{
private:
	// 클래스 관련
	player* _player;			// player 클래스 선언
	octopus* _octopus;			// octopus 클래스 선언

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();
};