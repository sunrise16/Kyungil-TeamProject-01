#include "stdafx.h"
#include "inGameScene.h"

// 초기화 (init)
HRESULT inGameScene::init()
{
	// 타일 로드
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

	// boss 클래스 동적 할당 생성
	_boss = new boss;
	_boss->init();

	// 주소값 전달
	_player->setBossAdress(_boss);
	_player->setOctopusAdress(_octopus);
	_player->setMushroomAdress(_mushroom);
	_boss->setPlayerAdress(_player);
	_boss->getMissileE()->setPlayerAdress(_player);
	_boss->getMissileE2()->setPlayerAdress(_player);
	_octopus->setPlayerAdress(_player);
	_mushroom->setPlayerAdress(_player);

	// 혹시나 해서 만든 배경 렉트
	_bgRc = RectMakeCenter(_player->getPlayercenter().x, _player->getPlayercenter().y, WINSIZEX, WINSIZEY);

	// 초기화 종료
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

	// boss 클래스 해제
	_boss->release();
	SAFE_DELETE(_boss);
}

// 업데이트 (update)
void inGameScene::update()
{
	// 타일 업데이트
	this->updateRect();

	// player 클래스 업데이트
	_player->update();

	// octopus 클래스 업데이트
	_octopus->update();

	// mushroom 클래스 업데이트
	_mushroom->update();

	// boss 클래스 업데이트
	_boss->update();

	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			//if ((_tiles[i * MAP_TILEX + j].terrain != TR_WATER) || (_tiles[i * MAP_TILEX + j].obj != OBJ_BLOCKS) || (_tiles[i * MAP_TILEX + j].terrain != TR_WALL)) continue;

			//if (_tiles[i * MAP_TILEX + j].terrain != TR_WATER)continue;
			//if (_tiles[i * MAP_TILEX + j].obj != OBJ_BLOCKS) continue;
			if (_tiles[i * MAP_TILEX + j].terrain != TR_WALL)continue;
			//하나만 하면 되는데 두 개 이상 하면 안 됨. 주의!!!!!!!!!!!!!

			//플레이어와 오브젝트 충돌 --> 야매니 들키지 않도록 주의
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

// 렌더 (render)
void inGameScene::render()
{
	// 타일 렌더
	this->mapRender();

	// player 클래스 렌더
	_player->render();

	// octopus 클래스 렌더
	_octopus->render();

	// mushroom 클래스 렌더
	_mushroom->render();

	// boss 클래스 렌더
	_boss->render();

	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{

			if (_tiles[i * MAP_TILEX + j].terrain == TR_WATER || _tiles[i * MAP_TILEX + j].obj == OBJ_BLOCKS || _tiles[i * MAP_TILEX + j].terrain == TR_WALL)
			{
				sprintf(str, "%d, %d", j, i);
				TextOut(getMemDC(), _tiles[i * MAP_TILEX + j].rc.left, _tiles[i * MAP_TILEX + j].rc.top, str, strlen(str));
				sprintf(str3, "%d, %d", _tiles[i * MAP_TILEX + j].rc.left + 32, _tiles[i * MAP_TILEX + j].rc.top + 32);
				TextOut(getMemDC(), _tiles[i * MAP_TILEX + j].rc.left, _tiles[i * MAP_TILEX + j].rc.top + 32, str3, strlen(str3));
			}
		}
	}

	sprintf(str2, "%d, %d", _player->getPlayercenter().x, _player->getPlayercenter().y);
	TextOut(getMemDC(), 710, 300, str2, strlen(str2));
}

// 타일 로드
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

// 타일 업데이트
void inGameScene::updateRect()
{
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			_tiles[(i) * MAP_TILEX + (j)].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
}

// 타일 렌더
void inGameScene::mapRender()
{
	for (int i = 0; i < MAP_TILEY * MAP_TILEX; i++)
	{
		if (_tiles[i].rc.left < 0)
			continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		//sprintf(str, "[ %d, %d ]", _tiles[i].x, _tiles[i].y);
		//TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));

		// 인게임 맵 오브젝트 렌더
		if (_tiles[i].obj == OBJ_NONE)
			continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}