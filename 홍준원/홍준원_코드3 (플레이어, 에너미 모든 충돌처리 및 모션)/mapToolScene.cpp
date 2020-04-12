#include "stdafx.h"
#include "mapToolScene.h"

// 초기화 (init)
HRESULT mapToolScene::init()
{
	// 타일맵 이미지 초기화
	//IMAGEMANAGER->addFrameImage("Tilemap", "Source/Tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);

	// 맵툴 세팅
	//this->mapToolSetup();

	// 현재 타일 초기화 (지형 = 잔디)
	//_currentTile.x = 3;
	//_currentTile.y = 0;

	// 지형 그리기 속성으로 시작
	//_ctrlSelect = CTRL_TERRAIN;

	return S_OK;
}

// 해제 (release)
void mapToolScene::release()
{
}

// 업데이트 (update)
void mapToolScene::update()
{
	// 타일 배치
	//if (INPUT->getKey(VK_LBUTTON))
	//{
	//	this->setMap();
	//}
	//
	//// 버튼 누르기
	//if (INPUT->getKeyDown(VK_LBUTTON))
	//{
	//	if (PtInRect(&_rcSave, _ptMouse))
	//	{
	//		_ctrlSelect = CTRL_SAVE;
	//		this->save();
	//	}
	//	if (PtInRect(&_rcLoad, _ptMouse))
	//	{
	//		_ctrlSelect = CTRL_LOAD;
	//		this->load();
	//	}
	//	if (PtInRect(&_rcTerrain, _ptMouse))
	//	{
	//		_ctrlSelect = CTRL_TERRAIN;
	//	}
	//	if (PtInRect(&_rcObject, _ptMouse))
	//	{
	//		_ctrlSelect = CTRL_OBJECT;
	//	}
	//	if (PtInRect(&_rcEraser, _ptMouse))
	//	{
	//		_ctrlSelect = CTRL_ERASER;
	//	}
	//}
}

// 렌더 (render)
void mapToolScene::render()
{
	// 타일맵 이미지 전체화면 우측 상단에 배치
//IMAGEMANAGER->render("Tilemap", getMemDC(), 660, 0);
//
//// 인게임 화면 지형 출력
//for (int i = 0; i < TILEX * TILEY; i++)
//{
//	IMAGEMANAGER->frameRender("Tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
//}
//
//// 인게임 화면 오브젝트 출력
//for (int i = 0; i < TILEX * TILEY; i++)
//{
//	if (_tiles[i].obj == OBJ_NONE) continue;
//
//	IMAGEMANAGER->frameRender("Tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
//		_tiles[i].objFrameX, _tiles[i].objFrameY);
//}
//
//// 왼쪽 게임 화면 및 오른쪽 샘플 타일 RECT 출력
//if (INPUT->getToggleKey(VK_F1))
//{
//	for (int i = 0; i < TILEX * TILEY; i++)
//	{
//		Rectangle(getMemDC(), _tiles[i].rc);
//		//FrameRect(getMemDC(), _tiles[i].rc, RGB(255, 255, 0));
//	}
//
//	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
//	{
//		//Rectangle(getMemDC(), _sampleTile[i].rc);
//		FrameRect(getMemDC(), _sampleTile[i].rc, RGB(255, 255, 0));
//	}
//}
//
//// 컨트롤 버튼 RECT 출력
//Rectangle(getMemDC(), _rcSave);
//Rectangle(getMemDC(), _rcLoad);
//Rectangle(getMemDC(), _rcTerrain);
//Rectangle(getMemDC(), _rcObject);
//Rectangle(getMemDC(), _rcEraser);
//
//// 버튼 RECT 텍스트 출력
//SetTextColor(getMemDC(), RGB(255, 0, 0));
//TextOut(getMemDC(), _rcSave.left + 20, _rcSave.top + 20, "세이브", strlen("세이브"));
//TextOut(getMemDC(), _rcLoad.left + 20, _rcLoad.top + 20, "로드", strlen("로드"));
//TextOut(getMemDC(), _rcTerrain.left + 20, _rcTerrain.top + 20, "지형", strlen("지형"));
//TextOut(getMemDC(), _rcObject.left + 20, _rcObject.top + 20, "오브젝트", strlen("오브젝트"));
//TextOut(getMemDC(), _rcEraser.left + 20, _rcEraser.top + 20, "지우개", strlen("지우개"));
}

// 맵툴 세팅
//void mapToolScene::mapToolSetup()
//{
//	// 왼쪽 인게임 화면 RECT 초기화
//	for (int i = 0; i < TILEY; i++)
//	{
//		for (int j = 0; j < TILEX; j++)
//		{
//			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
//		}
//	}
//
//	// 오른쪽 샘플 타일 RECT 초기화
//	for (int i = 0; i < SAMPLETILEY; i++)
//	{
//		for (int j = 0; j < SAMPLETILEX; j++)
//		{
//			_sampleTile[i * SAMPLETILEX + j].rc = RectMake(660 + j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
//		
//			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
//			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;
//		}
//	}
//
//	// 왼쪽 인게임 화면 모두 잔디가 기본 타일이 되도록 세팅
//	for (int i = 0; i < TILEX * TILEY; i++)
//	{
//		_tiles[i].terrainFrameX = 3;
//		_tiles[i].terrainFrameY = 0;
//		_tiles[i].objFrameX = 0;
//		_tiles[i].objFrameY = 0;
//		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
//		_tiles[i].obj = OBJ_NONE;
//	}
//	// 컨트롤 버튼 RECT 위치 초기화
//	_rcSave = RectMake(660, 400, 100, 50);
//	_rcLoad = RectMake(660 + 100, 400, 100, 50);
//	_rcTerrain = RectMake(660, 400 + 100, 100, 50);
//	_rcObject = RectMake(660 + 100, 400 + 100, 100, 50);
//	_rcEraser = RectMake(660 + 200, 400 + 100, 100, 50);
//}
//void mapToolScene::setMap()
//{
//	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
//	{
//		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
//		{
//			_currentTile.x = _sampleTile[i].terrainFrameX;
//			_currentTile.y = _sampleTile[i].terrainFrameY;
//			break;
//		}
//	}
//
//	// 인게임 화면과 RECT 간의 충돌 처리
//	for (int i = 0; i < TILEX * TILEY; i++)
//	{
//		if (PtInRect(&_tiles[i].rc, _ptMouse))
//		{
//			// 현재 버튼에 따라 타일 생성
//			if (_ctrlSelect == CTRL_TERRAIN)
//			{
//				_tiles[i].terrainFrameX = _currentTile.x;
//				_tiles[i].terrainFrameY = _currentTile.y;
//				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
//			}
//			if (_ctrlSelect == CTRL_OBJECT)
//			{
//				_tiles[i].objFrameX = _currentTile.x;
//				_tiles[i].objFrameY = _currentTile.y;
//				_tiles[i].obj = objectSelect(_currentTile.x, _currentTile.y);
//			}
//			if (_ctrlSelect == CTRL_ERASER)
//			{
//				_tiles[i].objFrameX = 0;
//				_tiles[i].objFrameY = 0;
//				_tiles[i].obj = OBJ_NONE;
//			}
//		}
//	}
//
//}
//void mapToolScene::save()
//{
//	HANDLE file;
//	DWORD write;
//
//	// 파일 세이브
//	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
//		FILE_ATTRIBUTE_NORMAL, NULL);
//	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
//	CloseHandle(file);
//}
//void mapToolScene::load()
//{
//	HANDLE file;
//	DWORD read;
//
//	// 파일 로드
//	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL, NULL);
//	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
//	CloseHandle(file);
//}
//
//// 지형 세팅
//TERRAIN mapToolScene::terrainSelect(int frameX, int frameY)
//{
//	// 시멘트
//	if (frameX == 1 && frameY == 0)
//	{
//		return TR_CEMENT;
//	}
//	// 땅
//	if (frameX == 2 && frameY == 0)
//	{
//		return TR_GROUND;
//	}
//	// 잔디
//	if (frameX == 3 && frameY == 0)
//	{
//		return TR_GRASS;
//	}
//	// 물
//	if (frameX == 4 && frameY == 0)
//	{
//		return TR_WATER;
//	}
//
//	// 그 이외일 경우 땅으로 기본값 설정
//	return TR_GROUND;
//}
//// 오브젝트 세팅
//OBJECT mapToolScene::objectSelect(int frameX, int frameY)
//{
//	return OBJ_BLOCKS;
//}
