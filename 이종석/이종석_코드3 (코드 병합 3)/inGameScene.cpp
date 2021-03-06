#include "stdafx.h"
#include "inGameScene.h"

// 초기화 (init)
HRESULT inGameScene::init()
{
	this->load();

	// player 클래스 동적 할당 생성
	_player = new player;
	_player->init();

	// octupus 클래스 동적 할당 생성
	_octopus = new octopus;
	_octopus->init();

	// mushroom 클래스 동적 할당 생성
	_mushroom = new mushroom;
	_mushroom->init();

	// 주소값 전달
	_player->setOctopusAdress(_octopus);
	_player->setMushroomAdress(_mushroom);
	_octopus->setPlayerAdress(_player);
	_mushroom->setPlayerAdress(_player);

	return S_OK;
}

// 해제 (release)
void inGameScene::release()
{
	// player 클래스 해제
	_player->release();
	SAFE_DELETE(_player);

	// octopus 클래스 해제
	_octopus->release();
	SAFE_DELETE(_octopus);

	// mushroom 클래스 해제
	_mushroom->release();
	SAFE_DELETE(_mushroom);
}

// 업데이트 (update)
void inGameScene::update()
{
	// player 클래스 업데이트
	_player->update();

	// octopus 클래스 업데이트
	_octopus->update();

	// mushroom 클래스 업데이트
	_mushroom->update();

	this->updateRect();
}

// 렌더 (render)
void inGameScene::render()
{
	this->mapRender();

	// player 클래스 렌더
	_player->render();

	// octopus 클래스 렌더
	_octopus->render();

	// mushroom 클래스 렌더
	_mushroom->render();
}

void inGameScene::updateRect()
{
	//타일 렉트 업뎃
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{ // 32, 35
			_tiles[(i) * MAP_TILEX + (j)].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
}

void inGameScene::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save1.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * MAP_TILEX * MAP_TILEY, &read, NULL);
	CloseHandle(file);

	TextOut(getMemDC(), WINSIZEX / 2, 100, "LOAD COMPLETE", RGB(255, 0, 0));
}

void inGameScene::mapRender()
{
	for (int i = 0; i < MAP_TILEY * MAP_TILEX; i++)
	{
		if (_tiles[i].rc.left < 0) continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		//sprintf(str, "[ %d, %d ]", _tiles[i].x, _tiles[i].y);
		//TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));

		//인게임 맵 오브젝트 렌더
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}
