#include "stdafx.h"
#include "mushroom.h"
#include "player.h"

HRESULT mushroom::init()
{
	//���� �̹��� ����
	_room = IMAGEMANAGER->addFrameImage("mushroom", "Images/Enemy/Mushroom/�������� 2048 + 128 _ X16 Y1.bmp", 2048, 128, 16, 1, true, RGB(255, 0, 255));
	_destroy4 = IMAGEMANAGER->addFrameImage("destroy4", "Images/Enemy/Mushroom/�����ı� 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));

	//���� ����ü �ʱ�ȭ
	//for (int i = 0; i < _octopus.size(); i++)
	//{
	//	//���Ʈ ��ġ ���� ����
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

void mushroom::release()
{
	_missile->release();
	SAFE_DELETE(_missile);
}

void mushroom::update()
{
	_missile->update();

	if (INPUT->getKeyDown(VK_RBUTTON))
	{
		tagMushroom mushroom;
		mushroom.x = RANDOM->Range(0, WINSIZEX - 128);
		mushroom.y = RANDOM->Range(0, WINSIZEY - 128);
		mushroom._rc = RectMakeCenter(mushroom.x, mushroom.y, 100, 100);		// �̹��� ������ �� Ŀ�� ��Ʈ�� ����;
		mushroom._hp = MUSHROOM_HP;
		mushroom._angle = PI_2;
		mushroom._speed = 1.0f;
		mushroom.frameX = 0;
		mushroom.frameY = 0;
		mushroom._state = RANDOM->Range(0, 3);
		mushroom._direction = RANDOM->Range(0, 1);
		mushroom.destroyX = mushroom.destroyY = 0;
		mushroom._count = 0;
		mushroom._dead = 0;
		_mushroom.push_back(mushroom);
	}

	
	for (int i = 0; i < _mushroom.size(); i++)
	{
		_mushroom[i]._hp -= 1;			//�׾����� ��� Ȯ��
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


		//������ ������� ��
		if (_mushroom[i]._hp > 0)
		{
			//�������� (�Ʒ���)
			if (_mushroom[i]._state == MUSH_DOWN)
			{
				if (!_mushroom[i]._direction)			//���� �̵�����
				{
					_mushroom[i]._angle += 0.03f;
				}
				else if (_mushroom[i]._direction)
				{
					_mushroom[i]._angle -= 0.03f;
				}
				if (_mushroom[i]._count % 20 == 0)		//���� ������ī��Ʈ
				{
					_mushroom[i].frameX++;
				}
				if (_mushroom[i].frameX > 15)			//���� ���� �ʱ�ȭ
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
			//�������� (����)
			if (_mushroom[i]._state == MUSH_LEFT)
			{
				if (!_mushroom[i]._direction)			//���� �̵�����
				{
					_mushroom[i]._angle += 0.03f;
				}
				else if (_mushroom[i]._direction)
				{
					_mushroom[i]._angle -= 0.03f;
				}
				if (_mushroom[i]._count % 20 == 0)		//���� ������ī��Ʈ
				{
					_mushroom[i].frameX++;
				}
				if (_mushroom[i].frameX > 15)			//���� ���� �ʱ�ȭ
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
			//�������� (������)
			if (_mushroom[i]._state == MUSH_RIGHT)
			{
				if (!_mushroom[i]._direction)			//���� �̵�����
				{
					_mushroom[i]._angle += 0.03f;
				}
				else if (_mushroom[i]._direction)
				{
					_mushroom[i]._angle -= 0.03f;
				}
				if (_mushroom[i]._count % 20 == 0)		//���� ������ī��Ʈ
				{
					_mushroom[i].frameX++;
				}
				if (_mushroom[i].frameX > 15)			//���� ���� �ʱ�ȭ
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
			//�������� (����)
			if (_mushroom[i]._state == MUSH_UP)
			{
				if (!_mushroom[i]._direction)			//���� �̵�����
				{
					_mushroom[i]._angle += 0.03f;
				}
				else if (_mushroom[i]._direction)
				{
					_mushroom[i]._angle -= 0.03f;
				}
				if (_mushroom[i]._count % 20 == 0)		//���� ������ī��Ʈ
				{
					_mushroom[i].frameX++;
				}
				if (_mushroom[i].frameX > 15)			//���� ���� �ʱ�ȭ
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
		}
	}

	for (int i = 0; i < _mushroom.size(); i++)
	{
		if (_mushroom[i]._hp <= 0)
		{
			_mushroom[i]._hp = 0;
			_mushroom[i]._dead++;
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
}

void mushroom::render()
{
	_missile->render();
	for (int i = 0; i < _mushroom.size(); i++)
	{
		if (_mushroom[i]._hp > 0)
		{
			
			_room->frameRender(getMemDC(), _mushroom[i].x - 64, _mushroom[i].y - 64, _mushroom[i].frameX, 0);
		}
		else
		{
			_destroy4->frameRender(getMemDC(), _mushroom[i].x - 64, _mushroom[i].y - 32, _mushroom[i].destroyX, 0);
		}
		//���� ��Ʈ Ȯ��
		//Rectangle(getMemDC(), _octopus[i]._rc);
	}
}
