#include "stdafx.h"
#include "player.h"
#include "octopus.h"
#include "mushroom.h"

// �ʱ�ȭ (init)
HRESULT player::init()
{
	// inventory Ŭ���� ���� �Ҵ� ����
	_inventory = new inventory;
	_inventory->init();

	// �÷��̾� �߽� ��ǥ �ʱ�ȭ
	playerCenter.x = WINSIZEX / 2;
	playerCenter.y = WINSIZEY / 2;

	// �÷��̾� �̹��� �ʱ�ȭ (�⺻ ���ĵ�, ü��, �̵�)
	_playerLeftStanding = IMAGEMANAGER->addImage("�÷��̾���", "Images/Player/��ũ�����.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerRightStanding = IMAGEMANAGER->addImage("�÷��̾�����ʿ����", "Images/Player/��ũ�����ʿ����.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerUpStanding = IMAGEMANAGER->addImage("�÷��̾�޸��", "Images/Player/��ũ�޸��.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerDownStanding = IMAGEMANAGER->addImage("�÷��̾�ո��", "Images/Player/��ũ�ո��.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerHP = IMAGEMANAGER->addImage("�÷��̾�ü��", "Images/Player/��Ʈ 400+80_X5Y1.bmp", 400, 80, true, RGB(255, 0, 255));
	_playerLeft = IMAGEMANAGER->addFrameImage("�÷��̾�����̵�", "Images/Player/��ũ�����ΰȱ�_230+23_10��.bmp", 640, 64, 10, 1);
	_playerRight = IMAGEMANAGER->addFrameImage("�÷��̾�������̵�", "Images/Player/��ũ�����ʿ����ΰȱ�_230+23_10��.bmp", 640, 64, 10, 1);
	_playerUp = IMAGEMANAGER->addFrameImage("�÷��̾������̵�", "Images/Player/��ũ���ΰȱ�_180+26_10��.bmp", 640, 64, 10, 1);
	_playerDown = IMAGEMANAGER->addFrameImage("�÷��̾�Ʒ����̵�", "Images/Player/��ũ�����ΰȱ�_180+24_10��.bmp", 640, 64, 10, 1);

	// �÷��̾� �̹��� �ʱ�ȭ (����) (����, ���ΰ� 80�� ������ 64�� �ʹ� �۱� ����)
	_playerLeftAtk = IMAGEMANAGER->addFrameImage("�÷��̾���ʰ���", "Images/Player/��ũ�����ΰ���_609+25_29��.bmp", 2320, 80, 29, 1);
	_playerRightAtk = IMAGEMANAGER->addFrameImage("�÷��̾�����ʰ���", "Images/Player/��ũ�����ʿ����ΰ���_609+25_29��.bmp", 2320, 80, 29, 1);
	_playerUpAtk = IMAGEMANAGER->addFrameImage("�÷��̾����ʰ���", "Images/Player/��ũ�ڷΰ���_638+28_11��.bmp", 880, 80, 11, 1);
	_playerDownAtk = IMAGEMANAGER->addFrameImage("�÷��̾���ʰ���", "Images/Player/��ũ�����ΰ���_209+24_11��.bmp", 880, 80, 11, 1);

	// �÷��̾� �̹��� �ʱ�ȭ (�ǰ�)
	_playerGetAtk = IMAGEMANAGER->addFrameImage("�÷��̾��ǰ�", "Images/Player/��ũ�ǰ�_125_24_5��.bmp", 320, 64, 5, 1);
	
	// �÷��̾� RECT �ʱ�ȭ (�Ϲ�)
	playerRc = RectMakeCenter(playerCenter.x, playerCenter.y, 64, 64);
	
	// �÷��̾� RECT �ʱ�ȭ (�ǰ� ���� RECT)
	playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 32, 10, 50);
	playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 32, 10, 50);
	playerGetAtkTopRc = RectMakeCenter(playerRc.left + 32, playerRc.top, 50, 10);
	playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 32, playerRc.bottom, 50, 10);
	
	// ��Ÿ ���� �ʱ�ȭ
	hpCount = 4;
	count = 0;
	index = 0;
	// ���ĵ� bool ����
	playerLeftStanding = false;
	playerRightStanding = false;
	playerUpStanding = false;
	playerDownStanding = true;
	// �̵� bool ����
	playerLeft = false;
	playerRight = false;
	playerUp = false;
	playerDown = false;
	// ���� bool ����
	playerLeftAtk = false;
	playerRightAtk = false;
	playerUpAtk = false;
	playerDownAtk = false;
	// �ǰ� bool ����
	playerGetAtkLeft = false;
	playerGetAtkRight = false;
	playerGetAtkTop = false;
	playerGetAtkBottom = false;
	playerGetAtk = false;
	playerGetAtkDelay = 0;
	playerGetAtkDelayBool = false;

	// �⺻ ���� ����
	playerState = PLAYER_STATE_DOWNSTANDING;

	// �ʱ�ȭ ����
	return S_OK;
}

// ���� (release)
void player::release()
{
	// inventory Ŭ���� ����
	_inventory->release();
	SAFE_DELETE(_inventory);
}

// ������Ʈ (update)
void player::update()
{
	// �ǰ� ��ǥ ����
	playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 32, 10, 50);
	playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 32, 10, 50);
	playerGetAtkTopRc = RectMakeCenter(playerRc.left + 32, playerRc.top, 50, 10);
	playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 32, playerRc.bottom, 50, 10);
	playerAttack = RectMakeCenter(playerRc.left + 40, playerRc.top - 20, 0, 0);		//���ݷ�Ʈ ġ��������

	// ĳ���� �̵� (�밢�� �̵��� �Ұ����ϰ� if, else if�� ó��)
	if (playerGetAtk == false && playerGetAtkDelayBool == false && hpCount > 0)
	{
		// ���� �̵�
		if (INPUT->getKey(VK_LEFT) && playerRc.left >= 0)
		{
			// ���� �̵��ϴ� ���·� ����
			playerLeftStanding = false;
			playerRightStanding = false;
			playerUpStanding = false;
			playerDownStanding = false;
			playerLeft = true;
			playerState = PLAYER_STATE_LEFT;

			// ��ǥ ����
			playerRc.left -= 3;
			playerRc.right -= 3;

			// ���� ����
			if (INPUT->getKey(VK_SPACE))
			{
				// ���� �����ϴ� ���·� ����
				playerLeftAtk = true;
				playerState = PLAYER_STATE_LEFTATK;

				// �⺻ ���ĵ� ���� RECT ũ��� ���� ���� RECT ũ�Ⱑ �ٸ��Ƿ� �ǰ� ���� RECT�� �ٽ� ����
				playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
				playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
				playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
				playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
				playerAttack = RectMakeCenter(playerRc.left - 20, playerRc.top + 30, 20, 60);
			}
			// ���� Ű�� ���� �� �޸��� ���·� �ٽ� ��ȯ
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerLeftAtk = false;
				playerState = PLAYER_STATE_LEFT;
			}
		}
		// ������ �̵�
		else if (INPUT->getKey(VK_RIGHT) && playerRc.right <= WINSIZEX)
		{
			// ������ �̵��ϴ� ���·� ����
			playerLeftStanding = false;
			playerRightStanding = false;
			playerUpStanding = false;
			playerDownStanding = false;
			playerRight = true;
			playerState = PLAYER_STATE_RIGHT;

			// ��ǥ ����
			playerRc.left += 3;
			playerRc.right += 3;

			// ������ ����
			if (INPUT->getKey(VK_SPACE))
			{
				// ������ �����ϴ� ���·� ����
				playerRightAtk = true;
				playerState = PLAYER_STATE_RIGHTATK;

				// �⺻ ���ĵ� ���� RECT ũ��� ���� ���� RECT ũ�Ⱑ �ٸ��Ƿ� �ǰ� ���� RECT�� �ٽ� ����
				playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
				playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
				playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
				playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
				playerAttack = RectMakeCenter(playerRc.right + 20, playerRc.top + 30, 20, 60);
			}
			// ���� Ű�� ���� �� �޸��� ���·� �ٽ� ��ȯ
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerRightAtk = false;
				playerState = PLAYER_STATE_RIGHT;
			}
		}
		// ���� �̵�
		else if (INPUT->getKey(VK_UP) && playerRc.top >= 0)
		{
			// ���� �̵��ϴ� ���·� ����
			playerLeftStanding = false;
			playerRightStanding = false;
			playerUpStanding = false;
			playerDownStanding = false;
			playerUp = true;
			playerState = PLAYER_STATE_UP;

			// ��ǥ ����
			playerRc.top -= 3;
			playerRc.bottom -= 3;

			// ���� ����
			if (INPUT->getKey(VK_SPACE))
			{
				// ���� �����ϴ� ���·� ����
				playerUpAtk = true;
				playerState = PLAYER_STATE_UPATK;

				// �⺻ ���ĵ� ���� RECT ũ��� ���� ���� RECT ũ�Ⱑ �ٸ��Ƿ� �ǰ� ���� RECT�� �ٽ� ����
				playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
				playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
				playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
				playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
				playerAttack = RectMakeCenter(playerRc.left + 30, playerRc.top - 20, 60, 20);
			}
			// ���� Ű�� ���� �� �޸��� ���·� �ٽ� ��ȯ
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerUpAtk = false;
				playerState = PLAYER_STATE_UP;
			}
		}
		// �Ʒ��� �̵�
		else if (INPUT->getKey(VK_DOWN) && playerRc.bottom <= WINSIZEY)
		{
			// �Ʒ��� �̵��ϴ� ���·� ����
			playerLeftStanding = false;
			playerRightStanding = false;
			playerUpStanding = false;
			playerDownStanding = false;
			playerDown = true;
			playerState = PLAYER_STATE_DOWN;

			// ��ǥ ����
			playerRc.top += 3;
			playerRc.bottom += 3;

			// �Ʒ��� �̵�
			if (INPUT->getKey(VK_SPACE))
			{
				// �Ʒ��� �����ϴ� ���·� ����
				playerDownAtk = true;
				playerState = PLAYER_STATE_DOWNATK;

				// �⺻ ���ĵ� ���� RECT ũ��� ���� ���� RECT ũ�Ⱑ �ٸ��Ƿ� �ǰ� ���� RECT�� �ٽ� ����
				playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
				playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
				playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
				playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
				playerAttack = RectMakeCenter(playerRc.left + 30, playerRc.bottom + 20, 60, 20);
			}
			// ���� Ű�� ���� �� �޸��� ���·� �ٽ� ��ȯ
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerDownAtk = false;
				playerState = PLAYER_STATE_DOWN;
			}
		}

		// ���� ����
		if (INPUT->getKey(VK_SPACE) && playerLeftStanding == true)
		{
			// ���� �����ϴ� ���·� ����
			playerLeftAtk = true;
			playerState = PLAYER_STATE_LEFTATK;

			// �⺻ ���ĵ� ���� RECT ũ��� ���� ���� RECT ũ�Ⱑ �ٸ��Ƿ� �ǰ� ���� RECT�� �ٽ� ����
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
			playerAttack = RectMakeCenter(playerRc.left - 20, playerRc.top + 30, 20, 60);
		}
		// ������ ����
		else if (INPUT->getKey(VK_SPACE) && playerRightStanding == true)
		{
			// ������ �����ϴ� ���·� ����
			playerRightAtk = true;
			playerState = PLAYER_STATE_RIGHTATK;

			// �⺻ ���ĵ� ���� RECT ũ��� ���� ���� RECT ũ�Ⱑ �ٸ��Ƿ� �ǰ� ���� RECT�� �ٽ� ����
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
			playerAttack = RectMakeCenter(playerRc.right + 20, playerRc.top + 30, 20, 60);
		}
		// ���� ����
		else if (INPUT->getKey(VK_SPACE) && playerUpStanding == true)
		{
			// ���� �����ϴ� ���·� ����
			playerUpAtk = true;
			playerState = PLAYER_STATE_UPATK;

			// �⺻ ���ĵ� ���� RECT ũ��� ���� ���� RECT ũ�Ⱑ �ٸ��Ƿ� �ǰ� ���� RECT�� �ٽ� ����
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
			playerAttack = RectMakeCenter(playerRc.left + 30, playerRc.top - 20, 60, 20);
		}
		// �Ʒ��� ���� 
		else if (INPUT->getKey(VK_SPACE) && playerDownStanding == true)
		{
			// �Ʒ��� �����ϴ� ���·� ����
			playerDownAtk = true;
			playerState = PLAYER_STATE_DOWNATK;

			// �⺻ ���ĵ� ���� RECT ũ��� ���� ���� RECT ũ�Ⱑ �ٸ��Ƿ� �ǰ� ���� RECT�� �ٽ� ����
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 30, 10, 60);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 30, 10, 60);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 30, playerRc.top, 60, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 30, playerRc.bottom, 60, 10);
			playerAttack = RectMakeCenter(playerRc.left + 30, playerRc.bottom + 20, 60, 20);
		}

		// ���� Ű�� ���� �� ���ִ� ���·� �ٽ� ��ȯ
		if (playerLeftAtk == true)
		{
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerLeftAtk = false;
				playerLeftStanding = true;
				playerState = PLAYER_STATE_LEFTSTANDING;
			}
		}
		// ���� Ű�� ���� �� ���ִ� ���·� �ٽ� ��ȯ
		else if (playerRightAtk == true)
		{
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerRightAtk = false;
				playerRightStanding = true;
				playerState = PLAYER_STATE_RIGHTSTANDING;
			}
		}
		// ���� Ű�� ���� �� ���ִ� ���·� �ٽ� ��ȯ
		else if (playerUpAtk == true)
		{
			if (INPUT->getKeyUp(VK_SPACE))
			{
				playerUpAtk = false;
				playerUpStanding = true;
				playerState = PLAYER_STATE_UPSTANDING;
			}
		}
		// ���� Ű�� ���� �� ���ִ� ���·� �ٽ� ��ȯ
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

	// �ǰ� �� ü�� ����
	// ������ ���Ѱ��� �ǰ�
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
	// �������� �ǰ�
	if (!_mushroomAdress->getMushroom().empty())
	{
		for (int i = 0; i < _mushroomAdress->getMushroom().size(); i++)
		{
			// ���� �浹
			if (IntersectRect(&empty, &playerGetAtkLeftRc, &_mushroomAdress->getMushroom()[i]._rc))
			{
				playerRc.left += 30;
				playerRc.right += 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// ������ �浹
			else if (IntersectRect(&empty, &playerGetAtkRightRc, &_mushroomAdress->getMushroom()[i]._rc))
			{
				playerRc.left -= 30;
				playerRc.right -= 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// ���� �浹
			else if (IntersectRect(&empty, &playerGetAtkTopRc, &_mushroomAdress->getMushroom()[i]._rc))
			{
				playerRc.top += 30;
				playerRc.bottom += 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// �Ʒ��� �浹
			else if (IntersectRect(&empty, &playerGetAtkBottomRc, &_mushroomAdress->getMushroom()[i]._rc))
			{
				playerRc.top -= 30;
				playerRc.bottom -= 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
		}
	}
	// ������� �ǰ�
	if (!_octopusAdress->getOctopus().empty())
	{
		for (int i = 0; i < _octopusAdress->getOctopus().size(); i++)
		{
			// ���� �浹
			if (IntersectRect(&empty, &playerGetAtkLeftRc, &_octopusAdress->getOctopus()[i]._rc))
			{
				playerRc.left += 30;
				playerRc.right += 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// ������ �浹
			else if (IntersectRect(&empty, &playerGetAtkRightRc, &_octopusAdress->getOctopus()[i]._rc))
			{
				playerRc.left -= 30;
				playerRc.right -= 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// ���� �浹
			else if (IntersectRect(&empty, &playerGetAtkTopRc, &_octopusAdress->getOctopus()[i]._rc))
			{
				playerRc.top += 30;
				playerRc.bottom += 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
			// �Ʒ��� �浹
			else if (IntersectRect(&empty, &playerGetAtkBottomRc, &_octopusAdress->getOctopus()[i]._rc))
			{
				playerRc.top -= 30;
				playerRc.bottom -= 30;
				playerGetAtk = true;
				playerState = PLAYER_STATE_GETATK;
			}
		}
	}
	// �ǰ� ���� ó��
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

	// �÷��̾� ���
	if (hpCount <= 0)
	{
		playerState = PLAYER_STATE_DEAD;
	}

	// inventory Ŭ���� ������Ʈ
	_inventory->update();

	// �ִϸ��̼� ���
	this->animation();
}

// ���� (render)
void player::render()
{
	// �ӽ� RECT ����
	Rectangle(getMemDC(), playerRc);

	// �÷��̾� ���� ���� ��� (�̵�, ���ٵ�)
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
	// �÷��̾� ���� ���� ��� (����)
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
	// �÷��̾� ���� ���� ��� (�ǰ�)
	else if (playerState == PLAYER_STATE_GETATK)
	{
		_playerGetAtk->frameRender(getMemDC(), playerRc.left, playerRc.top);
	}
	// �÷��̾� ü�� ���� ���
	_playerHP->render(getMemDC(), 100, 50, 80 * hpCount, 0, 80, 80);

	// �ǰ� ���� RECT ���� (�ӽ�)
	Rectangle(getMemDC(), playerGetAtkLeftRc);
	Rectangle(getMemDC(), playerGetAtkRightRc);
	Rectangle(getMemDC(), playerGetAtkTopRc);
	Rectangle(getMemDC(), playerGetAtkBottomRc);
	Rectangle(getMemDC(), playerAttack);

	// inventory Ŭ���� ����
	_inventory->render();
}

// �ִϸ��̼� (animation)
void player::animation()
{
	// ���� ���¿� ���� �÷��̾� �ִϸ��̼�
	switch (playerState)
	{
	// �ִϸ��̼� ��� (�̵�)
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
	// �ִϸ��̼� ��� (����)
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
	// �ִϸ��̼� ��� (�ǰ�)
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
	// �ִϸ��̼� ��� (���)
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