#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{

	_inventory = new Inventory;//�κ��丮 Ŭ���� ������
	_inventory->init();

	_playercenter.x = WINSIZEX / 2;//�÷��̾� �߽� ��ǥ ����
	_playercenter.y = WINSIZEY / 2;

	//������� �÷��̾��� ���̵�, �̵� ����
	_playerImage = IMAGEMANAGER->addImage("�÷��̾�ո��", "�÷��̾�/��ũ�ո��.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerLeft = IMAGEMANAGER->addFrameImage("�÷��̾�����̵�", "�÷��̾�/��ũ�����ΰȱ�_230+23_10��.bmp", 640, 64, 10, 1);
	_playerRight = IMAGEMANAGER->addFrameImage("�÷��̾�������̵�", "�÷��̾�/��ũ�����ʿ����ΰȱ�_230+23_10��.bmp", 640, 64, 10, 1);
	_playerUp = IMAGEMANAGER->addFrameImage("�÷��̾������̵�", "�÷��̾�/��ũ���ΰȱ�_180+26_10��.bmp", 640, 64, 10, 1);
	_playerDown = IMAGEMANAGER->addFrameImage("�÷��̾�Ʒ����̵�", "�÷��̾�/��ũ�����ΰȱ�_180+24_10��.bmp", 640, 64, 10, 1);


	//������� �÷��̾��� ���� ���� --> ����, ���ΰ� 80�� ������ 64�� �ʹ� �۱� �����Դϴ�
	_playerLeftatk = IMAGEMANAGER->addFrameImage("�÷��̾���ʰ���", "�÷��̾�/��ũ�����ΰ���_609+25_29��.bmp", 2320, 80, 29, 1);
	_playerRightatk = IMAGEMANAGER->addFrameImage("�÷��̾�����ʰ���", "�÷��̾�/��ũ�����ʿ����ΰ���_609+25_29��.bmp", 2320, 80, 29, 1);
	_playerUpatk = IMAGEMANAGER->addFrameImage("�÷��̾����ʰ���", "�÷��̾�/��ũ�ڷΰ���_638+28_11��.bmp", 880, 80, 11, 1);
	_playerFrontatk = IMAGEMANAGER->addFrameImage("�÷��̾���ʰ���", "�÷��̾�/��ũ�����ΰ���_209+24_11��.bmp", 880, 80, 11, 1);

	_playerGetatk = IMAGEMANAGER->addFrameImage("�÷��̾��ǰ�", "�÷��̾�/��ũ�ǰ�_125+24_5��.bmp", 320, 64, 5, 1);

	
	
	_playerHp = IMAGEMANAGER->addFrameImage("�÷��̾�ü��", "�÷��̾�/��Ʈ 400+80_X5Y1.bmp", 200, 50, 5, 1);
	

	_playerRc = RectMakeCenter(_playercenter.x, _playercenter.y, 64, 64);//�÷��̾� ��Ʈ
	
	_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 32, 10, 10);//�ǰ����� ��Ʈ�Դϴ�
	_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 32, 10, 10);
	_getAtktopRc = RectMakeCenter(_playerRc.left + 32, _playerRc.top, 10, 10);
	_getAtkbottomRc = RectMakeCenter(_playerRc.left + 32, _playerRc.bottom, 10, 10);
	
	_left = false;//�̵� ���� ����
	_right = false;
	_up = false;
	_down = false;

	_leftatk = false;//���� ���� ����
	_rightatk = false;
	_upatk = false;
	_frontatk = false;


	_getatkleft = false;//���� ���� ����
	_getatkright = false;
	_getatktop = false;
	_getatkbottom = false;

	_count = _index = 0;//�����ӷ����� �� ���� �ʱ�ȭ

	_hpCount = 4;

	_getatk = false;

	return S_OK;
}

void player::release()
{
	_inventory->release();//�κ��丮 Ŭ���� ����
	SAFE_DELETE(_inventory);
}

void player::update()
{
	_state = IDLE;//�÷��̾� ���� : ���̵�

	if (INPUT->getKey(VK_LEFT) && _playerRc.left >= 0)//�������� �̵��մϴ�
	{
		_left = true;
		_state = LEFT;//���� �ٲ��ְ�

		_playerRc.left -= 3;
		_playerRc.right -= 3;



		if (INPUT->getKey(VK_SPACE))//�������� �����մϴ�
		{
			_leftatk = true;
			_state = LEFTATK;//�������� ���� ���·� �ٲ��ݴϴ�

			_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 40, 10, 10);//���̵� ������ ��Ʈ�� ũ��� ���� ������ ��Ʈ�� ũ�Ⱑ �ٸ��Ƿ� �ٽ� �ǰ�������Ʈ�� �׷��ݴϴ�
			_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 40, 10, 10);
			_getAtktopRc = RectMakeCenter(_playerRc.left + 40, _playerRc.top, 10, 10);
			_getAtkbottomRc = RectMakeCenter(_playerRc.left + 40, _playerRc.bottom, 10, 10);

		}
	}


	//===========================================������� ����================================================================//



	//�밢�� �̵��� �Ұ����ϰԲ� �������� ó��
	else if (INPUT->getKey(VK_RIGHT) && _playerRc.right <= WINSIZEX)//���������� �̵��մϴ�
	{
		_right = true;
		_state = RIGHT;//���� �ٲ��ְ�

		_playerRc.left += 3;
		_playerRc.right += 3;

		if (INPUT->getKey(VK_SPACE))//���������� �����մϴ�
		{
			_rightatk = true;
			_state = RIGHTATK;//���������� ���� ���·� �ٲ��ݴϴ�

			_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 40, 10, 10);
			_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 40, 10, 10);
			_getAtktopRc = RectMakeCenter(_playerRc.left + 40, _playerRc.top, 10, 10);
			_getAtkbottomRc = RectMakeCenter(_playerRc.left + 40, _playerRc.bottom, 10, 10);

		}
	}


	//===========================================������� ������================================================================//
	


	else if (INPUT->getKey(VK_UP) && _playerRc.top >= 0)//�������� �̵��մϴ�
	{
		_up = true;
		_state = UP;//���� �ٲ��ְ�

		_playerRc.top -= 3;
		_playerRc.bottom -= 3;

		if (INPUT->getKey(VK_SPACE))//�������� �����մϴ�
		{
			_upatk = true;
			_state = UPATK;//�������� ���� ���·� �ٲ��ݴϴ�

			_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 40, 10, 10);
			_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 40, 10, 10);
			_getAtktopRc = RectMakeCenter(_playerRc.left + 40, _playerRc.top, 10, 10);
			_getAtkbottomRc = RectMakeCenter(_playerRc.left + 40, _playerRc.bottom, 10, 10);

		}
	}


	//===========================================������� ����================================================================//


	else if (INPUT->getKey(VK_DOWN) && _playerRc.bottom <= WINSIZEY)//�Ʒ������� �̵��մϴ�
	{
		_down = true;
		_state = DOWN;//���� �ٲ��ְ�

		_playerRc.top += 3;
		_playerRc.bottom += 3;

		if (INPUT->getKey(VK_SPACE))//�Ʒ������� �����մϴ�
		{
			_frontatk = true;
			_state = FRONTATK;//�Ʒ������� ���� ���·� �ٲ��ݴϴ�

			_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 40, 10, 10);
			_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 40, 10, 10);
			_getAtktopRc = RectMakeCenter(_playerRc.left + 40, _playerRc.top, 10, 10);
			_getAtkbottomRc = RectMakeCenter(_playerRc.left + 40, _playerRc.bottom, 10, 10);

		}
	}


	//===========================================������� �Ʒ���================================================================//



	this->animation();//�ִϸ��̼� �����ݽô�


	_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 32, 10, 10);//���̵�, �̵� ������ �ǰ����� ��Ʈ�Դϴ�
	_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 32, 10, 10);
	_getAtktopRc = RectMakeCenter(_playerRc.left + 32, _playerRc.top, 10, 10);
	_getAtkbottomRc = RectMakeCenter(_playerRc.left + 32, _playerRc.bottom, 10, 10);


	//if(IntersectRect(&empty, &_getAtkleftRc, &/*���� ��Ʈ �����ּ���*/)
	//	{
	//		_hpCount--;
	//	}
	//else if (IntersectRect(&empty, &_getAtkrightRc, &/*���� ��Ʈ �����ּ���*/)
	//{
	//	_hpCount--;
	//}
	//else if (IntersectRect(&empty, &_getAtktopRc, &/*���� ��Ʈ �����ּ���*/)
	//{
	//	_hpCount--;
	//}
	//else if (IntersectRect(&empty, &_getAtkbottomRc, &/*���� ��Ʈ �����ּ���*/)
	//{
	//	_hpCount--;
	//}





	_inventory->update();//�κ��丮 ������Ʈ
}

void player::render()
{

	Rectangle(getMemDC(), _playerRc);


	if (_state == IDLE)
	{
		_playerImage->render(getMemDC(), _playerRc.left, _playerRc.top);
	}
	if (_state == LEFT)
	{
		_playerLeft->frameRender(getMemDC(), _playerRc.left, _playerRc.top);
	}
	if (_state == RIGHT)
	{
		_playerRight->frameRender(getMemDC(), _playerRc.left, _playerRc.top);
	}
	if (_state == UP)
	{
		_playerUp->frameRender(getMemDC(), _playerRc.left, _playerRc.top);
	}
	if (_state == DOWN)
	{
		_playerDown->frameRender(getMemDC(), _playerRc.left, _playerRc.top);
	}



	//======================������� �̵�====================================//


	if (_state == LEFTATK)
	{
		_playerLeftatk->frameRender(getMemDC(), _playerRc.left - 20, _playerRc.top - 15);
	}
	if (_state == RIGHTATK)
	{
		_playerRightatk->frameRender(getMemDC(), _playerRc.left + 10, _playerRc.top - 10);
	}
	if (_state == UPATK)
	{
		_playerUpatk->frameRender(getMemDC(), _playerRc.left - 10, _playerRc.top - 15);
	}
	if (_state == FRONTATK)
	{
		_playerFrontatk->frameRender(getMemDC(), _playerRc.left - 10, _playerRc.top);
	}


	if (_hpCount == 4)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 5, 0);
		_getatk = true;
		_state = GETATK;

		if (_count > 5000 == 0)
		{
			_state = IDLE;
			_count = 0;
		}
	}
	if (_hpCount == 3)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 4, 0);
		_getatk = true;
		_state = GETATK;

		if (_count > 5000 == 0)
		{
			_state = IDLE;
			_count = 0;
		}
	}
	if (_hpCount == 2)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 3, 0);
		_getatk = true;
		_state = GETATK;

		if (_count > 5000 == 0)
		{
			_state = IDLE;
			_count = 0;
		}
	}
	if (_hpCount == 1)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 2, 0);
		_getatk = true;
		_state = GETATK;

		if (_count > 5000 == 0)
		{
			_state = IDLE;
			_count = 0;
		}
	}
	if (_hpCount == 0)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 1, 0);
		_state = DEAD;
	}
	//=============================������� ����=========================================================================//

	Rectangle(getMemDC(), _getAtkleftRc);//�ǰ����� ��Ʈ�Դϴ�
	Rectangle(getMemDC(), _getAtkrightRc);
	Rectangle(getMemDC(), _getAtktopRc);
	Rectangle(getMemDC(), _getAtkbottomRc);


	_inventory->render();//�κ��丮 �׷��ݴϴ�
}



void player::animation()
{
	switch (_state)
	{

	case IDLE:

		_playerImage->render(getMemDC(), _playerRc.left, _playerRc.top);

		break;

	case LEFT:

		if (_left)
		{
			_count++;
			_playerLeft->setFrameY(0);

			if (_count % 10 == 0)
			{
				_index++;

				if (_index >= 10)
				{
					_index = 0;
				}
				_playerLeft->setFrameX(_index);
			}
		}
		break;
	case RIGHT:

		if (_right)
		{
			_count++;
			_playerRight->setFrameY(0);
			if (_count % 10 == 0)
			{
				_index++;

				if (_index >= 10)
				{
					_index = 0;
				}
				_playerRight->setFrameX(_index);
			}
		}
		break;
	case UP:

		if (_up)
		{
			_count++;
			_playerUp->setFrameY(0);
			if (_count % 10 == 0)
			{
				_index++;

				if (_index >= 10)
				{
					_index = 0;
				}
				_playerUp->setFrameX(_index);
			}
		}
		break;
	case DOWN:

		if (_down)
		{
			_count++;
			_playerDown->setFrameY(0);
			if (_count % 10 == 0)
			{
				_index++;

				if (_index >= 10)
				{
					_index = 0;
				}
				_playerDown->setFrameX(_index);
			}
		}
		break;


		//================================================================������� �̵�==================================================================//



	case LEFTATK:

		if (_leftatk)
		{
			_count++;
			_playerLeftatk->setFrameY(0);
			if (_count % 3 == 0)
			{
				_index++;

				if (_index >= 29)
				{
					_index = 0;
				}
				_playerLeftatk->setFrameX(_index);
			}
		}
		break;
	case RIGHTATK:

		if (_rightatk)
		{
			_count++;
			_playerRightatk->setFrameY(0);

			if (_count % 3 == 0)
			{
				_index++;

				if (_index >= 29)
				{
					_index = 0;
				}
				_playerRightatk->setFrameX(_index);
			}
		}
		break;
	case UPATK:

		if (_upatk)
		{
			_count++;
			_playerUpatk->setFrameY(0);

			if (_count % 3 == 0)
			{
				_index++;

				if (_index >= 11)
				{
					_index = 0;
				}
				_playerUpatk->setFrameX(_index);
			}
		}
		break;

	case FRONTATK:

		if (_frontatk)
		{
			_count++;
			_playerFrontatk->setFrameY(0);

			if (_count % 5 == 0)
			{
				_index++;

				if (_index >= 11)
				{
					_index = 0;
				}
				_playerFrontatk->setFrameX(_index);
			}
		}
		break;
	case GETATK:

		if (_hpCount == 0)
		{
			_count++;
			_playerGetatk->setFrameY(0);

			if (_count % 5 == 0)
			{
				_index++;

				if (_index >= 5)
				{
					_index = 5;
				}

				_playerGetatk->setFrameX(_index);
			}
		}
		break;
	case DEAD:

		if (_hpCount == 0)
		{
			_count++;
			_playerGetatk->setFrameY(0);

			if (_count % 5 == 0)
			{
				_index++;

				if (_index >= 5)
				{
					_index = 5;
				}

				_playerGetatk->setFrameX(_index);
			}
		}
		break;
	
	}
}