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
	_playerImage = IMAGEMANAGER->addImage("�÷��̾�ո��", "Images/Player/��ũ�ո��.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerHP = IMAGEMANAGER->addFrameImage("�÷��̾�ü��", "Images/Player/��Ʈ 400+80_X5Y1.bmp", 200, 50, 5, 1);
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
	_playerGetAtk = IMAGEMANAGER->addFrameImage("�÷��̾��ǰ�", "Images/Player/��ũ�ǰ�_125+24_5��.bmp", 320, 64, 5, 1);
	
	// �÷��̾� RECT �ʱ�ȭ (�Ϲ�)
	playerRc = RectMakeCenter(playerCenter.x, playerCenter.y, 64, 64);
	
	// �÷��̾� RECT �ʱ�ȭ (�ǰ� ���� RECT)
	playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 32, 10, 10);
	playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 32, 10, 10);
	playerGetAtkTopRc = RectMakeCenter(playerRc.left + 32, playerRc.top, 10, 10);
	playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 32, playerRc.bottom, 10, 10);
	
	// ��Ÿ ���� �ʱ�ȭ
	hpCount = 4;
	count = 0;
	index = 0;
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

	// �⺻ ���� ����
	playerState = PLAYER_STATE_IDLE;

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
	// ĳ���� �̵� (�밢�� �̵��� �Ұ����ϰ� if, else if�� ó��)
	// ���� �̵�
	if (INPUT->getKey(VK_LEFT) && playerRc.left >= 0)
	{
		// ���� �̵��ϴ� ���·� ����
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
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 40, 10, 10);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 40, 10, 10);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 40, playerRc.top, 10, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 40, playerRc.bottom, 10, 10);

		}
	}
	// ������ �̵�
	else if (INPUT->getKey(VK_RIGHT) && playerRc.right <= WINSIZEX)
	{
		// ������ �̵��ϴ� ���·� ����
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
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 40, 10, 10);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 40, 10, 10);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 40, playerRc.top, 10, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 40, playerRc.bottom, 10, 10);

		}
	}
	// ���� �̵�
	else if (INPUT->getKey(VK_UP) && playerRc.top >= 0)
	{
		// ���� �̵��ϴ� ���·� ����
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
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 40, 10, 10);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 40, 10, 10);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 40, playerRc.top, 10, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 40, playerRc.bottom, 10, 10);
		}
	}
	// �Ʒ��� �̵�
	else if (INPUT->getKey(VK_DOWN) && playerRc.bottom <= WINSIZEY)
	{
		// �Ʒ��� �̵��ϴ� ���·� ����
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
			playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 40, 10, 10);
			playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 40, 10, 10);
			playerGetAtkTopRc = RectMakeCenter(playerRc.left + 40, playerRc.top, 10, 10);
			playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 40, playerRc.bottom, 10, 10);
		}
	}

	// ���� ������Ʈ ����
	if (INPUT->getKeyUp(VK_LEFT))				// ����
	{
		playerLeft = false;
		_playerLeft->setFrameX(0);
	}
	else if (INPUT->getKeyUp(VK_RIGHT))			// ������
	{
		playerRight = false;
		_playerRight->setFrameX(0);
	}
	else if (INPUT->getKeyUp(VK_UP))			// ����
	{
		playerUp = false;
		_playerUp->setFrameX(0);
	}
	else if (INPUT->getKeyUp(VK_DOWN))			// �Ʒ���
	{
		playerDown = false;
		_playerDown->setFrameX(0);
	}

	// �ǰ� ���� RECT ��ǥ ����
	playerGetAtkLeftRc = RectMakeCenter(playerRc.left, playerRc.top + 32, 10, 10);
	playerGetAtkRightRc = RectMakeCenter(playerRc.right, playerRc.top + 32, 10, 10);
	playerGetAtkTopRc = RectMakeCenter(playerRc.left + 32, playerRc.top, 10, 10);
	playerGetAtkBottomRc = RectMakeCenter(playerRc.left + 32, playerRc.bottom, 10, 10);

	// if(IntersectRect(&empty, &_getAtkleftRc, &/*���� ��Ʈ �����ּ���*/)
	// {
	//	_hpCount--;
	// }
	// else if (IntersectRect(&empty, &_getAtkrightRc, &/*���� ��Ʈ �����ּ���*/)
	// {
	// 	_hpCount--;
	// }
	// else if (IntersectRect(&empty, &_getAtktopRc, &/*���� ��Ʈ �����ּ���*/)
	// {
	//	_hpCount--;
	// }
	// else if (IntersectRect(&empty, &_getAtkbottomRc, &/*���� ��Ʈ �����ּ���*/)
	// {
	// 	_hpCount--;
	// }

	// �ǰ� �� ü�� ����
	// ���� �浹��
	if (!_octopusAdress->getOctopus().empty())
	{
		for (int i = 0; i < _octopusAdress->getOctopus().size(); i++)
		{
			// ���� �浹
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
			// ������ �浹
		}
	}

	// ���� �浹��
	if (!_mushroomAdress->getMushroom().empty())
	{
		for (int i = 0; i < _mushroomAdress->getMushroom().size(); i++)
		{
			// ���� �浹
			if (IntersectRect(&empty, &playerGetAtkLeftRc, &_mushroomAdress->getMushroom()[i]._rc))
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
			// ������ �浹
		}
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
	//Rectangle(getMemDC(), playerRc);

	// �÷��̾� ���� ���� ��� (�̵�)
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

	// �÷��̾� ���� ���� ��� (����)
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

	// �÷��̾� ���� ���� ��� (�ǰ�)
	if (playerState == PLAYER_STATE_GETATK)
	{
		if (hpCount == 4)
		{
			_playerHP->frameRender(getMemDC(), 100, 50, 5, 0);
			playerGetAtk = true;
			count++;
			//playerState = PLAYER_STATE_GETATK;

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
			//playerState = PLAYER_STATE_GETATK;

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
			//playerState = PLAYER_STATE_GETATK;

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
			//playerState = PLAYER_STATE_GETATK;

			if (count > 5000)
			{
				playerState = PLAYER_STATE_IDLE;
				count = 0;
			}
		}
	}
	if (hpCount == 0)
	{
		_playerHP->frameRender(getMemDC(), 100, 50, 1, 0);
		playerState = PLAYER_STATE_DEAD;
	}
	
	// �ǰ� ���� RECT ���� (�ӽ�)
	Rectangle(getMemDC(), playerGetAtkLeftRc);
	Rectangle(getMemDC(), playerGetAtkRightRc);
	Rectangle(getMemDC(), playerGetAtkTopRc);
	Rectangle(getMemDC(), playerGetAtkBottomRc);

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
	// �ִϸ��̼� ��� (����)
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
	// �ִϸ��̼� ��� (�ǰ�)
	case PLAYER_STATE_GETATK:
		if (hpCount <= 4 || hpCount > 0)
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
	// �ִϸ��̼� ��� (���)
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