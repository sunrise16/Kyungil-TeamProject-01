#include "stdafx.h"
#include "inGameScene.h"
#include "mapToolScene.h"

// �ʱ�ȭ (init)
HRESULT inGameScene::init()
{
	_country = IMAGEMANAGER->addImage("���ٸ�����", "Images/Source/����_������4028x2756.bmp", 4028, 2756);

	// Ÿ�� �ε�
	this->load();

	// player Ŭ���� ���� �Ҵ� ����
	_player = new player;
	_player->init(playerPt);

	// octupus Ŭ���� ���� �Ҵ� ����
	_octopus = new octopus;
	_octopus->init(octopusPt_x, octopusPt_y);

	// mushroom Ŭ���� ���� �Ҵ� ����
	_mushroom = new mushroom;
	_mushroom->init(mushroomPt_x, mushroomPt_y);

	// boss Ŭ���� ���� �Ҵ� ����
	_boss = new boss;
	_boss->init(bossPt_x, bossPt_y);

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
	_player->update(0, 0, true, true, true, true);

	// octopus Ŭ���� ������Ʈ
	_octopus->update(0, 0, true, true);

	// mushroom Ŭ���� ������Ʈ
	_mushroom->update(0, 0, true, true);

	// boss Ŭ���� ������Ʈ
	_boss->update(0, 0, true, true);

	bgcenter.x = _bgRc.left + ((_bgRc.right - _bgRc.left) / 2);
	bgcenter.y = _bgRc.top + ((_bgRc.bottom - _bgRc.top) / 2);

	if (INPUT->getKey(VK_LEFT))
	{
		if (_bgRc.left <= 0)
		{
			_bgRc.left = 0;
		}
		else
		{
			bgcenter.x -= 5;

			POINT pt;
			pt.x = _player->getPlayercenter().x - 5;
			pt.y = _player->getPlayercenter().y;
			_player->setPlayercenter(pt);
		}
	}
	else if (INPUT->getKey(VK_RIGHT))
	{
		if (_bgRc.right >= _country->getWidth())
		{
			_bgRc.right = _country->getWidth();
		}
		else
		{
			bgcenter.x += 5;

			POINT pt;
			pt.x = _player->getPlayercenter().x + 5;
			pt.y = _player->getPlayercenter().y;
			_player->setPlayercenter(pt);
		}
	}
	else if (INPUT->getKey(VK_UP))
	{
		if (_bgRc.top <= 0)
		{
			_bgRc.top = 0;

		}
		else
		{
			bgcenter.y -= 5;

			POINT pt;
			pt.x = _player->getPlayercenter().x;
			pt.y = _player->getPlayercenter().y - 5;
			_player->setPlayercenter(pt);
		}
	}
	else if (INPUT->getKey(VK_DOWN))
	{
		if (_bgRc.bottom >= _country->getHeight() || _player->getPlayerRc().bottom >= WINSIZEY)
		{
			_bgRc.bottom = _country->getHeight();
		}
		else
		{
			bgcenter.y += 5;

			POINT pt;
			pt.x = _player->getPlayercenter().x;
			pt.y = _player->getPlayercenter().y + 5;
			_player->setPlayercenter(pt);
		}
	}
	_bgRc = RectMakeCenter(bgcenter.x, bgcenter.y, WINSIZEX, WINSIZEY);

	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{

			//if (_tiles[i * MAP_TILEX + j].terrain != TR_WATER)continue;
			//if (_tiles[i * MAP_TILEX + j].obj != OBJ_BLOCKS) continue;
			if (_tiles[i * MAP_TILEX + j].terrain != TR_WALL)continue;
			// �ϳ��� �ϸ� �Ǵµ� �� �� �̻� �ϸ� �� ��. ����!!!!!!!!!!!!!

			// �÷��̾�� ������Ʈ �浹 (�߸Ŵ� ��Ű�� �ʵ��� ����)
			if (IntersectRect(&empty, &_player->getPlayerRc(), &_tiles[i * MAP_TILEX + j].rc))
			{
				if (IntersectRect(&empty, &_player->getplayerleftatkRc(), &_tiles[i * MAP_TILEX + j].rc))//����
				{
					_player->setPlayerRc(_tiles[(i * MAP_TILEX + j) + 1].rc);
				}
				if (IntersectRect(&empty, &_player->getplayerrightatkRc(), &_tiles[i * MAP_TILEX + j].rc))//������
				{
					_player->setPlayerRc(_tiles[(i * MAP_TILEX + j) - 1].rc);
				}
				if (IntersectRect(&empty, &_player->getplayertopatkRc(), &_tiles[i * MAP_TILEX + j].rc))//����
				{
					_player->setPlayerRc(_tiles[(i + 1) * MAP_TILEX + j].rc);
				}
				if (IntersectRect(&empty, &_player->getplayerbottomatkRc(), &_tiles[i * MAP_TILEX + j].rc))//�Ʒ���
				{
					_player->setPlayerRc(_tiles[(i - 1) * MAP_TILEX + j].rc);
				}
			}

			//������ Ÿ���� �浹ó��

			//if (!_mushroom->getMushroom().empty()) //����
			//{
			//	for (int k = 0; k < _mushroom->getMushroom().size(); k++)
			//	{
			//		if (IntersectRect(&empty, &_mushroom->getMushroom()[k]._rc, &_tiles[i * MAP_TILEX + j].rc))
			//		{

			//			if ((_mushroom->getMushroom()[k]._rc.top < _tiles[i * MAP_TILEX + j].rc.bottom && _mushroom->getMushroom()[k]._rc.bottom > _tiles[i * MAP_TILEX + j].rc.top)
			//				|| (_mushroom->getMushroom()[k]._rc.top < _tiles[i * MAP_TILEX + j].rc.bottom && _mushroom->getMushroom()[k]._rc.bottom > _tiles[i * MAP_TILEX + j].rc.top))
			//			{
			//
			//				if (_mushroom->getMushroom()[k]._rc.left <= _tiles[i * MAP_TILEX + j].rc.right)
			//				{
			//					_mushroom->setMushroom[k]._rc(_tiles[(i * MAP_TILEX + j) + 1].rc);
			//				}
			//
			//				/*if (_mushroom->getMushroom()[k]._rc.right >= _tiles[i * MAP_TILEX + j].rc.left)
			//				{
			//					_mushroom->setMushroom[k]._rc(_tiles[(i * MAP_TILEX + j) + 1].rc);
			//				}*/
			//
			//			}
			//
			//			/*if ((_mushroom->getMushroom()[k]._rc.right > _tiles[i * MAP_TILEX + j].rc.left && _mushroom->getMushroom()[k]._rc.left < _tiles[i * MAP_TILEX + j].rc.right)
			//				|| (_mushroom->getMushroom()[k]._rc.left < _tiles[i * MAP_TILEX + j].rc.right && _mushroom->getMushroom()[k]._rc.right > _tiles[i * MAP_TILEX + j].rc.left))
			//			{

			//				if (_mushroom->getMushroom()[k]._rc.top <= _tiles[i * MAP_TILEX + j].rc.bottom)
			//				{
			//					_mushroom->setMushroom[k]._rc(_tiles[((i - 1) * MAP_TILEX + j)].rc);
			//				}
			//			
			//				if (_mushroom->getMushroom()[k]._rc.top >= _tiles[i * MAP_TILEX + j].rc.bottom)
			//				{
			//					_mushroom->setMushroom[k]._rc(_tiles[((i + 1) * MAP_TILEX + j) + 1].rc);
			//				}

						//}
			/*		}
				}
			}*/



			//����� Ÿ���� �浹ó��

			//if (!_octopus->getOctopus().empty()) //����
			//{
			//	for (int k = 0; k < _octopus->getOctopus().size(); k++)
			//	{
			//		if (IntersectRect(&empty, &_octopus->getOctopus()[k]._rc, &_tiles[i * MAP_TILEX + j].rc))
			//		{

			//			if ((_octopus->getOctopus()[k]._rc.top < _tiles[i * MAP_TILEX + j].rc.bottom && _octopus->getOctopus()[k]._rc.bottom > _tiles[i * MAP_TILEX + j].rc.top)
			//				|| (_octopus->getOctopus()[k]._rc.top < _tiles[i * MAP_TILEX + j].rc.bottom && _octopus->getOctopus()[k]._rc.bottom > _tiles[i * MAP_TILEX + j].rc.top))
			//			{
			//
			//				if (_octopus->getOctopus()[k]._rc.left <= _tiles[i * MAP_TILEX + j].rc.right)
			//				{
			//					_octopus->setOctopus[k]._rc(_tiles[(i * MAP_TILEX + j) + 1].rc);
			//				}
			//
			//				/*if (_octopus->getOctopus()[k]._rc.right >= _tiles[i * MAP_TILEX + j].rc.left)
			//				{
			//					_octopus->setOctopus[k]._rc(_tiles[(i * MAP_TILEX + j) + 1].rc);
			//				}*/
			//
			//			}
			//
			//			/*if ((_octopus->getOctopus()[k]._rc.right > _tiles[i * MAP_TILEX + j].rc.left && _octopus->getOctopus()[k]._rc.left < _tiles[i * MAP_TILEX + j].rc.right)
			//				|| (_octopus->getOctopus()[k]._rc.left < _tiles[i * MAP_TILEX + j].rc.right && _octopus->getOctopus()[k]._rc.right > _tiles[i * MAP_TILEX + j].rc.left))
			//			{

			//				if (_octopus->getOctopus()[k]._rc.top <= _tiles[i * MAP_TILEX + j].rc.bottom)
			//				{
			//					_octopus->setOctopus[k]._rc(_tiles[((i - 1) * MAP_TILEX + j)].rc);
			//				}
			//			
			//				if (_octopus->getOctopus()[k]._rc.top >= _tiles[i * MAP_TILEX + j].rc.bottom)
			//				{
			//					_octopus->setOctopus[k]._rc(_tiles[((i + 1) * MAP_TILEX + j) + 1].rc);
			//				}

						//}
			/*		}
				}
			}*/
		}
	}
	//_bgRc = RectMakeCenter(_player->getPlayerRc().left - _cameraRc.left, _player->getPlayerRc().top - _cameraRc.top, WINSIZEX, WINSIZEY);

	cameraX = _player->getPlayercenter().x;
	cameraY = _player->getPlayercenter().y;

	_cameraRc = RectMakeCenter(cameraX, cameraY, WINSIZEX, WINSIZEY);
}

// ���� (render)
void inGameScene::render()
{
	IMAGEMANAGER->render("���ٸ�����", getMemDC(), 0, 0, _bgRc.left, _bgRc.top, WINSIZEX, WINSIZEY);

	// Ÿ�� ����
	//this->mapRender();

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
			if (_tiles[i * MAP_TILEX + j].terrain == TR_WALL)
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