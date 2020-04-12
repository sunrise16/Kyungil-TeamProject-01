#include "stdafx.h"
#include "inGameScene.h"

// �ʱ�ȭ (init)
HRESULT inGameScene::init()
{
	this->load();

	// player Ŭ���� ���� �Ҵ� ����
	_player = new player;
	_player->init();

	// octupus Ŭ���� ���� �Ҵ� ����
	_octopus = new octopus;
	_octopus->init();

	// mushroom Ŭ���� ���� �Ҵ� ����
	_mushroom = new mushroom;
	_mushroom->init();

	// �ּҰ� ����
	_player->setOctopusAdress(_octopus);
	_player->setMushroomAdress(_mushroom);
	_octopus->setPlayerAdress(_player);
	_mushroom->setPlayerAdress(_player);

	return S_OK;
}

// ���� (release)
void inGameScene::release()
{
	// player Ŭ���� ����
	_player->release();
	SAFE_DELETE(_player);

	// octopus Ŭ���� ����
	_octopus->release();
	SAFE_DELETE(_octopus);

	// mushroom Ŭ���� ����
	_mushroom->release();
	SAFE_DELETE(_mushroom);
}

// ������Ʈ (update)
void inGameScene::update()
{
	// player Ŭ���� ������Ʈ
	_player->update();

	// octopus Ŭ���� ������Ʈ
	_octopus->update();

	// mushroom Ŭ���� ������Ʈ
	_mushroom->update();

	this->updateRect();
}

// ���� (render)
void inGameScene::render()
{
	this->mapRender();

	// player Ŭ���� ����
	_player->render();

	// octopus Ŭ���� ����
	_octopus->render();

	// mushroom Ŭ���� ����
	_mushroom->render();
}

void inGameScene::updateRect()
{
	//Ÿ�� ��Ʈ ����
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

		//�ΰ��� �� ������Ʈ ����
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}
