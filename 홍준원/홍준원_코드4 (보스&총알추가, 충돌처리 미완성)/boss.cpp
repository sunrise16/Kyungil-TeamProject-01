#include "stdafx.h"
#include "boss.h"
#include "player.h"

HRESULT boss::init()
{
	// 보스 이미지 추가
	_bossIdle = IMAGEMANAGER->addFrameImage("보스기본", "Images/Enemy/Boss/보스기본이미지 12288 + 512 _ X32 Y1.bmp", 12288, 512, 32, 1, true, RGB(255, 0, 255));
	_fireBall = IMAGEMANAGER->addFrameImage("파이어볼시전", "Images/Enemy/Boss/파이어볼시전 2496 + 480 _ X6 Y1.bmp", 2496, 480, 6, 1, true, RGB(255, 0, 255));
	_teleportS = IMAGEMANAGER->addFrameImage("텔레포트시작", "Images/Enemy/Boss/텔레포트시전 3584 + 480 _ X7 Y1.bmp", 3584, 480, 7, 1, true, RGB(255, 0, 255));
	_teleportE = IMAGEMANAGER->addFrameImage("텔레포트도착", "Images/Enemy/Boss/텔레포트도착 4096 + 480 _ X8 Y1.bmp", 4096, 480, 8, 1, true, RGB(255, 0, 255));
	//_eyeShield = IMAGEMANAGER->addFrameImage("아이쉴드", "Images/Enemy/Boss/아이쉴드 1280 + 128 _ X10 Y1.bmp", 1280, 128, 10, 1, true, RGB(255, 0, 255));

	// 보스 구조체 초기화
	tagBoss boss;
	ZeroMemory(&boss, sizeof(tagBoss));

	// missile 클래스 동적 할당 생성
	_missile = new missileB;
	_missile->init(20, 1500);

	_missileE = new missileE;
	_missileE->init(20, 1500);

	_missileE2 = new missileE2;
	_missileE2->init(20, 3000);


	return S_OK;
}

void boss::release()
{
	// missile 클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);
	_missileE->release();
	SAFE_DELETE(_missileE);
	_missileE2->release();
	SAFE_DELETE(_missileE2);
}

void boss::update()
{
	// F1 보스 추가
	if (INPUT->getKeyDown(VK_F4))
	{
		tagBoss boss;
		boss.x = RANDOM->Range(0, WINSIZEX - 480);
		boss.y = RANDOM->Range(0, WINSIZEY - 512);
		boss._rc = RectMakeCenter(boss.x, boss.y + 30, 300, 300);		// 이미지 여백이 꽤 커서 렉트를 줄임;
		boss._hp = BOSS_HP;
		boss._angle = -(PI_2);
		boss._speed = 3.0f;
		boss.frameX = boss.frameY = 0;
		boss.fireFrameX = boss.fireFrameY = 0;
		boss._state = BOSS_IDLE;
		boss._direction = RANDOM->Range(0, 1);
		boss.destroyX = boss.destroyY = 0;
		boss._count = 0;
		boss._dead = 0;
		_boss.push_back(boss);
	}

	for (int i = 0; i < _boss.size(); i++)
	{
		//_boss[i]._hp -= 1;															//죽었을때 모션 확인

		if (_boss[i].x - 64 < 0)
		{
			_boss[i].x = 64;
		}
		if (_boss[i].x + 64 > WINSIZEX)
		{
			_boss[i].x = WINSIZEX - 64;
		}
		if (_boss[i].y - 64 < 0)
		{
			_boss[i].y = 64;
		}
		if (_boss[i].y + 64 > WINSIZEY)
		{
			_boss[i].y = WINSIZEY - 64;
		}

		if (_boss[i].frameX > 26)
		{
			_boss[i].x += cosf(_boss[i]._angle) * _boss[i]._speed;
			_boss[i].y += -sinf(_boss[i]._angle) * _boss[i]._speed;
		}
		

		//보스가 살아있을 때
		if (_boss[i]._hp > 0)
		{
			_boss[i]._count++;
			_boss[i]._rc = RectMakeCenter(_boss[i].x, _boss[i].y + 30, 300, 400);	//렉트 위치 이미지기준 업데이트
			//버섯방향 (아래쪽)
			if (_boss[i]._state == BOSS_IDLE)
			{
				
				if (!_boss[i]._direction)			//보스 이동각도
				{
					_boss[i]._angle += 0.03f;
				}
				else if (_boss[i]._direction)
				{
					_boss[i]._angle -= 0.03f;
				}
			}
			if (_boss[i]._count % 250 == 0)
			{
				_boss[i]._direction = RANDOM->Range(0, 1);
			}
			if (_boss[i]._count % 500 == 0)
			{
				_boss[i]._angle = RANDOM->Range(-3.141592f, 3.141592f);
			}
			if(_boss[i]._count % 500 == 0)
			{
				_boss[i]._state = BOSS_FIREBALL;
			}
			switch (_boss[i]._state)				//보스 상태
			{
			case(BOSS_IDLE):
				if (_boss[i]._count % 10 == 0)
				{
					_boss[i].frameX++;
					if (_boss[i].frameX > 31)		//보스 방향 초기화
					{
						_boss[i].frameX = 27;
					}
				}
				break;
			case(BOSS_FIREBALL):
				if (_boss[i]._count % 20 == 0)
				{
					_boss[i].fireFrameX++;
					if (_boss[i].fireFrameX > 5)
					{
						_boss[i].fireFrameX = 0;
						_missileE2->fire(_boss[i].x,_boss[i].y,PI2);
						_missile->fire(_boss[i].x, _boss[i].y, PI_4);
						_missileE2->fire(_boss[i].x, _boss[i].y, PI_2);
						_missile->fire(_boss[i].x, _boss[i].y, PI * 0.8);
						_missileE2->fire(_boss[i].x, _boss[i].y, PI);
						_missile->fire(_boss[i].x, _boss[i].y, -(PI_4));
						_missileE2->fire(_boss[i].x, _boss[i].y, -(PI_2));
						_missile->fire(_boss[i].x, _boss[i].y, -(PI * 0.8));
						//_missileE->fire(_boss[i].x, _boss[i].y, PI_2);
						_boss[i]._state = BOSS_IDLE;
					}
				}
				break;
			case(BOSS_TELESTART):
				break;
			case(BOSS_TELEEND):
				break;
			case(BOSS_DEAD):
				break;
			}
		}
		if (_boss[i]._hp < 10000)			// 2페이즈
		{

		}
		
		
	}
	// missile 클래스 업데이트
	_missile->update();
	_missileE->update();
	_missileE2->update();
}

void boss::render()
{
	for (int i = 0; i < _boss.size(); i++)
	{
		if (_boss[i]._state == BOSS_IDLE)
		{
			IMAGEMANAGER->frameRender("보스기본", getMemDC(), _boss[i]._rc.left - 45, _boss[i]._rc.top - 90, _boss[i].frameX, 0);
		}
		else if (_boss[i]._state == BOSS_FIREBALL)
		{
			IMAGEMANAGER->frameRender("파이어볼시전", getMemDC(), _boss[i]._rc.left - 50, _boss[i]._rc.top - 90, _boss[i].fireFrameX, 0);
		}
		else if (_boss[i]._state == BOSS_TELESTART)
		{
			IMAGEMANAGER->frameRender("텔레포트시작", getMemDC(), _boss[i]._rc.left - 45, _boss[i]._rc.top - 90, _boss[i].frameX, 0);
		}
		else if (_boss[i]._state == BOSS_TELEEND)
		{
			IMAGEMANAGER->frameRender("텔레포트도착", getMemDC(), _boss[i]._rc.left - 45, _boss[i]._rc.top - 90, _boss[i].frameX, 0);
		}
	}

	// missile 클래스 렌더
	_missile->render();
	_missileE->render();
	_missileE2->render();
}



