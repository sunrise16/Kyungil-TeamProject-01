#pragma once
#include "gameNode.h"
#include "tileNode.h"

// mapToolScene 클래스
class mapToolScene : public gameNode
{
private:
	// 객체 관련
	tagTile _tiles[TILEX * TILEY];							// 인게임 화면에 사용되는 타일 (총 400개)
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];	// 샘플 타일 (총 160개)
	tagCurrentTile _currentTile;							// 현재 타일
	RECT _rcSave;											// 세이브
	RECT _rcLoad;											// 로드
	RECT _rcTerrain;										// 지형
	RECT _rcObject;											// 오브젝트
	RECT _rcEraser;											// 지우개 (오브젝트만 지우고 지형은 덮어씌움)
	
	// 변수 관련
	CTRL _ctrlSelect;										// 현재 어떤 컨트롤 상태인지 판별

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 맵툴 세팅
	void mapToolSetup();
	void setMap();
	void save();
	void load();

	// 지형, 오브젝트 세팅
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	// 생성자, 소멸자
	mapToolScene() {}
	~mapToolScene() {}
};

