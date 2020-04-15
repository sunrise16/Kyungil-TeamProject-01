#pragma once
#include "gameNode.h"
#include "player.h"
#include "octopus.h"
#include "mushroom.h"
#include "boss.h"
#include "tileNode.h"

// 클래스 전방 선언
class mapToolScene;

// inGameScene 클래스
class inGameScene : public gameNode
{
private:
	// 주소값 관련
	mapToolScene* _mapToolSceneAdress;

	// 클래스 관련
	player* _player;			// player 클래스 선언
	octopus* _octopus;			// octopus 클래스 선언
	mushroom* _mushroom;		// mushroom 클래스 선언
	boss* _boss;				// boss 클래스 선언

	// 임시
	tagTile _tiles[MAP_TILEY * MAP_TILEX];		// 인게임 화면에 사용되는 타일 (총 400개)
	RECT empty;									// IntersectRect용 렉트
	RECT _bgRc;
	RECT _cameraRc;
	int cameraX, cameraY;
	POINT bgcenter;
	image* _country;
	char str[100];
	char str2[30];
	char str3[100];
	POINT playerPt;
	float octopusPt_x;
	float octopusPt_y;
	float mushroomPt_x;
	float mushroomPt_y;
	float bossPt_x;
	float bossPt_y;

public:
	// GET, SET 함수
	void setPlayerPt(POINT _playerPt) { playerPt = _playerPt; }
	void setOctopusPtX(float _octopusPtX) { octopusPt_x = _octopusPtX; }
	void setOctopusPtY(float _octopusPtY) { octopusPt_y = _octopusPtY; }
	void setMushroomPtX(float _mushroomPtX) { mushroomPt_x = _mushroomPtX; }
	void setMushroomPtY(float _mushroomPtY) { mushroomPt_y = _mushroomPtY; }
	void setBossPtX(float _bossPtX) { bossPt_x = _bossPtX; }
	void setBossPtY(float _bossPtY) { bossPt_y = _bossPtY; }
	// 주소값 받기
	void setMapToolSceneAdress(mapToolScene* mapToolSceneAdress) { _mapToolSceneAdress = mapToolSceneAdress; }

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