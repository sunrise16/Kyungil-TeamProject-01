#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define MAP_HEIGHT 256

struct CAMERA
{
	float x, y;
	RECT rc;
};

// mapToolScene 클래스
class mapToolScene : public gameNode
{
private:
	// 객체 관련
	tagTile _tiles[MAP_TILEY * MAP_TILEX];					// 인게임 화면에 사용되는 타일 (총 400개)
	tagSampleTile _sampleTile[SAMPLE_TILEX][SAMPLE_TILEY];	// 샘플 타일 (총 160개)
	tagCurrentTile _currentTile;							// 현재 타일
	
	//드래그용
	int _dragIndexStartX;
	int _dragIndexStartY;
	int _dragIndexEndX;
	int _dragIndexEndY;
	int _dragRectWidth;
	int _dragRectHeight;


	//메뉴 구분 구분
	MAPTOOL_MENU _menu;

	//UI RECT
	RECT _rcSave;											// 세이브
	RECT _rcSave1;											// 세이브
	RECT _rcSave2;											// 세이브
	RECT _rcSave3;											// 세이브
	
	RECT _rcLoad;											// 로드
	RECT _rcLoad1;											// 로드
	RECT _rcLoad2;											// 로드
	RECT _rcLoad3;											// 로드
	
	RECT _rcTerrain;										// 지형
	RECT _rcObject;											// 오브젝트
	RECT _rcEraser;							// 지우개 (오브젝트만 지우고 지형은 덮어씌움)
	RECT _rcReset;							// 지우개 (오브젝트만 지우고 지형은 덮어씌움)
	
	RECT _rcMinimap;
	RECT _rcMinimap_C;
	
	CAMERA _rcMCamera;//맵툴 카메라 RECT
	
	RECT _BG;
	RECT _rcSaveBg;
	RECT _rcLoadBg;
	RECT _rcUIBg;	// 맵툴UI배경RECT
	RECT _rcSaveLoadBg;
	RECT _rcMapSpace;
	RECT _rcArrowLeft;
	RECT _rcArrowRight;
	RECT icon[5];

	RECT mouseRect;
	RECT selectTiles;

	//BRUSH
	HBRUSH water;
	HBRUSH grass;
	HBRUSH block;
	HBRUSH ground;


	//마우스의 포인터 좌표
	POINT mouseCoord;
	
	// UI배경 옮길 임시 마우스 포인트
	POINT tmp;
	POINT mouseT;

	// 선택한 타일 표시 RECT
	RECT select_tile;

	bool upUI;	// 맵툴UI팝업변수
	bool tileSelect;
	bool objectOn;
	bool eraseOn;
	bool saveOn;
	bool loadOn;
	bool tilerectOn;
	bool dragOnSample;

	char str[128];
	int scrollX; // 타일맵 스크롤
	int scrollY; // 메뉴변경
	int camX, camY;
	int idX, idY;

	CTRL currentCtrl;

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
	void reset();

	void updateRect();
	//맵툴UI 팝업 애니메이션 함수
	void mapUiAnimation();

	// 지형, 오브젝트 세팅
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	void input();
	//예외처리용(ex > UI배경 뒤에 타일 그려지거나 UI icon 뒤에 Rect 그려지는 현상 예외처리)

	void setSampleTile(int indexX, int indexY);

	void saveloadRectSet();

	// 생성자, 소멸자
	mapToolScene() {}
	~mapToolScene() {}
};

