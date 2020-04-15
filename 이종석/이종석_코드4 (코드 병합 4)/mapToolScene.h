#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define MAP_HEIGHT 256			// 맵의 길이

// 카메라 구조체
struct CAMERA
{
	float x, y;
	RECT rc;
};

//===========================================================================//
//
//	TAB 키 : 맵툴 UI 올라오고 내려가는 처리
//	E키 : ERASER키 (오브젝트 지우는 키)		==> 키가 씹히는 경우 존재
//	R키 : ERASER키 (타일 지우는 키)		==> 키가 씹히는 경우 존재
//	W, A, S, D : 화면 이동키
//	
// ***** 샘플 타일에서 드래그 한 후에 계속 클릭해서 생성 가능 (ptMouse 기준으로 생성됨)
// ***** 드래그 푸는 키 : SPACE 키
//
// 타일(_tiles)에서 드래그 하면 그 범위에 선택한 샘플 타일 1개가 드래그 범위에 복사됨.
// 샘플 타일(_sampleTile)에서 드래그 하면 그 범위만큼 타일에 입힐 수 있다.
//
//===========================================================================//

// mapToolScene 클래스
class mapToolScene : public gameNode
{
private:
	// 객체 관련
	// 타일 관련
	tagTile _tiles[MAP_TILEY][MAP_TILEX];					// 인게임 화면에 사용되는 타일 (총 400개)
	tagSampleTile _sampleTile[SAMPLE_TILEX][SAMPLE_TILEY];	// 샘플 타일 (총 160개)
	tagCurrentTile _currentTile;							// 현재 타일
	// 드래그 관련
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
	vector<tagSampleTile> _dragT;			// 드래그한 샘플 타일 이미지 좌표값 저장하는 벡터
	RECT _drag;								// 드래그용 렉트 (샘플 타일 드래그하면 이 렉트가 마우스 좌표에 찍힘)
	// UI 관련
	RECT _rcSave;							// 세이브 메뉴칸
	RECT _rcSave1;							// 세이브 저장소 1
	RECT _rcSave2;							// 세이브 저장소 2
	RECT _rcSave3;							// 세이브 저장소 3
	RECT _rcLoad;							// 로드 메뉴칸
	RECT _rcLoad1;							// 로드 저장소 1
	RECT _rcLoad2;							// 로드 저장소 2
	RECT _rcLoad3;							// 로드 저장소 3
	RECT _rcTerrain;						// 지형
	RECT _rcObject;							// 오브젝트
	RECT _rcEraser;							// 지우개 (오브젝트만 지우고 지형은 덮어 씌움)
	RECT _rcReset;							// 리셋
	RECT _rcMinimap;						// 미니맵 전체 RECT
	RECT _rcMinimap_C;						// 미니맵 안 카메라 RECT
	CAMERA _rcMCamera;						// 맵툴 카메라 RECT
	// UI 관련 (아이콘)
	RECT _rcSaveBg;
	RECT _rcLoadBg;
	RECT _rcUIBg;							// 맵툴 UI 배경 RECT
	RECT _rcSaveLoadBg;
	RECT _rcMapSpace;
	RECT _rcArrowLeft;
	RECT _rcArrowRight;
	RECT icon[5];							// 메뉴 선택 아이콘용 RECT 배열
	RECT mouseRect;							// 마우스 드래그하면 생성되는 RECT
	RECT selectTiles;						// 선택한 타일 표시하는 RECT
	RECT tmp;								// 화면 출력(테스트)용 임시 변수
	POINT mouseT;							// 드래그용 마우스 포인터
	RECT select_tile;						// 선택한 타일 표시 RECT

	// 변수 관련
	MAPTOOL_MENU _menu;						// 메뉴 상태
	CTRL currentCtrl;						// 현재 컨트롤 상태
	CTRL _ctrlSelect;						// 현재 컨트롤 상태 판별
	bool upUI;								// 맵툴 UI 팝업 변수
	bool objectOn;							// OBJ 버튼 누르면 해당 메뉴의 OBJ 목록으로 간다.
	bool eraseOn;							// ERASER 켜졌는가
	bool saveOn;							// SAVE 버튼 눌렀을때 켜짐
	bool loadOn;							// LOAD 버튼 눌렀을때 켜짐
	bool tilerectOn;						// 드래그용
	bool dragOnSample;						// 샘플 타일 드래그 체크
	bool dragSelectedSample;				// 샘플 타일 드래그 선택
	bool dragOn;							// 샘플 타일 드래그 범위 그리는용
	bool noSample;							// MENU_AUTO, MENU_CHAR용
	char str[1024];							// 문자열
	int scrollX;							// 타일맵 스크롤
	int scrollY;							// 메뉴변경
	int camX, camY;							// 카메라 X, Y 좌표값

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

	// 계속 업데이트 할 RECT들 모음
	void updateRect();

	// 맵툴 UI 팝업 애니메이션
	void mapUiAnimation();

	// 지형, 오브젝트 세팅
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	// 키입력 (VK_LBUTTON들 모여있음 (다른 키도 있음))
	void input();
	void drag();

	// 세이브 로드할때 생성되는 RECT 애니메이션
	void saveloadRectSet();

	// 생성자, 소멸자
	mapToolScene() {}
	~mapToolScene() {}
};