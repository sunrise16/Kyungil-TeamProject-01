#include "stdafx.h"
#include "mushroom.h"
#include "player.h"

// 초기화 (init)
HRESULT mushroom::init()
{
	// 버섯 이미지 삽입
	_room = IMAGEMANAGER->addFrameImage("mushroom", "Images/Enemy/Mushroom/버섯괴물 2048 + 128 _ X16 Y1.bmp", 2048, 128, 16, 1, true, RGB(255, 0, 255));
	_destroy4 = IMAGEMANAGER->addFrameImage("destroy4", "Images/Enemy/Mushroom/버섯파괴 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));
	_getAtk = IMAGEMANAGER->addFrameImage("roomGetAtk", "Images/Enemy/Mushroom/버섯피격 384 + 512 _ X3 Y4.bmp", 384, 512, 3, 4, true, RGB(255, 0, 255));

	// 버섯 구조체 초기화
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

	// missile 클래스 동적 할당 생성
	_missile = new missile;
	_missile->init(30, 500);

	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void mushroom::release()
{
	// missile 클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);
}

// 업데이트 (update)
void mushroom::update()
{
	// 마우스 우클릭 시 버섯 생성
	if (INPUT->getKeyDown(VK_RBUTTON))
	{
		tagMushroom mushroom;
		mushroom.x = RANDOM->Range(0, WINSIZEX - 128);
		mushroom.y = RANDOM->Range(0, WINSIZEY - 128);
		mushroom._rc = RectMakeCenter(mushroom.x, mushroom.y + 30, 60, 60);		// 이미지 여백이 꽤 커서 렉트를 줄임;
		mushroom._hp = MUSHROOM_HP;
		mushroom._angle = PI_2;
		mushroom._speed = 1.0f;
		mushroom._count = 0;
		mushroom._dead = 0;
		mushroom.frameX = mushroom.frameY = 0;
		mushroom.hitFrameX = mushroom.hitFrameY = 0;
		mushroom._state = RANDOM->Range(0, 3);
		mushroom.destroyX = mushroom.destroyY = 0;
		mushroom._direction = RANDOM->Range(0, 1);
		_mushroom.push_back(mushroom);
	}

	// 버섯 행동
	for (int i = 0; i < _mushroom.size(); i++)
	{
		//_mushroom[i]._hp -= 1;			// 죽었을때 모션 확인
		if (_mushroom[i].x - 64 < 0)
		{	
			_mushroom[i].x = 64;
		}	
		if (_mushroom[i].x + 64 > WINSIZEX)
		{	
			_mushroom[i].x = WINSIZEX - 64;
		}	
		if (_mushroom[i].y - 64 < 0)
		{	
			_mushroom[i].y = 64;
		}	
		if (_mushroom[i].y + 64 > WINSIZEY)
		{	
			_mushroom[i].y = WINSIZEY - 64;
		}
		if (_mushroom[i].frameX < 8 || _mushroom[i].frameX > 13)
		{
			_mushroom[i].x += cosf(_mushroom[i]._angle) * _mushroom[i]._speed;
			_mushroom[i].y += -sinf(_mushroom[i]._angle) * _mushroom[i]._speed;
		}
		_mushroom[i]._count++;

		// 버섯 이동
		// 버섯의 체력이 0 이상일 때 (살아있을 때)
		if (_mushroom[i]._hp > 0)
		{
			// mushroom RECT 고정
			_mushroom[i]._rc = RectMakeCenter(_mushroom[i].x, _mushroom[i].y + 30, 60, 60);		// RECT 위치를 기준으로 이미지 업데이트

			// 버섯의 방향이 아래쪽일 때
			if (_mushroom[i]._state == MUSH_DOWN)
			{
				if (!_mushroom[i]._direction)			// 버섯 이동 각도
				{
					_mushroom[i]._angle += 0.03f;
				}
				else if (_mushroom[i]._direction)
				{
					_mushroom[i]._angle -= 0.03f;
				}
				if (_mushroom[i]._count % 20 == 0)		// 버섯 프레임 카운트
				{
					_mushroom[i].frameX++;
				}
				if (_mushroom[i].frameX > 15)			// 버섯 방향 초기화
				{
					_mushroom[i].frameX = 0;
					_mushroom[i]._state = RANDOM->Range(MUSH_DOWN, MUSH_UP);
					if (_mushroom[i]._state == MUSH_DOWN)
					{
						_mushroom[i]._angle = -(PI_2);
					}
					else if (_mushroom[i]._state == MUSH_LEFT)
					{
						_mushroom[i]._angle = (PI);
					}
					else if (_mushroom[i]._state == MUSH_RIGHT)
					{
						_mushroom[i]._angle = (PI2);
					}
					else if (_mushroom[i]._state == MUSH_UP)
					{
						_mushroom[i]._angle = (PI_2);
					}
					_mushroom[i]._count = RANDOM->Range(0, 30);
					_mushroom[i]._direction = RANDOM->Range(0, 1);
				}
			}
			// 버섯의 방향이 왼쪽일 때
			if (_mushroom[i]._state == MUSH_LEFT)
			{
				if (!_mushroom[i]._direction)			// 버섯 이동 각도
				{
					_mushroom[i]._angle += 0.03f;
				}
				else if (_mushroom[i]._direction)
				{
					_mushroom[i]._angle -= 0.03f;
				}
				if (_mushroom[i]._count % 20 == 0)		// 버섯 프레임 카운트
				{
					_mushroom[i].frameX++;
				}
				if (_mushroom[i].frameX > 15)			// 버섯 방향 초기화
				{
					_mushroom[i].frameX = 0;
					_mushroom[i]._state = RANDOM->Range(MUSH_DOWN, MUSH_UP);
					if (_mushroom[i]._state == MUSH_DOWN)
					{
						_mushroom[i]._angle = -(PI_2);
					}
					else if (_mushroom[i]._state == MUSH_LEFT)
					{
						_mushroom[i]._angle = (PI);
					}
					else if (_mushroom[i]._state == MUSH_RIGHT)
					{
						_mushroom[i]._angle = (PI2);
					}
					else if (_mushroom[i]._state == MUSH_UP)
					{
						_mushroom[i]._angle = (PI_2);
					}
					_mushroom[i]._count = RANDOM->Range(0, 30);
					_mushroom[i]._direction = RANDOM->Range(0, 1);
				}
			}
			// 버섯의 방향이 오른쪽일 때
			if (_mushroom[i]._state == MUSH_RIGHT)
			{
				if (!_mushroom[i]._direction)			// 버섯 이동 각도
				{
					_mushroom[i]._angle += 0.03f;
				}
				else if (_mushroom[i]._direction)
				{
					_mushroom[i]._angle -= 0.03f;
				}
				if (_mushroom[i]._count % 20 == 0)		// 버섯 프레임 카운트
				{
					_mushroom[i].frameX++;
				}
				if (_mushroom[i].frameX > 15)			// 버섯 방향 초기화
				{
					_mushroom[i].frameX = 0;
					_mushroom[i]._state = RANDOM->Range(MUSH_DOWN, MUSH_UP);
					if (_mushroom[i]._state == MUSH_DOWN)
					{
						_mushroom[i]._angle = -(PI_2);
					}
					else if (_mushroom[i]._state == MUSH_LEFT)
					{
						_mushroom[i]._angle = (PI);
					}
					else if (_mushroom[i]._state == MUSH_RIGHT)
					{
						_mushroom[i]._angle = (PI2);
					}
					else if (_mushroom[i]._state == MUSH_UP)
					{
						_mushroom[i]._angle = (PI_2);
					}
					_mushroom[i]._count = RANDOM->Range(0, 30);
					_mushroom[i]._direction = RANDOM->Range(0, 1);
				}
			}
			// 버섯의 방향이 위쪽일 때
			if (_mushroom[i]._state == MUSH_UP)
			{
				if (!_mushroom[i]._direction)			// 버섯 이동 각도
				{
					_mushroom[i]._angle += 0.03f;
				}
				else if (_mushroom[i]._direction)
				{
					_mushroom[i]._angle -= 0.03f;
				}
				if (_mushroom[i]._count % 20 == 0)		// 버섯 프레임 카운트
				{
					_mushroom[i].frameX++;
				}
				if (_mushroom[i].frameX > 15)			// 버섯 방향 초기화
				{
					_mushroom[i].frameX = 0;
					_mushroom[i]._state = RANDOM->Range(MUSH_DOWN, MUSH_UP);
					if (_mushroom[i]._state == MUSH_DOWN)
					{
						_mushroom[i]._angle = -(PI_2);
					}
					else if (_mushroom[i]._state == MUSH_LEFT)
					{
						_mushroom[i]._angle = (PI);
					}
					else if (_mushroom[i]._state == MUSH_RIGHT)
					{
						_mushroom[i]._angle = (PI2);
					}
					else if (_mushroom[i]._state == MUSH_UP)
					{
						_mushroom[i]._angle = (PI_2);
					}
					_mushroom[i]._count = RANDOM->Range(0, 30);
					_mushroom[i]._direction = RANDOM->Range(0, 1);
				}
			}

			// 버섯 피격
			// 위쪽에서 피격당했을 경우
			if (_mushroom[i]._state == MUSH_ATKDOWN)
			{
				_mushroom[i].hitFrameY = 0;
				if (_mushroom[i]._count % 10 == 0)		// 버섯 프레임 카운트
				{
					_mushroom[i].hitFrameX++;
				}
				if (_mushroom[i].hitFrameX > 2)			// 버섯 상태 초기화
				{
					_mushroom[i].hitFrameX = 0;
					_mushroom[i]._count = RANDOM->Range(0, 30);					// 움직임 카운트
					_mushroom[i]._state = RANDOM->Range(MUSH_DOWN, MUSH_UP);	// 상태값 조절
					_mushroom[i]._direction = RANDOM->Range(0, 1);				// 방향 조절
					_mushroom[i].frameX = 0;									// 프레임값 조절
				}
			}
			// 왼쪽에서 피격당했을 경우
			else if (_mushroom[i]._state == MUSH_ATKLEFT)
			{
				_mushroom[i].hitFrameY = 1;
				if (_mushroom[i]._count % 10 == 0)		// 버섯 프레임 카운트
				{
					_mushroom[i].hitFrameX++;
				}
				if (_mushroom[i].hitFrameX > 2)			// 버섯 상태 초기화
				{
					_mushroom[i].hitFrameX = 0;
					_mushroom[i]._count = RANDOM->Range(0, 30);					// 움직임 카운트
					_mushroom[i]._state = RANDOM->Range(MUSH_DOWN, MUSH_UP);	// 상태값 조절
					_mushroom[i]._direction = RANDOM->Range(0, 1);				// 방향 조절
					_mushroom[i].frameX = 0;									// 프레임값 조절
				}
			}
			// 오른쪽에서 피격당했을 경우
			else if (_mushroom[i]._state == MUSH_ATKRIGHT)
			{
				_mushroom[i].hitFrameY = 2;
				if (_mushroom[i]._count % 10 == 0)		// 버섯 프레임 카운트
				{
					_mushroom[i].hitFrameX++;
				}
				if (_mushroom[i].hitFrameX > 2)			// 버섯 상태 초기화
				{
					_mushroom[i].hitFrameX = 0;
					_mushroom[i]._count = RANDOM->Range(0, 30);					// 움직임 카운트
					_mushroom[i]._state = RANDOM->Range(MUSH_DOWN, MUSH_UP);	// 상태값 조절
					_mushroom[i]._direction = RANDOM->Range(0, 1);				// 방향 조절
					_mushroom[i].frameX = 0;									// 프레임값 조절
				}
			}
			// 아래쪽에서 피격당했을 경우
			else if (_mushroom[i]._state == MUSH_ATKUP)
			{
				_mushroom[i].hitFrameY = 3;
				if (_mushroom[i]._count % 10 == 0)		// 버섯 프레임 카운트
				{
					_mushroom[i].hitFrameX++;
				}
				if (_mushroom[i].hitFrameX > 2)			// 버섯 상태 초기화
				{
					_mushroom[i].hitFrameX = 0;
					_mushroom[i]._count = RANDOM->Range(0, 30);					// 움직임 카운트
					_mushroom[i]._state = RANDOM->Range(MUSH_DOWN, MUSH_UP);	// 상태값 조절
					_mushroom[i]._direction = RANDOM->Range(0, 1);				// 방향 조절
					_mushroom[i].frameX = 0;									// 프레임값 조절
				}
			}

			// 플레이어 공격에 피격
			RECT temp;
			if (IntersectRect(&temp, &_playerAdress->getAttack(), &_mushroom[i]._rc))
			{
				if (_playerAdress->getAttack().right < _mushroom[i].x && _playerAdress->getAttack().bottom > _mushroom[i]._rc.top&& _playerAdress->getAttack().top < _mushroom[i]._rc.bottom)
				{
					_mushroom[i].x += 30;
					_mushroom[i]._state = MUSH_ATKLEFT;
				}
				else if (_playerAdress->getAttack().left > _mushroom[i].x&& _playerAdress->getAttack().bottom > _mushroom[i]._rc.top&& _playerAdress->getAttack().top < _mushroom[i]._rc.bottom)
				{
					_mushroom[i].x -= 30;
					_mushroom[i]._state = MUSH_ATKRIGHT;
				}
				else if (_playerAdress->getAttack().top < _mushroom[i].y && _playerAdress->getAttack().right > _mushroom[i]._rc.left&& _playerAdress->getAttack().left < _mushroom[i]._rc.right)
				{
					_mushroom[i].y += 30;
					_mushroom[i]._state = MUSH_ATKUP;
				}
				else if (_playerAdress->getAttack().bottom > _mushroom[i].y&& _playerAdress->getAttack().right > _mushroom[i]._rc.left&& _playerAdress->getAttack().left < _mushroom[i]._rc.right)
				{
					_mushroom[i].y -= 30;
					_mushroom[i]._state = MUSH_ATKDOWN;
				}
				_mushroom[i]._hp -= 100;			// 플레이어 공격력이어야 함
			}
		}
	}

	// 버섯 사망
	for (int i = 0; i < _mushroom.size(); i++)
	{
		if (_mushroom[i]._hp <= 0)
		{
			_mushroom[i]._hp = 0;
			_mushroom[i]._dead++;
			_mushroom[i]._rc = RectMakeCenter(_mushroom[i].x, _mushroom[i].y, 0, 0);
			if (_mushroom[i]._dead % 10 == 0)
			{
				_mushroom[i].destroyX++;
			}
			if (_mushroom[i].destroyX > 8)
			{
				//_mushroom[i]._hp = 30;
				_mushroom.erase(_mushroom.begin() + i);
			}
		}
	}

	// missile 클래스 업데이트
	_missile->update();
}

// 렌더 (render)
void mushroom::render()
{
	// 버섯 렌더
	for (int i = 0; i < _mushroom.size(); i++)
	{
		Rectangle(getMemDC(), _mushroom[i]._rc);		// 충돌 판정 RECT 위치 확인용

		if (_mushroom[i]._hp > 0)
		{
			if (_mushroom[i]._state >= MUSH_DOWN && _mushroom[i]._state <= MUSH_UP)
			{
				_room->frameRender(getMemDC(), _mushroom[i].x - 64, _mushroom[i].y - 64, _mushroom[i].frameX, 0);
			}
			else if (_mushroom[i]._state == MUSH_ATKDOWN)
			{
				_getAtk->frameRender(getMemDC(), _mushroom[i].x - 64, _mushroom[i].y - 64, _mushroom[i].hitFrameX, _mushroom[i].hitFrameY);
			}
			else if (_mushroom[i]._state == MUSH_ATKLEFT)
			{
				_getAtk->frameRender(getMemDC(), _mushroom[i].x - 64, _mushroom[i].y - 64, _mushroom[i].hitFrameX, _mushroom[i].hitFrameY);
			}
			else if (_mushroom[i]._state == MUSH_ATKRIGHT)
			{
				_getAtk->frameRender(getMemDC(), _mushroom[i].x - 64, _mushroom[i].y - 64, _mushroom[i].hitFrameX, _mushroom[i].hitFrameY);
			}
			else if (_mushroom[i]._state == MUSH_ATKUP)
			{
				_getAtk->frameRender(getMemDC(), _mushroom[i].x - 64, _mushroom[i].y - 64, _mushroom[i].hitFrameX, _mushroom[i].hitFrameY);
			}
		}
		else
		{
			_destroy4->frameRender(getMemDC(), _mushroom[i].x - 64, _mushroom[i].y - 32, _mushroom[i].destroyX, 0);
		}
		// 문어 RECT 확인
		// Rectangle(getMemDC(), _octopus[i]._rc);
	}

	// missile 클래스 렌더
	_missile->render();
}