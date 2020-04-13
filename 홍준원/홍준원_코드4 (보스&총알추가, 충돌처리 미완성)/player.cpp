#include "stdafx.h"
#include "player.h"
#include "boss.h"
#include "octopus.h"
#include "mushroom.h"

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
	_playerLeftStanding = IMAGEMANAGER->addImage("플레이어옆모습", "Images/Player/링크옆모습.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerRightStanding = IMAGEMANAGER->addImage("플레이어오른쪽옆모습", "Images/Player/링크오른쪽옆모습.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerUpStanding = IMAGEMANAGER->addImage("플레이어뒷모습", "Images/Player/링크뒷모습.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerDownStanding = IMAGEMANAGER->addImage("플레이어앞모습", "Images/Player/링크앞모습.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerHP = IMAGEMANAGER->addImage("플레이어체력", "Images/Player/하트 400+80_X5Y1.bmp", 400, 80, true, RGB(255, 0, 255));
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
	_playerGetAtk = IMAGEMANAGER->addFrameImage("플레이어피격", "Images/Player/링크피격_125_24_5장.bmp", 320, 64, 5, 1);
	
	// 플레이어 RECT 초기화 (일반)
	playerRc = RectMakeCenter(playerCenter.x, playerCenter.y, 64, 64);
	
	// 플레이어 RECT 초기화 (피격 판정 RECT)
	playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 32, 10, 50);
	playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 32, 10, 50);
	playerGetAtkTopRc = RectMakeCenter(playerRc.left + 32, playerRc.top, 50, 10);
	playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 32, playerRc.bottom, 50, 10);
	
	// 기타 변수 초기화
	hpCount = 4;
	count = 0;
	index = 0;
	// 스탠딩 bool 변수
	playerLeftStanding = false;
	playerRightStanding = false;
	playerUpStanding = false;
	playerDownStanding = true;
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
	playerGetAtkDelay = 0;
	playerGetAtkDelayBool = false;

	// 기본 상태 설정
	playerState = PLAYER_STATE_DOWNSTANDING;

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
	// 피격 좌표 고정
	playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 32, 10, 50);
	playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 32, 10, 50);
	playerGetAtkTopRc = RectMakeCenter(playerRc.left + 32, playerRc.top, 50, 10);
	playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 32, playerRc.bottom, 50, 10);
	playerAttack = RectMakeCenter(playerRc.left + 40, playerRc.top - 20, 0, 0);		//공격렉트 치워버리기

	// 캐릭터 이동 (대각선 이동이 불가능하게 if, else if로 처리)
	if (playerGetAtk == false && playerGetAtkDelayBool == false && hpCount > 0)
	{
		// 왼쪽 이동
		if (INPUT->getKey(VK_LEFT) && playerRc.left >= 0)
		{
			// 왼쪽 이동하는 상태로 변경
			playerLeftStanding = false;
			playerRightStanding = false;
			playerUpStanding = false;
			playerDownStanding = false;
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
				playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
				playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
				playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
				playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
				playerAttack = RectMakeCenter(playerRc.left - 20, playerRc.top + 30, 20, 60);
			}
			// 공격 키를 뗐을 때 달리는 상태로 다시 전환
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerLeftAtk = false;
				playerState = PLAYER_STATE_LEFT;
			}
		}
		// 오른쪽 이동
		else if (INPUT->getKey(VK_RIGHT) && playerRc.right <= WINSIZEX)
		{
			// 오른쪽 이동하는 상태로 변경
			playerLeftStanding = false;
			playerRightStanding = false;
			playerUpStanding = false;
			playerDownStanding = false;
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
				playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
				playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
				playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
				playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
				playerAttack = RectMakeCenter(playerRc.right + 20, playerRc.top + 30, 20, 60);
			}
			// 공격 키를 뗐을 때 달리는 상태로 다시 전환
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerRightAtk = false;
				playerState = PLAYER_STATE_RIGHT;
			}
		}
		// 위쪽 이동
		else if (INPUT->getKey(VK_UP) && playerRc.top >= 0)
		{
			// 위쪽 이동하는 상태로 변경
			playerLeftStanding = false;
			playerRightStanding = false;
			playerUpStanding = false;
			playerDownStanding = false;
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
				playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
				playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
				playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
				playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
				playerAttack = RectMakeCenter(playerRc.left + 30, playerRc.top - 20, 60, 20);
			}
			// 공격 키를 뗐을 때 달리는 상태로 다시 전환
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerUpAtk = false;
				playerState = PLAYER_STATE_UP;
			}
		}
		// 아래쪽 이동
		else if (INPUT->getKey(VK_DOWN) && playerRc.bottom <= WINSIZEY)
		{
			// 아래쪽 이동하는 상태로 변경
			playerLeftStanding = false;
			playerRightStanding = false;
			playerUpStanding = false;
			playerDownStanding = false;
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
				playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
				playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
				playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
				playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
				playerAttack = RectMakeCenter(playerRc.left + 30, playerRc.bottom + 20, 60, 20);
			}
			// 공격 키를 뗐을 때 달리는 상태로 다시 전환
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerDownAtk = false;
				playerState = PLAYER_STATE_DOWN;
			}
		}

		// 왼쪽 공격
		if (INPUT->getKey(VK_SPACE) && playerLeftStanding == true)
		{
			// 왼쪽 공격하는 상태로 변경
			playerLeftAtk = true;
			playerState = PLAYER_STATE_LEFTATK;

			// 기본 스탠딩 상태 RECT 크기와 공격 상태 RECT 크기가 다르므로 피격 판정 RECT를 다시 설정
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
			playerAttack = RectMakeCenter(playerRc.left - 20, playerRc.top + 30, 20, 60);
		}
		// 오른쪽 공격
		else if (INPUT->getKey(VK_SPACE) && playerRightStanding == true)
		{
			// 오른쪽 공격하는 상태로 변경
			playerRightAtk = true;
			playerState = PLAYER_STATE_RIGHTATK;

			// 기본 스탠딩 상태 RECT 크기와 공격 상태 RECT 크기가 다르므로 피격 판정 RECT를 다시 설정
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
			playerAttack = RectMakeCenter(playerRc.right + 20, playerRc.top + 30, 20, 60);
		}
		// 위쪽 공격
		else if (INPUT->getKey(VK_SPACE) && playerUpStanding == true)
		{
			// 위쪽 공격하는 상태로 변경
			playerUpAtk = true;
			playerState = PLAYER_STATE_UPATK;

			// 기본 스탠딩 상태 RECT 크기와 공격 상태 RECT 크기가 다르므로 피격 판정 RECT를 다시 설정
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
			playerAttack = RectMakeCenter(playerRc.left + 30, playerRc.top - 20, 60, 20);
		}
		// 아래쪽 공격 
		else if (INPUT->getKey(VK_SPACE) && playerDownStanding == true)
		{
			// 아래쪽 공격하는 상태로 변경
			playerDownAtk = true;
			playerState = PLAYER_STATE_DOWNATK;

			// 기본 스탠딩 상태 RECT 크기와 공격 상태 RECT 크기가 다르므로 피격 판정 RECT를 다시 설정
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
			playerAttack = RectMakeCenter(playerRc.left + 30, playerRc.bottom + 20, 60, 20);
		}

		// 공격 키를 뗐을 때 서있는 상태로 다시 전환
		if (playerLeftAtk == true)
		{
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerLeftAtk = false;
				playerLeftStanding = true;
				playerState = PLAYER_STATE_LEFTSTANDING;
			}
		}
		// 공격 키를 뗐을 때 서있는 상태로 다시 전환
		else if (playerRightAtk == true)
		{
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerRightAtk = false;
				playerRightStanding = true;
				playerState = PLAYER_STATE_RIGHTSTANDING;
			}
		}
		// 공격 키를 뗐을 때 서있는 상태로 다시 전환
		else if (playerUpAtk == true)
		{
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerUpAtk = false;
				playerUpStanding = true;
				playerState = PLAYER_STATE_UPSTANDING;
			}
		}
		// 공격 키를 뗐을 때 서있는 상태로 다시 전환
		else if (playerDownAtk == true)
		{
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerDownAtk = false;
				playerDownStanding = true;
				playerState = PLAYER_STATE_DOWNSTANDING;
			}
		}
	}

	// 피격 시 체력 감소
	// 문어의 씨앗과의 피격
	if (!_octopusAdress->getMissile()->getBullet().empty())
	{
		for (int i = 0; i < _octopusAdress->getMissile()->getBullet().size(); i++)
		{
			if (IntersectRect(&empty, &playerRc, &_octopusAdress->getMissile()->getBullet()[i].rc))
			{
				_octopusAdress->getMissile()->setBullet(i, false);
				_octopusAdress->getMissile()->eraseBullet(i);
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
		}
	}

	// 보스 파이어볼 피격
	if (!_bossAdress->getMissile()->getBullet().empty())
	{
		for (int i = 0; i < _bossAdress->getMissile()->getBullet().size(); i++)
		{
			if (IntersectRect(&empty, &playerRc, &_bossAdress->getMissile()->getBullet()[i].rc))
			{
				_bossAdress->getMissile()->setBullet(i, false);
				_bossAdress->getMissile()->eraseBullet(i);
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
		}
	}

	// 보스 아이쉴드 피격
	if (!_bossAdress->getMissileE()->getBullet().empty())
	{
		for (int i = 0; i < _bossAdress->getMissileE()->getBullet().size(); i++)
		{
			if (IntersectRect(&empty, &playerRc, &_bossAdress->getMissileE()->getBullet()[i].rc))
			{
				_bossAdress->getMissileE()->setBullet(i, false);
				_bossAdress->getMissileE()->eraseBullet(i);
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
		}
	}

	// 보스 아이쉴드 피격
	if (!_bossAdress->getMissileE2()->getBullet().empty())
	{
		for (int i = 0; i < _bossAdress->getMissileE2()->getBullet().size(); i++)
		{
			if (IntersectRect(&empty, &playerRc, &_bossAdress->getMissileE2()->getBullet()[i].rc))
			{
				_bossAdress->getMissileE2()->setBullet(i, false);
				_bossAdress->getMissileE2()->eraseBullet(i);
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
		}
	}

	// 버섯과의 피격
	if (!_mushroomAdress->getMushroom().empty())
	{
		for (int i = 0; i < _mushroomAdress->getMushroom().size(); i++)
		{
			// 왼쪽 충돌
			if (IntersectRect(&empty, &playerGetAtkLeftRc, &_mushroomAdress->getMushroom()[i]._rc))
			{
				playerRc.left += 30;
				playerRc.right += 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// 오른쪽 충돌
			else if (IntersectRect(&empty, &playerGetAtkRightRc, &_mushroomAdress->getMushroom()[i]._rc))
			{
				playerRc.left -= 30;
				playerRc.right -= 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// 위쪽 충돌
			else if (IntersectRect(&empty, &playerGetAtkTopRc, &_mushroomAdress->getMushroom()[i]._rc))
			{
				playerRc.top += 30;
				playerRc.bottom += 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// 아래쪽 충돌
			else if (IntersectRect(&empty, &playerGetAtkBottomRc, &_mushroomAdress->getMushroom()[i]._rc))
			{
				playerRc.top -= 30;
				playerRc.bottom -= 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
		}
	}
	// 문어와의 피격
	if (!_octopusAdress->getOctopus().empty())
	{
		for (int i = 0; i < _octopusAdress->getOctopus().size(); i++)
		{
			// 왼쪽 충돌
			if (IntersectRect(&empty, &playerGetAtkLeftRc, &_octopusAdress->getOctopus()[i]._rc))
			{
				playerRc.left += 30;
				playerRc.right += 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// 오른쪽 충돌
			else if (IntersectRect(&empty, &playerGetAtkRightRc, &_octopusAdress->getOctopus()[i]._rc))
			{
				playerRc.left -= 30;
				playerRc.right -= 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// 위쪽 충돌
			else if (IntersectRect(&empty, &playerGetAtkTopRc, &_octopusAdress->getOctopus()[i]._rc))
			{
				playerRc.top += 30;
				playerRc.bottom += 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// 아래쪽 충돌
			else if (IntersectRect(&empty, &playerGetAtkBottomRc, &_octopusAdress->getOctopus()[i]._rc))
			{
				playerRc.top -= 30;
				playerRc.bottom -= 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
		}
	}
	// 피격 판정 처리
	if (playerGetAtk == true)
	{
		if (hpCount > 0)
		{
			hpCount--;
		}
		playerGetAtk = false;
		playerGetAtkDelayBool = true;
	}
	if (playerGetAtkDelayBool == true)
	{
		playerGetAtkDelay++;
		
		if (playerGetAtkDelay >= 50)
		{
			playerGetAtkDelay = 0;
			playerGetAtkDelayBool = false;
			playerState = PLAYER_STATE_DOWNSTANDING;
		}
	}

	// 플레이어 사망
	if (hpCount <= 0)
	{
		playerState = PLAYER_STATE_DEAD;
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

	// 플레이어 현재 상태 출력 (이동, 스텐딩)
	if (playerState == PLAYER_STATE_LEFTSTANDING)
	{
		_playerLeftStanding->render(getMemDC(), playerRc.left, playerRc.top);
	}
	else if (playerState == PLAYER_STATE_RIGHTSTANDING)
	{
		_playerRightStanding->render(getMemDC(), playerRc.left, playerRc.top);
	}
	else if (playerState == PLAYER_STATE_UPSTANDING)
	{
		_playerUpStanding->render(getMemDC(), playerRc.left, playerRc.top);
	}
	else if (playerState == PLAYER_STATE_DOWNSTANDING)
	{
		_playerDownStanding->render(getMemDC(), playerRc.left, playerRc.top);
	}
	else if (playerState == PLAYER_STATE_LEFT)
	{
		_playerLeft->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}
	else if (playerState == PLAYER_STATE_RIGHT)
	{
		_playerRight->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}
	else if (playerState == PLAYER_STATE_UP)
	{
		_playerUp->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}
	else if (playerState == PLAYER_STATE_DOWN)
	{
		_playerDown->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}
	// 플레이어 현재 상태 출력 (공격)
	else if (playerState == PLAYER_STATE_LEFTATK)
	{
		_playerLeftAtk->frameRender(getMemDC(), playerRc.left - 20, playerRc.top - 15);
	}
	else if (playerState == PLAYER_STATE_RIGHTATK)
	{
		_playerRightAtk->frameRender(getMemDC(), playerRc.left + 10, playerRc.top - 10);
	}
	else if (playerState == PLAYER_STATE_UPATK)
	{
		_playerUpAtk->frameRender(getMemDC(), playerRc.left - 10, playerRc.top - 15);
	}
	else if (playerState == PLAYER_STATE_DOWNATK)
	{
		_playerDownAtk->frameRender(getMemDC(), playerRc.left - 10, playerRc.top);
	}
	// 플레이어 현재 상태 출력 (피격)
	else if (playerState == PLAYER_STATE_GETATK)
	{
		_playerGetAtk->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}
	// 플레이어 체력 상태 출력
	_playerHP->render(getMemDC(), 100, 50, 80 * hpCount, 0, 80, 80);

	// 피격 판정 RECT 렌더 (임시)
	Rectangle(getMemDC(), playerGetAtkLeftRc);
	Rectangle(getMemDC(), playerGetAtkRightRc);
	Rectangle(getMemDC(), playerGetAtkTopRc);
	Rectangle(getMemDC(), playerGetAtkBottomRc);
	Rectangle(getMemDC(), playerAttack);

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
	case PLAYER_STATE_LEFTSTANDING:
		_playerLeftStanding->render(getMemDC(), playerRc.left, playerRc.top);
		break;
	case PLAYER_STATE_RIGHTSTANDING:
		_playerRightStanding->render(getMemDC(), playerRc.left, playerRc.top);
		break;
	case PLAYER_STATE_UPSTANDING:
		_playerUpStanding->render(getMemDC(), playerRc.left, playerRc.top);
		break;
	case PLAYER_STATE_DOWNSTANDING:
		_playerDownStanding->render(getMemDC(), playerRc.left, playerRc.top);
		break;
	case PLAYER_STATE_LEFT:
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
		break;
	case PLAYER_STATE_RIGHT:
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
		break;
	case PLAYER_STATE_UP:
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
		break;
	case PLAYER_STATE_DOWN:
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
		break;
	// 애니메이션 출력 (공격)
	case PLAYER_STATE_LEFTATK:
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
		break;
	case PLAYER_STATE_RIGHTATK:
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
		break;
	case PLAYER_STATE_UPATK:
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
		break;
	case PLAYER_STATE_DOWNATK:
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
		break;
	// 애니메이션 출력 (피격)
	case PLAYER_STATE_GETATK:
		count++;
		_playerGetAtk->setFrameY(0);

		if (count % 5 == 0)
		{
			index++;

			if (index >= 5)
			{
				index = 0;
			}
			_playerGetAtk->setFrameX(index);
		}
		break;
	// 애니메이션 출력 (사망)
	case PLAYER_STATE_DEAD:
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
		break;
	}
}