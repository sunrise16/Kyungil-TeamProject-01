#include "stdafx.h"
#include "mapToolScene.h"

// �ʱ�ȭ (init)
HRESULT mapToolScene::init()
{
	//����
	IMAGEMANAGER->addImage("Bg", "Source/bkBlack.bmp", 64, 64);

	//���� UI ���
	IMAGEMANAGER->addImage("maptool_UI_House","Source/Scroll_UI_House.bmp", 904, 400, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("maptool_UI_Town", "Source/Scroll_UI_Town.bmp", 904, 400, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("maptool_UI_Boss", "Source/Scroll_UI_Boss.bmp", 904, 400, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("maptool_UI_Auto", "Source/Scroll_UI_Auto.bmp", 904, 400, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("maptool_UI_Char", "Source/Scroll_UI_Char.bmp", 904, 400, true, RGB(255,0,255));

	//���� UI ���� ������ (scrollX)
	IMAGEMANAGER->addFrameImage("maptool_UI_SCROLLS", "Source/Scrolls_UI250x60.bmp", 250, 60, 5, 1);

	//============================= TILE & OBJECT IMAGE =================================//

	// Ÿ�� �� �̹���
	IMAGEMANAGER->addFrameImage("tilemap", "Source/Ÿ�ϸ�3008x1536.bmp", 3008, 1536, 47, 24);
	// ��� ������ ��ư(���̺�, �ε�, ���찳, ����)
	IMAGEMANAGER->addImage("save_button", "Source/���̺��ư.bmp", 100, 40, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("load_button", "Source/�ε��ư.bmp", 100, 40, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("eraser_button", "Source/���찳��ư.bmp", 100, 40, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("reset_button", "Source/���¹�ư.bmp", 100, 40, true, RGB(255,0,255));

	// ȭ��ǥ (��ũ���ϴ� ȭ��ǥ)
	IMAGEMANAGER->addImage("arrow_right", "Source/����������ȭ��ǥ.bmp", 50, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("arrow_left", "Source/��������ȭ��ǥ.bmp", 50, 26, true, RGB(255, 0, 255));

	// ������ Ÿ�� ǥ���ϴ� �̹���
	IMAGEMANAGER->addFrameImage("select_tile", "Source/map_tool_UI_select.bmp", 128, 64, 2, 1);

	//��ũ�� ���� �ʱ�ȭ
	scrollX = scrollY = 0;

	// ���� ����
	this->mapToolSetup();

	// ���� Ÿ�� �ʱ�ȭ
	_currentTile.x = 0;
	_currentTile.y = 0;

	// ���� �׸��� �Ӽ����� ����
	_ctrlSelect = CTRL_TERRAIN;
	// �޴� HOUSE�� ����
	_menu = MENU_HOUSE;

	//����UI�˾�����(true�� �Ǹ� ��Ʈ�� �ö��)
	upUI = tileSelect = objectOn = eraseOn = false;

	return S_OK;
}

// ���� (release)
void mapToolScene::release()
{
}

// ������Ʈ (update)
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
	//POINT setMapCoord(mouseCoord)�� ���� ���콺 ��ǥ�� �ְ� setMapCoord �Լ��� ����ؼ� ������ ��ǥ��� �ٲ��ݴϴ�. (���� �̻��)
	mouseCoord.x = _ptMouse.x;
	mouseCoord.y = _ptMouse.y;

	//F2 ��ư�� ������ ���� UI�� �ö�ɴϴ�
	if (INPUT->getKeyDown(VK_F2))
	{
		if (!upUI)
		{
			upUI = true;
		}
		else
			upUI = false;
	
	}
	
	//LBUTTON���� Ÿ�ϸʿ� ����
	if (INPUT->getKey(VK_LBUTTON))
	{
		this->setMap();
	}
	// ������ ���� Ÿ�� RECT �ʱ�ȭ
	for (int i = 0; i < TILEMAPSIZEY; i++)
	{
		for (int j = 0; j < TILEMAPSIZEX; j++)
		{
			_sampleTile[i * TILEMAPSIZEX + j].rc = RectMake(_rcMapSpace.left + j * TILESIZE, _rcMapSpace.top + i * TILESIZE, TILESIZE, TILESIZE);

			_sampleTile[i * TILEMAPSIZEX + j].terrainFrameX = j + scrollX;
			_sampleTile[i * TILEMAPSIZEX + j].terrainFrameY = i + scrollY;

		}
	}


	// ȭ�� ī�޶� ��ũ�� ( W, A, S, D ) => ����� �۵� ���ؼ� ������
	//this->cameraScroll();

	this->mapUiAnimation();
	this->input();

	//��� �ʱ�ȭ �ؾ��� RECT�� ��Ƶа�
	updateRect();
}

void mapToolScene::render()
{
	//ī�޶� ���η� ���;� ���
	//IntersectRect�� �ӽ� ��Ʈ�ε� ī�޶���̶� ���� �̻��
	RECT tmp;
	
	//��(����) ����
	// �ΰ��� ȭ�� ���� ���
	for (int i = 0; i < MAP_TILEX * MAP_TILEY; i++)
	{
		//�ΰ��� �� ���� ���� 
		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);


		//�ΰ��� �� ������Ʈ ����
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);

	}
	
	//���� UI �̹��� ����
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

	//�޴� ���� ������(��ũ��)
	IMAGEMANAGER->render("maptool_UI_SCROLLS", getMemDC(), _rcUIBg.left + 100, _rcUIBg.top - 30);
	IMAGEMANAGER->render("tilemap", getMemDC(), _rcMapSpace.left, _rcMapSpace.top, scrollX * 64, scrollY * 64, 704, MAP_HEIGHT);



	// ���� ���� ȭ�� �� ������ ���� Ÿ�� RECT ���
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

	//������ RECT(���ľ���)
	for (int i = 0; i < 5; i++)
	{
		FrameRect(getMemDC(), icon[i], RGB(255, 255, 0));
	}

	//Ÿ�� �����ϸ� �� Ÿ�� ǥ�����ִ� RECT
	if(upUI) FrameRect(getMemDC(), select_tile, RGB(0, 255, 255));
	
	
	// UI ����(�׻� ���� �Ʒ���)
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(getMemDC(), &_rcSaveLoadBg, brush);

	FrameRect(getMemDC(), _rcUIBg, RGB(255, 0, 0));
	//UI ��ư �̹��� ����
	IMAGEMANAGER->findImage("save_button")->render(getMemDC(), _rcSave.left, _rcSave.top);
	IMAGEMANAGER->findImage("load_button")->render(getMemDC(), _rcLoad.left, _rcLoad.top);
	IMAGEMANAGER->findImage("eraser_button")->render(getMemDC(), _rcEraser.left, _rcEraser.top);
	IMAGEMANAGER->findImage("reset_button")->render(getMemDC(), _rcReset.left, _rcReset.top);

	IMAGEMANAGER->findImage("arrow_left")->render(getMemDC(), _rcArrowLeft.left, _rcArrowLeft.top);
	IMAGEMANAGER->findImage("arrow_right")->render(getMemDC(), _rcArrowRight.left, _rcArrowRight.top);


	//RECT ǥ�ÿ�
	FrameRect(getMemDC(), _rcMapSpace, RGB(255, 0, 0));
	FrameRect(getMemDC(), _rcArrowLeft, RGB(255, 0, 0));
	FrameRect(getMemDC(), _rcArrowRight, RGB(255, 0, 0));
	FrameRect(getMemDC(), _rcObjectMap, RGB(255, 0, 0));
	FrameRect(getMemDC(), IMAGEMANAGER->findImage("maptool_UI_SCROLLS")->boundingBox(), RGB(255, 0, 0));


	//ǥ�ÿ� TEXT
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	sprintf(str, "LEFT: %d, TOP: %d", _rcMapSpace.left, _rcMapSpace.top);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
	sprintf(str, "X: %d, Y: %d", setMapCoord(mouseCoord).x, setMapCoord(mouseCoord).y);
	TextOut(getMemDC(), 20, 20, str, strlen(str));

}

// ���� ����
void mapToolScene::mapToolSetup()
{
	// ���� �ΰ��� ȭ�� RECT �ʱ�ȭ
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			_tiles[i * MAP_TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	// Ÿ�ϸ� ��ü ����(�ʱ�ȭ)
	for (int i = 0; i < MAP_TILEX * MAP_TILEY; i++)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}

	//==================================== ���� RECT �ʱ�ȭ ========================================//

	//��� ī�޶� RECT �ʱ�ȭ(��ü�� ���߾�)
	//_rcMCamera = RectMakeCenter(TILESIZEX / 2, TILESIZEY / 2, WINSIZEX, WINSIZEY);
	_rcMCamera = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	// ���� UI�� RECT �ʱ�ȭ
	_rcUIBg = RectMakeCenter(WINSIZEX / 2, WINSIZEY + 150, 904, 400);
	_rcSaveLoadBg = RectMake(0, 0, WINSIZEX, 50);

	//�Ͽ콺 Ÿ�ϸ� Rect �ʱ�ȭ
	_rcMapSpace = RectMake(_rcUIBg.left + 100, _rcUIBg.top + 75, 704, MAP_HEIGHT);

	//������Ʈ �� �Ѵ� ��ư
	_rcObjectMap = RectMake(_rcUIBg.right - 80, _rcUIBg.top + 50, 20, 20);

	_rcArrowLeft = RectMake(_rcUIBg.left + 90, _rcUIBg.bottom - 65, 40, 20);
	_rcArrowRight = RectMake(_rcUIBg.right - 130, _rcUIBg.bottom - 65, 40, 20);



	//������ ��Ʈ �ʱ�ȭ
	for (int i = 0; i < 5; i++)
	{
		icon[i] = RectMakeCenter(125 + _rcUIBg.left + (50 * i), _rcUIBg.top, 50, 50);
	}

	// ��Ʈ�� ��ư RECT ��ġ �ʱ�ȭ
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
	
	// �ΰ��� ȭ��� RECT ���� �浹 ó��
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
					// ���� ��ư�� ���� Ÿ�� ����
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

	// ���� ���̺�
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

	// ���� �ε�
	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * MAP_TILEX * MAP_TILEY, &read, NULL);
	CloseHandle(file);

	textOut(getMemDC(), WINSIZEX, WINSIZEY, "LOAD COMPLETE", RGB(255, 0, 0));
}

void mapToolScene::updateRect()
{
	// ������ ��Ʈ �ʱ�ȭ
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
	// ���� �ΰ��� ȭ�� ��� �ܵ� �⺻ Ÿ���� �ǵ��� ����
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

// ���� ���� ( �� �� �� �� )..
TERRAIN mapToolScene::terrainSelect(int frameX, int frameY)
{
	// �ø�Ʈ
	if (frameX >= 3 && frameY < 4)
	{
		return TR_WALL;
	}
	// �ܵ�
	if (frameX == 3)
	{
		return TR_GRASS;
	}
	// ��
	if (frameX == 4)
	{
		return TR_WATER;
	}

	// �� �̿��� ��� ������ �⺻�� ����
	return TR_GROUND;
}
// ������Ʈ ����
OBJECT mapToolScene::objectSelect(int frameX, int frameY)
{
	//// �ø�Ʈ
	if (frameX <= 28)
	{
		return OBJ_CARPET;
	}
	// ��
	if ((frameX > 28 && frameX <= 32) || (frameX >= 32 && frameX < 36))
	{
		return OBJ_BLOCK1;
	}
	// �ܵ�
	if (frameX == 3)
	{
		return OBJ_BLOCK2;
	}
	// ��
	if (frameX == 4)
	{
		return OBJ_BLOCK3;
	}

	return OBJ_BLOCKS;
}

//input(feat. ptInRect) ������ ==> �׳� update�� ptInRect �߰��ϸ� �ٸ��� �۵� �ȵ˴ϴ�...
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

		// ��ũ�� X, ��ũ�� Y (���� ����� ����ó�� ����)
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

		// ���� UI �Է� ó��
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

//���� UI �˾� �ִϸ��̼�
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

//���� ���X
POINT mapToolScene::setMapCoord(POINT mouseP)
{
	mouseP.x = mouseP.x + _rcMCamera.left;
	mouseP.y = mouseP.y + _rcMCamera.top;

	return mouseP;
}
