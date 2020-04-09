#include "stdafx.h"
#include "player.h"
#include "octopus.h"

// 초기화 (init)
HRESULT player::init()
{
	// inventory 클래스 동적 할당 생성
	_inventory = new inventory;
	_inventory->init();

	// 플레이어 중심 좌표 초기화
	playerCenter.x = WINSIZEX / 2;
	playerCenter.y = WINSIZEY / 2;

	// 플레이어 이미지 초기화 (기본 스탠딩, 체력, 이동)
	_playerImage = IMAGEMANAGER->addImage("플레이어앞모습", "Images/Player/링크앞모습.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerHP = IMAGEMANAGER->addFrameImage("플레이어체력", "Images/Player/하트 400+80_X5Y1.bmp", 200, 50, 5, 1);
	_playerLeft = IMAGEMANAGER->addFrameImage("플레이어왼쪽이동", "Images/Player/링크옆으로걷기_230+23_10장.bmp", 640, 64, 10, 1);
	_playerRight = IMAGEMANAGER->addFrameImage("플레이어오른쪽이동", "Images/Player/링크오른쪽옆으로걷기_230+23_10장.bmp", 640, 64, 10, 1);
	_playerUp = IMAGEMANAGER->addFrameImage("플레이어위쪽이동", "Images/Player/링크위로걷기_180+26_10장.bmp", 640, 64, 10, 1);
	_playerDown = IMAGEMANAGER->addFrameImage("플레이어아래쪽이동", "Images/Player/링크앞으로걷기_180+24_10장.bmp", 640, 64, 10, 1);

	// 플레이어 이미지 초기화 (공격) (가로, 세로가 80인 이유는 64가 너무 작기 때문)
	_playerLeftAtk = IMAGEMANAGER->addFrameImage("플레이어왼쪽공격", "Images/Player/링크옆으로공격_609+25_29장.bmp", 2320, 80, 29, 1);
	_playerRightAtk = IMAGEMANAGER->addFrameImage("플레이어오른쪽공격", "Images/Player/링크오른쪽옆으로공격_609+25_29장.bmp", 2320, 80, 29, 1);
	_playerUpAtk = IMAGEMANAGER->addFrameImage("플레이어위쪽공격", "Images/Player/링크뒤로공격_638+28_11장.bmp", 880, 80, 11, 1);
	_playerDownAtk = IMAGEMANAGER->addFrameImage("플레이어앞쪽공격", "Images/Player/링크앞으로공격_209+24_11장.bmp", 880, 80, 11, 1);

	// 플레이어 이미지 초기화 (피격)
	_playerGetAtk = IMAGEMANAGER->addFrameImage("플레이어피격", "Images/Player/링크피격_125+24_5장.bmp", 320, 64, 5, 1);
	
	// 플레이어 RECT 초기화 (일반)
	playerRc = RectMakeCenter(playerCenter.x, playerCenter.y, 64, 64);
	
	// 플레이어 RECT 초기화 (피격 판정 RECT)
	playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 32, 10, 10);
	playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 32, 10, 10);
	playerGetAtkTopRc = RectMakeCenter(playerRc.left + 32, playerRc.top, 10, 10);
	playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 32, playerRc.bottom, 10, 10);
	
	// 기타 변수 초기화
	hpCount = 4;
	count = 0;
	index = 0;
	// 이동 bool 변수
	playerLeft = false;
	playerRight = false;
	playerUp = false;
	playerDown = false;
	// 공격 bool 변수
	playerLeftAtk = false;
	playerRightAtk = false;
	playerUpAtk = false;
	playerDownAtk = false;
	// 피격 bool 변수
	playerGetAtkLeft = false;
	playerGetAtkRight = false;
	playerGetAtkTop = false;
	playerGetAtkBottom = false;
	playerGetAtk = false;

	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void player::release()
{
	// inventory 클래스 해제
	_inventory->release();
	SAFE_DELETE(_inventory);
}

// 업데이트 (update)
void player::update()
{
	// 기본 상태 설정
	playerState = PLAYER_STATE_IDLE;

	// 캐릭터 이동 (대각선 이동이 불가능하게 if, else if로 처리)
	// 왼쪽 이동
	if (INPUT->getKey(VK_LEFT) && playerRc.left >= 0)
	{
		// 왼쪽 이동하는 상태로 변경
		playerLeft = true;
		playerState = PLAYER_STATE_LEFT;

		// 좌표 변경
		playerRc.left -= 3;
		playerRc.right -= 3;

		// 왼쪽 공격
		if (INPUT->getKey(VK_SPACE))
		{
			// 왼쪽 공격하는 상태로 변경
			playerLeftAtk = true;
			playerState = PLAYER_STATE_LEFTATK;

			// 기본 스탠딩 상태 RECT 크기와 공격 상태 RECT 크기가 다르므로 피격 판정 RECT를 다시 설정
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 40, 10, 10);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 40, 10, 10);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 40, playerRc.top, 10, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 40, playerRc.bottom, 10, 10);

		}
	}
	// 오른쪽 이동
	else if (INPUT->getKey(VK_RIGHT) && playerRc.right <= WINSIZEX)
	{
		// 오른쪽 이동하는 상태로 변경
		playerRight = true;
		playerState = PLAYER_STATE_RIGHT;

		// 좌표 변경
		playerRc.left += 3;
		playerRc.right += 3;

		// 오른쪽 공격
		if (INPUT->getKey(VK_SPACE))
		{
			// 오른쪽 공격하는 상태로 변경
			playerRightAtk = true;
			playerState = PLAYER_STATE_RIGHTATK;

			// 기본 스탠딩 상태 RECT 크기와 공격 상태 RECT 크기가 다르므로 피격 판정 RECT를 다시 설정
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 40, 10, 10);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 40, 10, 10);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 40, playerRc.top, 10, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 40, playerRc.bottom, 10, 10);

		}
	}
	// 위쪽 이동
	else if (INPUT->getKey(VK_UP) && playerRc.top >= 0)
	{
		// 위쪽 이동하는 상태로 변경
		playerUp = true;
		playerState = PLAYER_STATE_UP;

		// 좌표 변경
		playerRc.top -= 3;
		playerRc.bottom -= 3;

		// 위쪽 공격
		if (INPUT->getKey(VK_SPACE))
		{
			// 위쪽 공격하는 상태로 변경
			playerUpAtk = true;
			playerState = PLAYER_STATE_UPATK;

			// 기본 스탠딩 상태 RECT 크기와 공격 상태 RECT 크기가 다르므로 피격 판정 RECT를 다시 설정
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 40, 10, 10);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 40, 10, 10);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 40, playerRc.top, 10, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 40, playerRc.bottom, 10, 10);
		}
	}
	// 아래쪽 이동
	else if (INPUT->getKey(VK_DOWN) && playerRc.bottom <= WINSIZEY)
	{
		// 아래쪽 이동하는 상태로 변경
		playerDown = true;
		playerState = PLAYER_STATE_DOWN;

		// 좌표 변경
		playerRc.top += 3;
		playerRc.bottom += 3;

		// 아래쪽 이동
		if (INPUT->getKey(VK_SPACE))
		{
			// 아래쪽 공격하는 상태로 변경
			playerDownAtk = true;
			playerState = PLAYER_STATE_DOWNATK;

			// 기본 스탠딩 상태 RECT 크기와 공격 상태 RECT 크기가 다르므로 피격 판정 RECT를 다시 설정
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 40, 10, 10);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 40, 10, 10);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 40, playerRc.top, 10, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 40, playerRc.bottom, 10, 10);
		}
	}

	// 피격 판정 RECT 좌표 설정
	playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 32, 10, 10);
	playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 32, 10, 10);
	playerGetAtkTopRc = RectMakeCenter(playerRc.left + 32, playerRc.top, 10, 10);
	playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 32, playerRc.bottom, 10, 10);

	// if(IntersectRect(&empty, &_getAtkleftRc, &/*오빠 렉트 적어주세요*/)
	// {
	//	_hpCount--;
	// }
	// else if (IntersectRect(&empty, &_getAtkrightRc, &/*오빠 렉트 적어주세요*/)
	// {
	// 	_hpCount--;
	// }
	// else if (IntersectRect(&empty, &_getAtktopRc, &/*오빠 렉트 적어주세요*/)
	// {
	//	_hpCount--;
	// }
	// else if (IntersectRect(&empty, &_getAtkbottomRc, &/*오빠 렉트 적어주세요*/)
	// {
	// 	_hpCount--;
	// }

	// 피격 시 체력 감소
	if (!_octopusAdress->getOctopus().empty())
	{
		for (int i = 0; i < _octopusAdress->getOctopus().size(); i++)
		{
			// 왼쪽 충돌
			if (IntersectRect(&empty, &playerGetAtkLeftRc, &_octopusAdress->getOctopus()[i]._rc))
			{
				hpCount--;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;

				if (count > 5000)
				{
					playerState = PLAYER_STATE_IDLE;
					count = 0;
				}
			}
			// 오른쪽 충돌
		}
	}

	// inventory 클래스 업데이트
	_inventory->update();

	// 애니메이션 출력
	this->animation();
}

// 렌더 (render)
void player::render()
{
	// 임시 RECT 렌더
	Rectangle(getMemDC(), playerRc);

	// 플레이어 현재 상태 출력 (이동)
	if (playerState == PLAYER_STATE_IDLE)
	{
		_playerImage->render(getMemDC(), playerRc.left, playerRc.top);
	}
	if (playerState == PLAYER_STATE_LEFT)
	{
		_playerLeft->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}
	if (playerState == PLAYER_STATE_RIGHT)
	{
		_playerRight->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}
	if (playerState == PLAYER_STATE_UP)
	{
		_playerUp->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}
	if (playerState == PLAYER_STATE_DOWN)
	{
		_playerDown->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}

	// 플레이어 현재 상태 출력 (공격)
	if (playerState == PLAYER_STATE_LEFTATK)
	{
		_playerLeftAtk->frameRender(getMemDC(), playerRc.left - 20, playerRc.top - 15);
	}
	if (playerState == PLAYER_STATE_RIGHTATK)
	{
		_playerRightAtk->frameRender(getMemDC(), playerRc.left + 10, playerRc.top - 10);
	}
	if (playerState == PLAYER_STATE_UPATK)
	{
		_playerUpAtk->frameRender(getMemDC(), playerRc.left - 10, playerRc.top - 15);
	}
	if (playerState == PLAYER_STATE_DOWNATK)
	{
		_playerDownAtk->frameRender(getMemDC(), playerRc.left - 10, playerRc.top);
	}

	// 플레이어 현재 상태 출력 (피격)
	if (hpCount == 4)
	{
		_playerHP->frameRender(getMemDC(), 100, 50, 5, 0);
		playerGetAtk = true;
		playerState = PLAYER_STATE_GETATK;

		if (count > 5000)
		{
			playerState = PLAYER_STATE_IDLE;
			count = 0;
		}
	}
	if (hpCount == 3)
	{
		_playerHP->frameRender(getMemDC(), 100, 50, 4, 0);
		playerGetAtk = true;
		playerState = PLAYER_STATE_GETATK;

		if (count > 5000)
		{
			playerState = PLAYER_STATE_IDLE;
			count = 0;
		}
	}
	if (hpCount == 2)
	{
		_playerHP->frameRender(getMemDC(), 100, 50, 3, 0);
		playerGetAtk = true;
		playerState = PLAYER_STATE_GETATK;

		if (count > 5000)
		{
			playerState = PLAYER_STATE_IDLE;
			count = 0;
		}
	}
	if (hpCount == 1)
	{
		_playerHP->frameRender(getMemDC(), 100, 50, 2, 0);
		playerGetAtk = true;
		playerState = PLAYER_STATE_GETATK;

		if (count > 5000)
		{
			playerState = PLAYER_STATE_IDLE;
			count = 0;
		}
	}
	if (hpCount == 0)
	{
		_playerHP->frameRender(getMemDC(), 100, 50, 1, 0);
		playerState = PLAYER_STATE_DEAD;
	}
	
	// 피격 판정 RECT 렌더 (임시)
	Rectangle(getMemDC(), playerGetAtkLeftRc);
	Rectangle(getMemDC(), playerGetAtkRightRc);
	Rectangle(getMemDC(), playerGetAtkTopRc);
	Rectangle(getMemDC(), playerGetAtkBottomRc);

	// inventory 클래스 렌더
	_inventory->render();
}

// 애니메이션 (animation)
void player::animation()
{
	// 현재 상태에 따른 플레이어 애니메이션
	switch (playerState)
	{
	// 애니메이션 출력 (이동)
	case PLAYER_STATE_IDLE:
		_playerImage->render(getMemDC(), playerRc.left, playerRc.top);
		break;
	case PLAYER_STATE_LEFT:
		if (playerLeft)
		{
			count++;
			_playerLeft->setFrameY(0);

			if (count % 10 == 0)
			{
				index++;

				if (index >= 10)
				{
					index = 0;
				}
				_playerLeft->setFrameX(index);
			}
		}
		break;
	case PLAYER_STATE_RIGHT:
		if (playerRight)
		{
			count++;
			_playerRight->setFrameY(0);
			if (count % 10 == 0)
			{
				index++;

				if (index >= 10)
				{
					index = 0;
				}
				_playerRight->setFrameX(index);
			}
		}
		break;
	case PLAYER_STATE_UP:
		if (playerUp)
		{
			count++;
			_playerUp->setFrameY(0);
			if (count % 10 == 0)
			{
				index++;

				if (index >= 10)
				{
					index = 0;
				}
				_playerUp->setFrameX(index);
			}
		}
		break;
	case PLAYER_STATE_DOWN:
		if (playerDown)
		{
			count++;
			_playerDown->setFrameY(0);
			if (count % 10 == 0)
			{
				index++;

				if (index >= 10)
				{
					index = 0;
				}
				_playerDown->setFrameX(index);
			}
		}
		break;
	// 애니메이션 출력 (공격)
	case PLAYER_STATE_LEFTATK:
		if (playerLeftAtk)
		{
			count++;
			_playerLeftAtk->setFrameY(0);
			if (count % 3 == 0)
			{
				index++;

				if (index >= 29)
				{
					index = 0;
				}
				_playerLeftAtk->setFrameX(index);
			}
		}
		break;
	case PLAYER_STATE_RIGHTATK:
		if (playerRightAtk)
		{
			count++;
			_playerRightAtk->setFrameY(0);

			if (count % 3 == 0)
			{
				index++;

				if (index >= 29)
				{
					index = 0;
				}
				_playerRightAtk->setFrameX(index);
			}
		}
		break;
	case PLAYER_STATE_UPATK:
		if (playerUpAtk)
		{
			count++;
			_playerUpAtk->setFrameY(0);

			if (count % 3 == 0)
			{
				index++;

				if (index >= 11)
				{
					index = 0;
				}
				_playerUpAtk->setFrameX(index);
			}
		}
		break;
	case PLAYER_STATE_DOWNATK:
		if (playerDownAtk)
		{
			count++;
			_playerDownAtk->setFrameY(0);

			if (count % 5 == 0)
			{
				index++;

				if (index >= 11)
				{
					index = 0;
				}
				_playerDownAtk->setFrameX(index);
			}
		}
		break;
	// 애니메이션 출력 (피격)
	case PLAYER_STATE_GETATK:
		if (hpCount == 0)
		{
			count++;
			_playerGetAtk->setFrameY(0);

			if (count % 5 == 0)
			{
				index++;

				if (index >= 5)
				{
					index = 5;
				}
				_playerGetAtk->setFrameX(index);
			}
		}
		break;
	// 애니메이션 출력 (사망)
	case PLAYER_STATE_DEAD:
		if (hpCount == 0)
		{
			count++;
			_playerGetAtk->setFrameY(0);

			if (count % 5 == 0)
			{
				index++;

				if (index >= 5)
				{
					index = 5;
				}
				_playerGetAtk->setFrameX(index);
			}
		}
		break;
	}
}