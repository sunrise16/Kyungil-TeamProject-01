#include "stdafx.h"
#include "inGameScene.h"

// �ʱ�ȭ (init)
HRESULT inGameScene::init()
{
	// Ÿ�� �ε�
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

	// boss Ŭ���� ���� �Ҵ� ����
	_boss = new boss;
	_boss->init();

	// �ּҰ� ����
	_player->setBossAdress(_boss);
	_player->setOctopusAdress(_octopus);
	_player->setMushroomAdress(_mushroom);
	_boss->setPlayerAdress(_player);
	_boss->getMissileE()->setPlayerAdress(_player);
	_boss->getMissileE2()->setPlayerAdress(_player);
	_octopus->setPlayerAdress(_player);
	_mushroom->setPlayerAdress(_player);

	// Ȥ�ó� �ؼ� ���� ��� ��Ʈ
	_bgRc = RectMakeCenter(_player->getPlayercenter().x, _player->getPlayercenter().y, WINSIZEX, WINSIZEY);

	// �ʱ�ȭ ����
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

	// boss Ŭ���� ����
	_boss->release();
	SAFE_DELETE(_boss);
}

// ������Ʈ (update)
void inGameScene::update()
{
	// Ÿ�� ������Ʈ
	this->updateRect();

	// player Ŭ���� ������Ʈ
	_player->update();

	// octopus Ŭ���� ������Ʈ
	_octopus->update();

	// mushroom Ŭ���� ������Ʈ
	_mushroom->update();

	// boss Ŭ���� ������Ʈ
	_boss->update();

	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			//if ((_tiles[i * MAP_TILEX + j].terrain != TR_WATER) || (_tiles[i * MAP_TILEX + j].obj != OBJ_BLOCKS) || (_tiles[i * MAP_TILEX + j].terrain != TR_WALL)) continue;

			//if (_tiles[i * MAP_TILEX + j].terrain != TR_WATER)continue;
			//if (_tiles[i * MAP_TILEX + j].obj != OBJ_BLOCKS) continue;
			if (_tiles[i * MAP_TILEX + j].terrain != TR_WALL)continue;
			//�ϳ��� �ϸ� �Ǵµ� �� �� �̻� �ϸ� �� ��. ����!!!!!!!!!!!!!

			//�÷��̾�� ������Ʈ �浹 --> �߸Ŵ� ��Ű�� �ʵ��� ����
			if (IntersectRect(&empty, &_player->getPlayerRc(), &_tiles[i * MAP_TILEX + j].rc))
			{
				if (IntersectRect(&empty, &_player->getplayerleftatkRc(), &_tiles[i * MAP_TILEX + j].rc))
				{
					_player->setPlayerRc(_tiles[(i * MAP_TILEX + j) + 1].rc);
				}
				if (IntersectRect(&empty, &_player->getplayerrightatkRc(), &_tiles[i * MAP_TILEX + j].rc))
				{
					_player->setPlayerRc(_tiles[(i * MAP_TILEX + j) - 1].rc);
				}
				if (IntersectRect(&empty, &_player->getplayertopatkRc(), &_tiles[i * MAP_TILEX + j].rc))
				{
					_player->setPlayerRc(_tiles[(i + 1) * MAP_TILEX + j].rc);
				}
				if (IntersectRect(&empty, &_player->getplayerbottomatkRc(), &_tiles[i * MAP_TILEX + j].rc))
				{
					_player->setPlayerRc(_tiles[(i - 1) * MAP_TILEX + j].rc);
				}
			}
			//if (!_mushroom->getMushroom().empty())
			//{
			//	for (int k = 0; k < _mushroom->getMushroom().size(); k++)
			//	{
			//		if (IntersectRect(&empty, &_mushroom->getMushroom()[k]._rc, &_tiles[i * MAP_TILEX + j].rc))continue;
			//	}
			//}

			//if (!_octopus->getOctopus().empty())
			//{
			//	for (int k = 0; k < _octopus->getOctopus().size(); k++)
			//	{
			//		if (IntersectRect(&empty, &_octopus->getOctopus()[k]._rc, &_tiles[i * MAP_TILEX + j].rc))continue;
			//	}
			//}

			//if (IntersectRect(&empty, &_octopus->getOctopus()[i]._rc, &_tiles[i * MAP_TILEX + j].rc))continue;
			//if (IntersectRect(&empty, &_mushroom->getMushroom()[i]._rc, &_tiles[i * MAP_TILEX + j].rc))continue;
		}
	}

	_bgRc = RectMakeCenter(_player->getPlayerRc().left - _cameraRc.left, _player->getPlayerRc().top - _cameraRc.top, WINSIZEX, WINSIZEY);

	camX = _player->getPlayercenter().x;
	camY = _player->getPlayercenter().y;

	_cameraRc = RectMakeCenter(camX, camY, WINSIZEX, WINSIZEY);
}

// ���� (render)
void inGameScene::render()
{
	// Ÿ�� ����
	this->mapRender();

	// player Ŭ���� ����
	_player->render();

	// octopus Ŭ���� ����
	_octopus->render();

	// mushroom Ŭ���� ����
	_mushroom->render();

	// boss Ŭ���� ����
	_boss->render();

	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{

			if (_tiles[i * MAP_TILEX + j].terrain == TR_WATER || _tiles[i * MAP_TILEX + j].obj == OBJ_BLOCKS || _tiles[i * MAP_TILEX + j].terrain == TR_WALL)
			{
				sprintf_s(str, "%d, %d", j, i);
				TextOut(getMemDC(), _tiles[i * MAP_TILEX + j].rc.left, _tiles[i * MAP_TILEX + j].rc.top, str, strlen(str));
				sprintf_s(str3, "%d, %d", _tiles[i * MAP_TILEX + j].rc.left + 32, _tiles[i * MAP_TILEX + j].rc.top + 32);
				TextOut(getMemDC(), _tiles[i * MAP_TILEX + j].rc.left, _tiles[i * MAP_TILEX + j].rc.top + 32, str3, strlen(str3));
			}
		}
	}

	sprintf_s(str2, "%d, %d", _player->getPlayercenter().x, _player->getPlayercenter().y);
	TextOut(getMemDC(), 710, 300, str2, strlen(str2));
}

// Ÿ�� �ε�
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

// Ÿ�� ������Ʈ
void inGameScene::updateRect()
{
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{ // 32, 35
			_tiles[(i)* MAP_TILEX + (j)].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
}

// Ÿ�� ����
void inGameScene::mapRender()
{
	for (int i = 0; i < MAP_TILEY * MAP_TILEX; i++)
	{
		if (_tiles[i].rc.left < _cameraRc.left) continue;
		if (_tiles[i].rc.right > _cameraRc.right) continue;
		if (_tiles[i].rc.top < _cameraRc.top) continue;
		if (_tiles[i].rc.bottom > _cameraRc.bottom) continue;


		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		//sprintf(str, "[ %d, %d ]", _tiles[i].x, _tiles[i].y);
		//TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));

		//�ΰ��� �� ������Ʈ ����
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);


		IMAGEMANAGER->render("tilemap", getMemDC(), _bgRc.left, _bgRc.top);

	}
}