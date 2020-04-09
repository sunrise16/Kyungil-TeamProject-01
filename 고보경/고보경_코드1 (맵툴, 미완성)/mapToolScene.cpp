#include "stdafx.h"
#include "mapToolScene.h"

// 초기화 (init)
HRESULT mapToolScene::init()
{
	//배경맵
	IMAGEMANAGER->addImage("Bg", "Source/bkBlack.bmp", 64, 64);

	//맵툴 UI 배경
	IMAGEMANAGER->addImage("maptool_UI_House","Source/Scroll_UI_House.bmp", 904, 400, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("maptool_UI_Town", "Source/Scroll_UI_Town.bmp", 904, 400, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("maptool_UI_Boss", "Source/Scroll_UI_Boss.bmp", 904, 400, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("maptool_UI_Auto", "Source/Scroll_UI_Auto.bmp", 904, 400, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("maptool_UI_Char", "Source/Scroll_UI_Char.bmp", 904, 400, true, RGB(255,0,255));

	//맵툴 UI 선택 아이콘 (scrollX)
	IMAGEMANAGER->addFrameImage("maptool_UI_SCROLLS", "Source/Scrolls_UI250x60.bmp", 250, 60, 5, 1);

	//============================= TILE & OBJECT IMAGE =================================//

	// 타일 맵 이미지
	IMAGEMANAGER->addFrameImage("tilemap", "Source/타일맵3008x1536.bmp", 3008, 1536, 47, 24);
	// 상단 아이콘 버튼(세이브, 로드, 지우개, 리셋)
	IMAGEMANAGER->addImage("save_button", "Source/세이브버튼.bmp", 100, 40, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("load_button", "Source/로드버튼.bmp", 100, 40, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("eraser_button", "Source/지우개버튼.bmp", 100, 40, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("reset_button", "Source/리셋버튼.bmp", 100, 40, true, RGB(255,0,255));

	// 화살표 (스크롤하는 화살표)
	IMAGEMANAGER->addImage("arrow_right", "Source/오른쪽으로화살표.bmp", 50, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("arrow_left", "Source/왼쪽으로화살표.bmp", 50, 26, true, RGB(255, 0, 255));

	// 선택한 타일 표시하는 이미지
	IMAGEMANAGER->addFrameImage("select_tile", "Source/map_tool_UI_select.bmp", 128, 64, 2, 1);

	//스크롤 변수 초기화
	scrollX = scrollY = 0;

	// 맵툴 세팅
	this->mapToolSetup();

	// 현재 타일 초기화
	_currentTile.x = 0;
	_currentTile.y = 0;

	// 지형 그리기 속성으로 시작
	_ctrlSelect = CTRL_TERRAIN;
	// 메뉴 HOUSE로 시작
	_menu = MENU_HOUSE;

	//맵툴UI팝업변수(true가 되면 렉트가 올라옴)
	upUI = tileSelect = objectOn = eraseOn = false;

	return S_OK;
}

// 해제 (release)
void mapToolScene::release()
{
}

// 업데이트 (update)
void mapToolScene::update()
{
	if (objectOn)
	{
		_ctrlSelect = CTRL_OBJECT;
	}
	else
	{
		_ctrlSelect = CTRL_TERRAIN;
	}
	if (eraseOn)
	{
		_ctrlSelect = CTRL_ERASER;
	}
	//POINT setMapCoord(mouseCoord)에 현재 마우스 좌표를 넣고 setMapCoord 함수를 사용해서 윈도우 좌표계로 바꿔줍니다. (아직 미사용)
	mouseCoord.x = _ptMouse.x;
	mouseCoord.y = _ptMouse.y;

	//F2 버튼을 누르면 맵툴 UI가 올라옵니다
	if (INPUT->getKeyDown(VK_F2))
	{
		if (!upUI)
		{
			upUI = true;
		}
		else
			upUI = false;
	
	}
	
	//LBUTTON으로 타일맵에 세팅
	if (INPUT->getKey(VK_LBUTTON))
	{
		this->setMap();
	}
	// 오른쪽 샘플 타일 RECT 초기화
	for (int i = 0; i < TILEMAPSIZEY; i++)
	{
		for (int j = 0; j < TILEMAPSIZEX; j++)
		{
			_sampleTile[i * TILEMAPSIZEX + j].rc = RectMake(_rcMapSpace.left + j * TILESIZE, _rcMapSpace.top + i * TILESIZE, TILESIZE, TILESIZE);

			_sampleTile[i * TILEMAPSIZEX + j].terrainFrameX = j + scrollX;
			_sampleTile[i * TILEMAPSIZEX + j].terrainFrameY = i + scrollY;

		}
	}


	// 화면 카메라 스크롤 ( W, A, S, D ) => 제대로 작동 안해서 수정중
	//this->cameraScroll();

	this->mapUiAnimation();
	this->input();

	//계속 초기화 해야할 RECT들 모아둔것
	updateRect();
}

void mapToolScene::render()
{
	//카메라 내부로 들어와야 출력
	//IntersectRect용 임시 렉트인데 카메라용이라 아직 미사용
	RECT tmp;
	
	//맵(지형) 렌더
	// 인게임 화면 지형 출력
	for (int i = 0; i < MAP_TILEX * MAP_TILEY; i++)
	{
		//인게임 맵 지형 렌더 
		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);


		//인게임 맵 오브젝트 렌더
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);

	}
	
	//맵툴 UI 이미지 렌더
	switch (_menu)
	{
	case MENU_HOUSE:
		IMAGEMANAGER->render("maptool_UI_House", getMemDC(), _rcUIBg.left, _rcUIBg.top);
		break;
	case MENU_TOWN:
		IMAGEMANAGER->render("maptool_UI_Town", getMemDC(),  _rcUIBg.left, _rcUIBg.top);
		break;												 
	case MENU_BOSS:											 
		IMAGEMANAGER->render("maptool_UI_Boss", getMemDC(),  _rcUIBg.left, _rcUIBg.top);
		break;												 
	case MENU_AUTO:											 
		IMAGEMANAGER->render("maptool_UI_Auto", getMemDC(),  _rcUIBg.left, _rcUIBg.top);
		break;												 
	case MENU_CHAR:											 
		IMAGEMANAGER->render("maptool_UI_Char", getMemDC(),  _rcUIBg.left, _rcUIBg.top);
		break;
	}

	//메뉴 변경 아이콘(스크롤)
	IMAGEMANAGER->render("maptool_UI_SCROLLS", getMemDC(), _rcUIBg.left + 100, _rcUIBg.top - 30);
	IMAGEMANAGER->render("tilemap", getMemDC(), _rcMapSpace.left, _rcMapSpace.top, scrollX * 64, scrollY * 64, 704, MAP_HEIGHT);



	// 왼쪽 게임 화면 및 오른쪽 샘플 타일 RECT 출력
	if (INPUT->getToggleKey(VK_F1))
	{
		
		for (int i = 0; i < MAP_TILEX * MAP_TILEY; i++)
		{
			if (IntersectRect(&tmp, &_rcMCamera, &_tiles[i].rc))
			{

				if (_tiles[i].obj == OBJ_CARPET)
				{
					FrameRect(getMemDC(), _tiles[i].rc, RGB(255, 255, 0));
				}
				else if (_tiles[i].obj == OBJ_BLOCK1)
				{
					FrameRect(getMemDC(), _tiles[i].rc, RGB(255, 0, 0));
				}
				else if (_tiles[i].obj == OBJ_WALL)
				{
					FrameRect(getMemDC(), _tiles[i].rc, RGB(255, 0, 0));
				}
				else if (_tiles[i].obj == OBJ_BLOCKS)
				{
					FrameRect(getMemDC(), _tiles[i].rc, RGB(255, 0, 0));
				}
				else if (_tiles[i].terrain == TR_WALL)
				{
					FrameRect(getMemDC(), _tiles[i].rc, RGB(255, 0, 0));
				}
				else
				{
					FrameRect(getMemDC(), _tiles[i].rc, RGB(255, 255, 0));
				}

				
			}
		}

		//for (int i = 0; i < TILEMAPSIZEY * TILEMAPSIZEX; i++)
		//{
		//	FrameRect(getMemDC(), _sampleTile[i].rc, RGB(0, 255, 0));
		//}
		
	}

	//아이콘 RECT(고쳐야함)
	for (int i = 0; i < 5; i++)
	{
		FrameRect(getMemDC(), icon[i], RGB(255, 255, 0));
	}

	//타일 선택하면 그 타일 표시해주는 RECT
	if(upUI) FrameRect(getMemDC(), select_tile, RGB(0, 255, 255));
	
	
	// UI 렌더(항상 가장 아래에)
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(getMemDC(), &_rcSaveLoadBg, brush);

	FrameRect(getMemDC(), _rcUIBg, RGB(255, 0, 0));
	//UI 버튼 이미지 렌더
	IMAGEMANAGER->findImage("save_button")->render(getMemDC(), _rcSave.left, _rcSave.top);
	IMAGEMANAGER->findImage("load_button")->render(getMemDC(), _rcLoad.left, _rcLoad.top);
	IMAGEMANAGER->findImage("eraser_button")->render(getMemDC(), _rcEraser.left, _rcEraser.top);
	IMAGEMANAGER->findImage("reset_button")->render(getMemDC(), _rcReset.left, _rcReset.top);

	IMAGEMANAGER->findImage("arrow_left")->render(getMemDC(), _rcArrowLeft.left, _rcArrowLeft.top);
	IMAGEMANAGER->findImage("arrow_right")->render(getMemDC(), _rcArrowRight.left, _rcArrowRight.top);


	//RECT 표시용
	FrameRect(getMemDC(), _rcMapSpace, RGB(255, 0, 0));
	FrameRect(getMemDC(), _rcArrowLeft, RGB(255, 0, 0));
	FrameRect(getMemDC(), _rcArrowRight, RGB(255, 0, 0));
	FrameRect(getMemDC(), _rcObjectMap, RGB(255, 0, 0));
	FrameRect(getMemDC(), IMAGEMANAGER->findImage("maptool_UI_SCROLLS")->boundingBox(), RGB(255, 0, 0));


	//표시용 TEXT
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	sprintf(str, "LEFT: %d, TOP: %d", _rcMapSpace.left, _rcMapSpace.top);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
	sprintf(str, "X: %d, Y: %d", setMapCoord(mouseCoord).x, setMapCoord(mouseCoord).y);
	TextOut(getMemDC(), 20, 20, str, strlen(str));

}

// 맵툴 세팅
void mapToolScene::mapToolSetup()
{
	// 왼쪽 인게임 화면 RECT 초기화
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			_tiles[i * MAP_TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	// 타일맵 전체 세팅(초기화)
	for (int i = 0; i < MAP_TILEX * MAP_TILEY; i++)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}

	//==================================== 맵툴 RECT 초기화 ========================================//

	//배경 카메라 RECT 초기화(전체맵 정중앙)
	//_rcMCamera = RectMakeCenter(TILESIZEX / 2, TILESIZEY / 2, WINSIZEX, WINSIZEY);
	_rcMCamera = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	// 맵툴 UI의 RECT 초기화
	_rcUIBg = RectMakeCenter(WINSIZEX / 2, WINSIZEY + 150, 904, 400);
	_rcSaveLoadBg = RectMake(0, 0, WINSIZEX, 50);

	//하우스 타일맵 Rect 초기화
	_rcMapSpace = RectMake(_rcUIBg.left + 100, _rcUIBg.top + 75, 704, MAP_HEIGHT);

	//오브젝트 맵 켜는 버튼
	_rcObjectMap = RectMake(_rcUIBg.right - 80, _rcUIBg.top + 50, 20, 20);

	_rcArrowLeft = RectMake(_rcUIBg.left + 90, _rcUIBg.bottom - 65, 40, 20);
	_rcArrowRight = RectMake(_rcUIBg.right - 130, _rcUIBg.bottom - 65, 40, 20);



	//아이콘 렉트 초기화
	for (int i = 0; i < 5; i++)
	{
		icon[i] = RectMakeCenter(125 + _rcUIBg.left + (50 * i), _rcUIBg.top, 50, 50);
	}

	// 컨트롤 버튼 RECT 위치 초기화
	_rcSave = RectMake(WINSIZEX - 210 , 5, 100, 40);
	_rcLoad = RectMake(WINSIZEX - 105,  5, 100, 40);
	_rcEraser = RectMake(WINSIZEX - 315, 5, 100, 40);
	_rcReset = RectMake(WINSIZEX - 420, 5, 100, 40);
	
}

void mapToolScene::setMap()
{
	for (int i = 0; i < SAMPLE_TILEX * SAMPLE_TILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			if (eraseOn) eraseOn = false;
			_currentTile.x = _sampleTile[i].terrainFrameX;
			_currentTile.y = _sampleTile[i].terrainFrameY;
			currentCtrl = _ctrlSelect;
			select_tile = RectMake(_sampleTile[i].rc.left, _sampleTile[i].rc.top, 64, 64);
			break;
		}
	}
	
	// 인게임 화면과 RECT 간의 충돌 처리
	for (int i = 0; i < MAP_TILEX * MAP_TILEY; i++)
	{
		if (!(PtInRect(&_rcUIBg, _ptMouse) || PtInRect(&_rcSaveLoadBg, _ptMouse)
			|| PtInRect(&IMAGEMANAGER->findImage("maptool_UI_SCROLLS")->boundingBox(), _ptMouse)))
		{
			if (PtInRect(&_tiles[i].rc, setMapCoord(mouseCoord)))
			{
				if (_ctrlSelect == CTRL_ERASER)
				{
					_tiles[i].objFrameX = 0;
					_tiles[i].objFrameY = 0;
					_tiles[i].obj = OBJ_NONE;
				}
				else
				{
					// 현재 버튼에 따라 타일 생성
					if (currentCtrl == CTRL_TERRAIN)
					{
						_tiles[i].terrainFrameX = _currentTile.x;
						_tiles[i].terrainFrameY = _currentTile.y;
						_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
					}

					if (currentCtrl == CTRL_OBJECT)
					{
						_tiles[i].objFrameX = _currentTile.x;
						_tiles[i].objFrameY = _currentTile.y;
						_tiles[i].obj = objectSelect(_currentTile.x, _currentTile.y);
					}
				}
				
			}
		}
	}

}
void mapToolScene::save()
{
	HANDLE file;
	DWORD write;

	// 파일 세이브
	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tiles, sizeof(tagTile) * MAP_TILEX * MAP_TILEY, &write, NULL);
	CloseHandle(file);

	textOut(getMemDC(), WINSIZEX, WINSIZEY, "SAVE COMPLETE", RGB(0, 255, 0));
}

void mapToolScene::load()
{
	HANDLE file;
	DWORD read;

	// 파일 로드
	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * MAP_TILEX * MAP_TILEY, &read, NULL);
	CloseHandle(file);

	textOut(getMemDC(), WINSIZEX, WINSIZEY, "LOAD COMPLETE", RGB(255, 0, 0));
}

void mapToolScene::updateRect()
{
	// 아이콘 렉트 초기화
	for (int i = 0; i < 5; i++)
	{
		icon[i] = RectMakeCenter(125 + _rcUIBg.left + (50 * i), _rcUIBg.top, 50, 50);
	}

	IMAGEMANAGER->findImage("maptool_UI_SCROLLS")->setX(icon[0].left);
	IMAGEMANAGER->findImage("maptool_UI_SCROLLS")->setY(icon[0].top);

	_rcMapSpace = RectMake(_rcUIBg.left + 100, _rcUIBg.top + 75, 704, MAP_HEIGHT);
	_rcArrowLeft = RectMake(_rcUIBg.left + 90, _rcUIBg.bottom - 65, 40, 20);
	_rcArrowRight = RectMake(_rcUIBg.right - 130, _rcUIBg.bottom - 65, 40, 20);
	_rcObjectMap = RectMake(_rcUIBg.right - 130, _rcUIBg.top + 50, 20, 20);

}

void mapToolScene::reset()
{
	// 왼쪽 인게임 화면 모두 잔디가 기본 타일이 되도록 세팅
	for (int i = 0; i < MAP_TILEX * MAP_TILEY; i++)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}
}

void mapToolScene::cameraScroll()
{
	if (INPUT->getKey('A'))
	{
		_rcMCamera.left -= 5;
		_rcMCamera.right -= 5;
	}
	if (INPUT->getKey('D'))
	{
		_rcMCamera.left += 5;
		_rcMCamera.right += 5;
	}
	if (INPUT->getKey('W'))
	{
		_rcMCamera.top -= 5;
		_rcMCamera.bottom -= 5;
	}
	if (INPUT->getKey('S'))
	{
		_rcMCamera.top += 5;
		_rcMCamera.bottom += 5;
	}

	if (_rcMCamera.left < 0)
	{
		_rcMCamera.left = 0;
		_rcMCamera.right = _rcMCamera.left + WINSIZEX;
	}
	else if (_rcMCamera.right > TILESIZEX)
	{
		_rcMCamera.right = TILESIZEX;
		_rcMCamera.left = _rcMCamera.right - WINSIZEX;
	}

	if (_rcMCamera.top < 0)
	{
		_rcMCamera.top = 0;
		_rcMCamera.bottom = _rcMCamera.top + WINSIZEY;
	}
	else if (_rcMCamera.bottom > TILESIZEY)
	{
		_rcMCamera.bottom = TILESIZEY;
		_rcMCamera.top = _rcMCamera.bottom - WINSIZEY;
	}

	
}

// 지형 세팅 ( 아 직 안 함 )..
TERRAIN mapToolScene::terrainSelect(int frameX, int frameY)
{
	// 시멘트
	if (frameX >= 3 && frameY < 4)
	{
		return TR_WALL;
	}
	// 잔디
	if (frameX == 3)
	{
		return TR_GRASS;
	}
	// 물
	if (frameX == 4)
	{
		return TR_WATER;
	}

	// 그 이외일 경우 땅으로 기본값 설정
	return TR_GROUND;
}
// 오브젝트 세팅
OBJECT mapToolScene::objectSelect(int frameX, int frameY)
{
	//// 시멘트
	if (frameX <= 28)
	{
		return OBJ_CARPET;
	}
	// 땅
	if ((frameX > 28 && frameX <= 32) || (frameX >= 32 && frameX < 36))
	{
		return OBJ_BLOCK1;
	}
	// 잔디
	if (frameX == 3)
	{
		return OBJ_BLOCK2;
	}
	// 물
	if (frameX == 4)
	{
		return OBJ_BLOCK3;
	}

	return OBJ_BLOCKS;
}

//input(feat. ptInRect) 모음집 ==> 그냥 update에 ptInRect 추가하면 다른거 작동 안됩니다...
void mapToolScene::input()
{
	if (INPUT->getKeyDown(VK_LBUTTON))
	{

		if (PtInRect(&_rcObjectMap, _ptMouse))
		{
			if (!objectOn)
			{
				objectOn = true;
				switch (_menu)
				{
				case MENU_HOUSE:
					scrollY = 12;
					break;
				case MENU_TOWN:
					scrollY = 16;
					break;
				case MENU_BOSS:
					scrollY = 20;
					break;
				case MENU_AUTO:
					break;
				case MENU_CHAR:
					break;
				}
			}
			else
			{
				objectOn = false;
				switch (_menu)
				{
				case MENU_HOUSE:
					scrollY = 0;
					break;
				case MENU_TOWN:
					scrollY = 4;
					break;
				case MENU_BOSS:
					scrollY = 8;
					break;
				case MENU_AUTO:
					break;
				case MENU_CHAR:
					break;
				}
			}
		}

		// 스크롤 X, 스크롤 Y (아직 제대로 예외처리 안함)
		if (PtInRect(&_rcArrowLeft, _ptMouse))
		{
			if (scrollX > 0)
			{
				scrollX--;
			}
		}
		else if (PtInRect(&_rcArrowRight, _ptMouse))
		{
			if (scrollY <= 11)
			{
				if (scrollX < 21)
					scrollX++;
			}
			else
			{
				if (scrollX < 36)
					scrollX++;
			}
		}

		// 위쪽 UI 입력 처리
		if (PtInRect(&_rcSave, _ptMouse))
		{
			//_ctrlSelect = CTRL_SAVE;
			this->save();
		}
		else if (PtInRect(&_rcLoad, _ptMouse))
		{
			//_ctrlSelect = CTRL_LOAD;
			this->load();
		}
		else if (PtInRect(&_rcEraser, _ptMouse))
		{
			eraseOn = true;
		}
		else if (PtInRect(&_rcReset, _ptMouse))
		{
			this->reset();
		}

		if (PtInRect(&icon[0], _ptMouse))
		{
			scrollX = 0;
			scrollY = 0;
			_menu = MENU_HOUSE;
			if (!upUI)
				upUI = true;
			if(objectOn)
				objectOn = false;
		}
		else if (PtInRect(&icon[1], _ptMouse))
		{
			scrollX = 0;
			scrollY = 4;
			_menu = MENU_TOWN;
			if (!upUI)
				upUI = true;
			if (objectOn)
				objectOn = false;
		}
		else if (PtInRect(&icon[2], _ptMouse))
		{
			scrollX = 0;
			scrollY = 8;
			_menu = MENU_BOSS;
			if (!upUI)
				upUI = true;
			if (objectOn)
				objectOn = false;
		}
		else if (PtInRect(&icon[3], _ptMouse))
		{
			scrollX = 0;
			_menu = MENU_AUTO;
			if (!upUI)
				upUI = true;
			if (objectOn)
				objectOn = false;
		}
		else if (PtInRect(&icon[4], _ptMouse))
		{
			scrollX = 0;
			_menu = MENU_CHAR;
			if (!upUI)
				upUI = true;
			if (objectOn)
				objectOn = false;
		}
		
	}

}

//맵툴 UI 팝업 애니메이션
void mapToolScene::mapUiAnimation()
{
	if (upUI)
	{
		if (_rcUIBg.top > WINSIZEY / 2 + 80)
		{
			_rcUIBg.top -= 10;
			tileSelect = true;
		}
		_rcUIBg.bottom = _rcUIBg.top + IMAGEMANAGER->findImage("maptool_UI_House")->getHeight();
	}
	else
	{
		if (_rcUIBg.top < WINSIZEY - 50)
		{
			_rcUIBg.top += 10;
			tileSelect = false;
			_rcUIBg.bottom = _rcUIBg.top + IMAGEMANAGER->findImage("maptool_UI_House")->getHeight();
		}
	}


}

//아직 사용X
POINT mapToolScene::setMapCoord(POINT mouseP)
{
	mouseP.x = mouseP.x + _rcMCamera.left;
	mouseP.y = mouseP.y + _rcMCamera.top;

	return mouseP;
}
