#include "stdafx.h"
#include "octopus.h"
#include "player.h"

// 초기화 (init)
HRESULT octopus::init(float x, float y)
{
	// 문어 이미지 추가
	_red = IMAGEMANAGER->addFrameImage("red", "Images/Enemy/Octopus/빨간문어 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_blue = IMAGEMANAGER->addFrameImage("blue", "Images/Enemy/Octopus/하늘색문어 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_yellow = IMAGEMANAGER->addFrameImage("yellow", "Images/Enemy/Octopus/노란문어 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_destroy1 = IMAGEMANAGER->addFrameImage("destroy1", "Images/Enemy/Octopus/문어파괴 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));
	_destroy2 = IMAGEMANAGER->addFrameImage("destroy2", "Images/Enemy/Octopus/문어파괴1 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));
	_destroy3 = IMAGEMANAGER->addFrameImage("destroy3", "Images/Enemy/Octopus/문어파괴2 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));

	
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

	// 문어 구조체 초기화
	tagOctopus octopus;
	ZeroMemory(&octopus, sizeof(tagOctopus));

	octopus.x = x;
	octopus.y = y;
	octopus._rc = RectMakeCenter(octopus.x, octopus.y, 60, 64);
	octopus._hp = MINION_HP;
	octopus._angle = PI_2;
	octopus._speed = 3.0f;
	octopus.frameX = 0;
	octopus.frameY = RANDOM->Range(OCTO_DOWN, OCTO_UP);
	octopus._state = RANDOM->Range(0, 3);
	octopus.destroyX = octopus.destroyY = 0;
	octopus._color = RANDOM->Range(0, 2);
	_octopus.push_back(octopus);


	// missile 클래스 동적 할당 생성
	_missile = new missile;
	_missile->init(30, 500);

	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void octopus::release()
{
	// missile 클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);
}

// 업데이트 (update)
void octopus::update(int _scrollX, int _scrollY, bool isStart, bool playerSet)
{
	// 문어 행동
	for (int i = 0; i < _octopus.size(); i++)
	{

		_octopus[i].y += (scrollY - _scrollY) * 64;
		_octopus[i].x += (scrollX - _scrollX) * 64;
		// octopus RECT 고정
		_octopus[i]._rc = RectMakeCenter(_octopus[i].x, _octopus[i].y, 60, 64);		// RECT 위치를 기준으로 이미지 업데이트

		//_octopus[i]._hp -= 1;					// 죽었을 때 모션 확인 (테스트용)
		//if (_octopus[i].x - 32 < 0)
		//{
		//	_octopus[i].x = 32;
		//}
		//if (_octopus[i].x + 32 > TILESIZEX)
		//{
		//	_octopus[i].x = TILESIZEX - 32;
		//}
		//if (_octopus[i].y - 40 < 0)
		//{
		//	_octopus[i].y = 40;
		//}
		//if (_octopus[i].y + 40 > TILESIZEY)
		//{
		//	_octopus[i].y = TILESIZEY - 40;
		//}
		if (isStart)
		{

			// 문어 이동
			// 문어의 체력이 0 이상일 때 (살아있을 때)
			if (_octopus[i]._hp > 0)
			{
				// 문어의 방향이 왼쪽일 때
				if (_octopus[i].frameY == OCTO_LEFT)
				{
					_octopus[i].x -= 0.5;					// 자동 움직임
					_octopus[i]._count++;
					if (_octopus[i]._count % 50 == 0)
					{
						_octopus[i].frameX++;
					}
					if (_octopus[i].frameX > 3)				// 문어 공격 모션, 이동 정지
					{
						_octopus[i].x += 0.5;
					}
					if (_octopus[i]._count % 250 == 0)		// 문어 공격
					{
						_missile->fire(_octopus[i].x - 40, _octopus[i].y - 5, PI);
					}
					if (_octopus[i].frameX > 5)
					{
						_octopus[i].frameX = 0;
						_octopus[i].frameY = RANDOM->Range(OCTO_DOWN, OCTO_UP);
						_octopus[i]._count = RANDOM->Range(0, 30);
					}
				}
				// 문어의 방향이 오른쪽일 때
				else if (_octopus[i].frameY == OCTO_RIGHT)
				{
					_octopus[i].x += 0.5;					// 자동 움직임
					_octopus[i]._count++;
					if (_octopus[i]._count % 50 == 0)
					{
						_octopus[i].frameX++;
					}
					if (_octopus[i].frameX > 3)				// 문어 공격 모션, 이동 정지
					{
						_octopus[i].x -= 0.5;
					}
					if (_octopus[i]._count % 250 == 0)		// 문어 공격
					{
						_missile->fire(_octopus[i].x + 40, _octopus[i].y - 5, PI2);
					}
					if (_octopus[i].frameX > 5)
					{
						_octopus[i].frameX = 0;
						_octopus[i].frameY = RANDOM->Range(OCTO_DOWN, OCTO_UP);
						_octopus[i]._count = RANDOM->Range(0, 30);
					}
				}
				// 문어의 방향이 위쪽일 때
				else if (_octopus[i].frameY == OCTO_UP)
				{
					_octopus[i].y -= 0.5;					// 자동 움직임
					_octopus[i]._count++;
					if (_octopus[i]._count % 50 == 0)
					{
						_octopus[i].frameX++;
					}
					if (_octopus[i].frameX > 3)				// 문어 공격 모션, 이동 정지
					{
						_octopus[i].y += 0.5;
					}
					if (_octopus[i]._count % 250 == 0)		// 문어 공격
					{
						_missile->fire(_octopus[i].x, _octopus[i].y - 32, PI_2);
					}
					if (_octopus[i].frameX > 5)
					{
						_octopus[i].frameX = 0;
						_octopus[i].frameY = RANDOM->Range(OCTO_DOWN, OCTO_UP);
						_octopus[i]._count = RANDOM->Range(0, 30);
					}
				}
				// 문어의 방향이 아래쪽일 때
				else if (_octopus[i].frameY == OCTO_DOWN)
				{
					_octopus[i].y += 0.5;					// 자동 움직임
					_octopus[i]._count++;
					if (_octopus[i]._count % 50 == 0)
					{
						_octopus[i].frameX++;
					}
					if (_octopus[i].frameX > 3)				// 문어 공격 모션, 이동 정지
					{
						_octopus[i].y -= 0.5;
					}
					if (_octopus[i]._count % 250 == 0)		// 문어 공격
					{
						_missile->fire(_octopus[i].x, _octopus[i].y + 32, -(PI_2));
					}
					if (_octopus[i].frameX > 5)
					{
						_octopus[i].frameX = 0;
						_octopus[i].frameY = RANDOM->Range(OCTO_DOWN, OCTO_UP);
						_octopus[i]._count = RANDOM->Range(0, 30);
					}
				}

				if (playerSet)
				{
					// 플레이어 공격과 충돌 처리
					RECT temp;
					if (IntersectRect(&temp, &_playerAdress->getAttack(), &_octopus[i]._rc))
					{
						if (_playerAdress->getAttack().right < _octopus[i].x && _playerAdress->getAttack().bottom > _octopus[i]._rc.top && _playerAdress->getAttack().top < _octopus[i]._rc.bottom)
						{
							_octopus[i].x += 30;
							_octopus[i].frameY = OCTO_LEFT;
						}
						else if (_playerAdress->getAttack().left > _octopus[i].x && _playerAdress->getAttack().bottom > _octopus[i]._rc.top&& _playerAdress->getAttack().top < _octopus[i]._rc.bottom)
						{
							_octopus[i].x -= 30;
							_octopus[i].frameY = OCTO_RIGHT;
						}
						else if (_playerAdress->getAttack().top < _octopus[i].y && _playerAdress->getAttack().right > _octopus[i]._rc.left&& _playerAdress->getAttack().left < _octopus[i]._rc.right)
						{
							_octopus[i].y += 30;
							_octopus[i].frameY = OCTO_UP;
						}
						else if (_playerAdress->getAttack().bottom > _octopus[i].y && _playerAdress->getAttack().right > _octopus[i]._rc.left&& _playerAdress->getAttack().left < _octopus[i]._rc.right)
						{
							_octopus[i].y -= 30;
							_octopus[i].frameY = OCTO_DOWN;
						}
						_octopus[i].frameX = 4;
						_octopus[i]._count = 200;
						_octopus[i]._hp -= 100;			// 플레이어 공격력이어야 함
					}

				}
				
			}
		}

		

		// 문어 사망
		for (int i = 0; i < _octopus.size(); i++)
		{
			if (_octopus[i]._hp <= 0)
			{
				_octopus[i]._hp = 0;
				_octopus[i]._count++;
				_octopus[i]._rc = RectMakeCenter(_octopus[i].x, _octopus[i].y, 0, 0);
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
		// missile 클래스 업데이트
		_missile->update();
	}

	scrollX = _scrollX;
	scrollY = _scrollY;
}

// 렌더 (render)
void octopus::render()
{
	// 문어 렌더
	for (int i = 0; i < _octopus.size(); i++)
	{
		Rectangle(getMemDC(), _octopus[i]._rc);			// 문어 RECT 확인 (테스트용)

		// 문어 색깔 (0 = red , 1 = blue , 2 = yellow)
		// 문어가 살아있을 때
		if (_octopus[i]._hp > 0)
		{
			if (_octopus[i]._color == 0)
			{
				// RECT 활용
				// IMAGEMANAGER->frameRender("red", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top,_octopus[i].frameX,_octopus[i].frameY);
				// 이미지 활용
				_red->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
			}
			if (_octopus[i]._color == 1)
			{
				// RECT 활용
				// IMAGEMANAGER->frameRender("blue", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
				// 이미지 활용
				_blue->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
			}
			if (_octopus[i]._color == 2)
			{
				// RECT 활용
				// IMAGEMANAGER->frameRender("yellow", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
				// 이미지 활용
				_yellow->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
			}
		}
		// 문어가 죽었을 때
		else
		{
			// 사망 모션 출력
			if (_octopus[i]._color == 0)
			{
				_destroy1->frameRender(getMemDC(), _octopus[i].x - 64, _octopus[i].y - 32, _octopus[i].destroyX, 0);
			}
			if (_octopus[i]._color == 1)
			{
				_destroy2->frameRender(getMemDC(), _octopus[i].x - 64, _octopus[i].y - 32, _octopus[i].destroyX, 0);
			}
			if (_octopus[i]._color == 2)
			{
				_destroy3->frameRender(getMemDC(), _octopus[i].x - 64, _octopus[i].y - 32, _octopus[i].destroyX, 0);
			}
		}
		
	}

	// missile 클래스 렌더
	_missile->render();

}