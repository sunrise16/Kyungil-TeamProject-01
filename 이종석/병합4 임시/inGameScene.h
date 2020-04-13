#pragma once
#include "gameNode.h"
#include "player.h"
#include "octopus.h"
#include "mushroom.h"
#include "tileNode.h"

// inGameScene 클래스
class inGameScene : public gameNode
{
private:
	// 클래스 관련
	player* _player;			// player 클래스 선언
	octopus* _octopus;			// octopus 클래스 선언
	mushroom* _mushroom;		// mushroom 클래스 선언

	// 임시
	tagTile _tiles[MAP_TILEY * MAP_TILEX];					// 인게임 화면에 사용되는 타일 (총 400개)
	int camX, camY;

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 타일 로드
	void load();

	// 타일 업데이트
	void updateRect();

	// 타일 렌더
	void mapRender();
};