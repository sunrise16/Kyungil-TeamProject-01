#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define MAP_HEIGHT 256

struct CAMERA {
	float x, y;
	RECT rc;
};

// mapToolScene 클래스
class mapToolScene : public gameNode
{
private:
	// 객체 관련
	tagTile _tiles[MAP_TILEY][MAP_TILEX];					// 인게임 화면에 사용되는 타일 (총 400개)
	tagSampleTile _sampleTile[SAMPLE_TILEX][SAMPLE_TILEY];	// 샘플 타일 (총 160개)
	tagCurrentTile _currentTile;							// 현재 타일

	//드래그용
	int _dragIndexStartX;
	int _dragIndexStartY;
	int _dragIndexEndX;
	int _dragIndexEndY;
	int _dragRectStartLeft;
	int _dragRectStartTop;
	int _dragRectStartRight;
	int _dragRectStartBottom;
	int _dragRectWidth;
	int _dragRectHeight;

	tagSampleTile _dragTiles;
	tagSampleTile _dragTile[TILEMAPSIZEY][TILEMAPSIZEX];


	//메뉴 구분 구분
	MAPTOOL_MENU _menu;

	//UI RECT
	RECT _rcSave;							// 세이브
	RECT _rcSave1;							// 세이브
	RECT _rcSave2;							// 세이브
	RECT _rcSave3;							// 세이브
	
	RECT _rcLoad;							// 로드
	RECT _rcLoad1;							// 로드
	RECT _rcLoad2;							// 로드
	RECT _rcLoad3;							// 로드
	
	RECT _rcTerrain;						// 지형
	RECT _rcObject;							// 오브젝트
	RECT _rcEraser;							// 지우개 (오브젝트만 지우고 지형은 덮어씌움)
	RECT _rcReset;							// 리셋
	
	RECT _rcMinimap;						// 미니맵 전체 RECT
	RECT _rcMinimap_C;						// 미니맵 안 카메라 RECT
	
	CAMERA _rcMCamera;//맵툴 카메라 RECT
	
	// UI ICON용 RECT
	RECT _rcSaveBg;
	RECT _rcLoadBg;
	RECT _rcUIBg;		// 맵툴UI배경RECT
	RECT _rcSaveLoadBg;
	RECT _rcMapSpace;
	RECT _rcArrowLeft;
	RECT _rcArrowRight;
	RECT icon[5];		// 메뉴 선택 아이콘용 RECT 배열


	RECT mouseRect;		// 마우스 드래그하면 생성되는 RECT
	RECT selectTiles;	// 선택한 타일 표시하는 RECT

	//화면 출력(테스트)용 임시 변수
	RECT tmp;
	// 드래그용 마우스 포인터
	POINT mouseT;

	// 선택한 타일 표시 RECT
	RECT select_tile;

	bool upUI;			// 맵툴UI팝업변수
	bool objectOn;		// OBJ 버튼 누르면 해당 메뉴의 OBJ 목록으로 간다.
	bool eraseOn;		// ERASER 켜졌는가
	bool saveOn;		// SAVE 버튼 눌렀을때 켜짐
	bool loadOn;		// LOAD 버튼 눌렀을때 켜짐
	bool tilerectOn;	// 드래그용
	bool dragOnSample;	
	bool dragSelectedSample;	
	bool dragOn;
	bool noSample;		// MENU_AUTO, MENU_CHAR용

	char str[128];
	int scrollX; // 타일맵 스크롤
	int scrollY; // 메뉴변경
	int camX, camY;

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

	// 계속 Update() 에서 업뎃 해줘야 하는 RECT들 모음
	void updateRect();

	//맵툴UI 팝업 애니메이션 함수
	void mapUiAnimation();

	// 지형, 오브젝트 세팅
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	// 키입력 (VK_LBUTTON들 모여있음 (다른 키도 있음))
	void input();
	void drag();

	// 세이브 로드할때 생성되는 RECT들 ANIMATION용 함수
	void saveloadRectSet();

	// 생성자, 소멸자
	mapToolScene() {}
	~mapToolScene() {}
};

