#include "stdafx.h"
#include "octopus.h"

HRESULT octopus::init()
{
	//문어 이미지 삽입
	_red = IMAGEMANAGER->addFrameImage("red", "그림파일/빨간문어 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_blue = IMAGEMANAGER->addFrameImage("blue", "그림파일/하늘색문어 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_yellow = IMAGEMANAGER->addFrameImage("yellow", "그림파일/노란문어 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_destroy = IMAGEMANAGER->addFrameImage("destroy", "그림파일/문어파괴 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));
	_destroy1 = IMAGEMANAGER->addFrameImage("destroy1", "그림파일/문어파괴1 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));
	_destroy2 = IMAGEMANAGER->addFrameImage("destroy2", "그림파일/문어파괴2 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));

	//문어 구조체 초기화
	//for (int i = 0; i < _octopus.size(); i++)
	//{
	//	//문어렉트 위치 랜덤 생성
	//	_octopus[i].x = RANDOM->Range(0, WINSIZEX - 80);
	//	_octopus[i].y = RANDOM->Range(0, WINSIZEY - 64);
	//	_octopus[i]._hp = MINION_HP;
	//	_octopus[i]._angle = PI_2;
	//	_octopus[i]._speed = 3.0f;
	//	_octopus[i].frameX = 0;
	//	_octopus[i].frameY = RANDOM->Range(octo_DOWN,octo_UP);
	//	_octopus[i]._state = RANDOM->Range(0, 3);
	//	_octopus[i].destroyX = _octopus[i].destroyY = 0;
	//}

	_missile = new missile;
	_missile->init(30, 500);

	return S_OK;
}

void octopus::release()
{
	_missile->release();
	SAFE_DELETE(_missile);
}

void octopus::update()
{
	_missile->update();

	if (INPUT->getKeyDown(VK_LBUTTON))
	{
		tagOctopus octopus;
		octopus.x = RANDOM->Range(0, WINSIZEX - 80);
		octopus.y = RANDOM->Range(0, WINSIZEY - 64);
		octopus._hp = MINION_HP;
		octopus._angle = PI_2;
		octopus._speed = 3.0f;
		octopus.frameX = 0;
		octopus.frameY = RANDOM->Range(octo_DOWN, octo_UP);
		octopus._state = RANDOM->Range(0, 3);
		octopus.destroyX = octopus.destroyY = 0;
		octopus._color = RANDOM->Range(0, 2);
		_octopus.push_back(octopus);
	}

	for (int i = 0; i < _octopus.size(); i++)
	{
		//_octopus[i]._hp -= 1;			//죽었을때 모션 확인
		if (_octopus[i].x - 32 < 0)
		{
			_octopus[i].x = 32;
		}
		if (_octopus[i].x + 32 > WINSIZEX)
		{
			_octopus[i].x = WINSIZEX - 32;
		}
		if (_octopus[i].y - 40 < 0)
		{
			_octopus[i].y = 40;
		}
		if (_octopus[i].y + 40 > WINSIZEY)
		{
			_octopus[i].y = WINSIZEY - 40;
		}

		if (_octopus[i]._hp > 0)
		{
			if (_octopus[i].frameY == octo_DOWN)			//아래 방향
			{
				_octopus[i].y += 0.5;
				_octopus[i]._count++;
				if (_octopus[i]._count % 50 == 0)
				{
					_octopus[i].frameX++;
				}
				if (_octopus[i].frameX > 3)				//문어 대포모션, 이동 정지
				{
					_octopus[i].y -= 0.5;
				}
				if (_octopus[i]._count % 250 == 0)			//문어 발사
				{
					_missile->fire(_octopus[i].x, _octopus[i].y + 32, -(PI_2));
				}
				if (_octopus[i].frameX > 5)
				{
					_octopus[i].frameX = 0;
					_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
					_octopus[i]._count = RANDOM->Range(0, 30);
				}
			}
			if (_octopus[i].frameY == octo_LEFT)			//왼쪽 방향
			{
				_octopus[i].x -= 0.5;
				_octopus[i]._count++;
				if (_octopus[i]._count % 50 == 0)
				{
					_octopus[i].frameX++;
				}
				if (_octopus[i].frameX > 3)				//문어 대포모션, 이동 정지
				{
					_octopus[i].x += 0.5;
				}
				if (_octopus[i]._count % 250 == 0)			//문어 발사
				{
					_missile->fire(_octopus[i].x - 40, _octopus[i].y - 5, PI);
				}
				if (_octopus[i].frameX > 5)
				{
					_octopus[i].frameX = 0;
					_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
					_octopus[i]._count = RANDOM->Range(0, 30);
				}
			}
			if (_octopus[i].frameY == octo_RIGHT)		//오른쪽 방향
			{
				_octopus[i].x += 0.5;
				_octopus[i]._count++;
				if (_octopus[i]._count % 50 == 0)
				{
					_octopus[i].frameX++;
				}
				if (_octopus[i].frameX > 3)				//문어 대포모션, 이동 정지
				{
					_octopus[i].x -= 0.5;
				}
				if (_octopus[i]._count % 250 == 0)			//문어 발사
				{
					_missile->fire(_octopus[i].x + 40, _octopus[i].y - 5, PI2);
				}
				if (_octopus[i].frameX > 5)
				{
					_octopus[i].frameX = 0;
					_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
					_octopus[i]._count = RANDOM->Range(0, 30);
				}
			}
			if (_octopus[i].frameY == octo_UP)			//위쪽 방향
			{
				_octopus[i].y -= 0.5;
				_octopus[i]._count++;
				if (_octopus[i]._count % 50 == 0)
				{
					_octopus[i].frameX++;
				}
				if (_octopus[i].frameX > 3)			//문어 대포모션, 이동 정지
				{
					_octopus[i].y += 0.5;
				}
				if (_octopus[i]._count % 250 == 0)			//문어 발사
				{
					_missile->fire(_octopus[i].x, _octopus[i].y - 32, PI_2);
				}
				if (_octopus[i].frameX > 5)
				{
					_octopus[i].frameX = 0;
					_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
					_octopus[i]._count = RANDOM->Range(0, 30);
				}
			}
		}
	}

	//문어 죽음
	for (int i = 0; i < _octopus.size(); i++)
	{
		if (_octopus[i]._hp <= 0)
		{
			_octopus[i]._hp = 0;
			_octopus[i]._count++;
			if (_octopus[i]._count % 10 == 0)
			{
				_octopus[i].destroyX++;
			}
			if (_octopus[i].destroyX > 8)
			{
				//_octopus[i]._hp = 30;
				_octopus.erase(_octopus.begin() + i);
			}
		}
	}
}

void octopus::render()
{
	_missile->render();
	for (int i = 0; i < _octopus.size(); i++)
	{
		if (_octopus[i]._hp > 0)	// 문어 색깔 0 = red , 1 = blue , 2 = yellow
		{
			if (_octopus[i]._color == 0)
			{
				//렉트 활용
				//IMAGEMANAGER->frameRender("red", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top,_octopus[i].frameX,_octopus[i].frameY);
				//이미지 활용
				_red->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
			}
			if (_octopus[i]._color == 1)
			{
				//렉트 활용
				//IMAGEMANAGER->frameRender("blue", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
				//이미지 활용
				_blue->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
			}
			if (_octopus[i]._color == 2)
			{
				//렉트 활용
				//IMAGEMANAGER->frameRender("yellow", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
				//이미지 활용
				_yellow->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
			}
		}
		else // 문어 색깔 0 = red , 1 = blue , 2 = yellow
		{
			if (_octopus[i]._color == 0)
			{
				_destroy->frameRender(getMemDC(), _octopus[i].x - 64, _octopus[i].y - 32, _octopus[i].destroyX, 0);
			}
			if (_octopus[i]._color == 1)
			{
				_destroy1->frameRender(getMemDC(), _octopus[i].x - 64, _octopus[i].y - 32, _octopus[i].destroyX, 0);
			}
			if (_octopus[i]._color == 2)
			{
				_destroy2->frameRender(getMemDC(), _octopus[i].x - 64, _octopus[i].y - 32, _octopus[i].destroyX, 0);
			}
		}
		//문어 렉트 확인
		//Rectangle(getMemDC(), _octopus[i]._rc);
	}
}