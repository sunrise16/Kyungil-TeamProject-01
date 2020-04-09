#include "stdafx.h"
#include "octopus.h"

HRESULT octopus::init()
{
	//문어 이미지 삽입
	_red = IMAGEMANAGER->addFrameImage("red", "그림파일/빨간문어 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_blue = IMAGEMANAGER->addFrameImage("blue", "그림파일/하늘색문어 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_yellow = IMAGEMANAGER->addFrameImage("yellow", "그림파일/노란문어 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));

	//문어 구조체 초기화
	for (int i = 0; i < MINION_MAX; i++)
	{
		//문어렉트 위치 랜덤 생성
		_octopus[i].x = RANDOM->Range(0, WINSIZEX - 80);
		_octopus[i].y = RANDOM->Range(0, WINSIZEY - 64);
		_octopus[i]._hp = MINION_HP;
		_octopus[i]._angle = PI_2;
		_octopus[i]._speed = 3.0f;
		_octopus[i].frameX = 0;
		_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
		_octopus[i]._state = RANDOM->Range(0, 3);
	}


	return S_OK;
}

void octopus::release()
{
}

void octopus::update()
{
	for (int i = 0; i < MINION_MAX; i++)
	{
		if (_octopus[i].frameY == octo_DOWN)
		{
			_octopus[i].y += 0.5;
			_octopus[i]._count++;
			if (_octopus[i]._count % 50 == 0)
			{
				_octopus[i].frameX++;
			}
			if (_octopus[i].frameX >= 4 && _octopus[i].frameX <= 5)			//문어 대포모션, 이동 정지
			{
				_octopus[i].y -= 0.5;
			}
			if (_octopus[i].frameX > 5)
			{
				_octopus[i].frameX = 0;
				_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
			}
		}
		else if (_octopus[i].frameY == octo_LEFT)
		{
			_octopus[i].x -= 0.5;
			_octopus[i]._count++;
			if (_octopus[i]._count % 50 == 0)
			{
				_octopus[i].frameX++;
			}
			if (_octopus[i].frameX >= 4 && _octopus[i].frameX <= 5)			//문어 대포모션, 이동 정지
			{
				_octopus[i].x += 0.5;
			}
			if (_octopus[i].frameX > 5)
			{
				_octopus[i].frameX = 0;
				_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
			}
		}
		else if (_octopus[i].frameY == octo_RIGHT)
		{
			_octopus[i].x += 0.5;
			_octopus[i]._count++;
			if (_octopus[i]._count % 50 == 0)
			{
				_octopus[i].frameX++;
			}
			if (_octopus[i].frameX >= 4 && _octopus[i].frameX <= 5)			//문어 대포모션, 이동 정지
			{
				_octopus[i].x -= 0.5;
			}
			if (_octopus[i].frameX > 5)
			{
				_octopus[i].frameX = 0;
				_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
			}
		}
		else if (_octopus[i].frameY == octo_UP)
		{
			_octopus[i].y -= 0.5;
			_octopus[i]._count++;
			if (_octopus[i]._count % 50 == 0)
			{
				_octopus[i].frameX++;
			}
			if (_octopus[i].frameX >= 4 && _octopus[i].frameX <= 5)			//문어 대포모션, 이동 정지
			{
				_octopus[i].y += 0.5;
			}
			if (_octopus[i].frameX > 5)
			{
				_octopus[i].frameX = 0;
				_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
			}
		}
	}
}

void octopus::render()
{
	for (int i = 0; i < MINION_MAX; i++)
	{
		if (i < 3)
		{
			//렉트 활용
			//IMAGEMANAGER->frameRender("red", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top,_octopus[i].frameX,_octopus[i].frameY);
			//이미지 활용
			_red->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
		}
		if (i >= 3 && i < 6)
		{
			//렉트 활용
			//IMAGEMANAGER->frameRender("blue", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
			//이미지 활용
			_blue->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);

		}
		if (i >= 6 && i < MINION_MAX)
		{
			//렉트 활용
			//IMAGEMANAGER->frameRender("yellow", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
			//이미지 활용
			_yellow->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);

		}
		//문어 렉트 확인
		//Rectangle(getMemDC(), _octopus[i]._rc);
	}
}