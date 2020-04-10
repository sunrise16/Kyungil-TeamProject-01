#include "stdafx.h"
#include "octopus.h"
#include "player.h"

// �ʱ�ȭ (init)
HRESULT octopus::init()
{
	// ���� �̹��� �߰�
	_red = IMAGEMANAGER->addFrameImage("red", "Images/Enemy/Octopus/�������� 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_blue = IMAGEMANAGER->addFrameImage("blue", "Images/Enemy/Octopus/�ϴû����� 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_yellow = IMAGEMANAGER->addFrameImage("yellow", "Images/Enemy/Octopus/������� 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_destroy1 = IMAGEMANAGER->addFrameImage("destroy1", "Images/Enemy/Octopus/�����ı� 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));
	_destroy2 = IMAGEMANAGER->addFrameImage("destroy2", "Images/Enemy/Octopus/�����ı�1 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));
	_destroy3 = IMAGEMANAGER->addFrameImage("destroy3", "Images/Enemy/Octopus/�����ı�2 1280 + 64 _ X10 Y1.bmp", 1280, 64, 10, 1, true, RGB(255, 0, 255));

	// ���� ����ü �ʱ�ȭ
	tagOctopus octo;
	ZeroMemory(&octo, sizeof(tagOctopus));

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

	// missile Ŭ���� ���� �Ҵ� ����
	_missile = new missile;
	_missile->init(30, 500);

	// �ʱ�ȭ ����
	return S_OK;
}

// ���� (release)
void octopus::release()
{
	// missile Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);
}

// ������Ʈ (update)
void octopus::update()
{
	// ���콺 ��Ŭ�� �� ���� �߰�
	if (INPUT->getKeyDown(VK_LBUTTON))
	{
		tagOctopus octopus;
		octopus.x = RANDOM->Range(0, WINSIZEX - 80);
		octopus.y = RANDOM->Range(0, WINSIZEY - 64);
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
	}

	// ���� �̵�
	for (int i = 0; i < _octopus.size(); i++)
	{
		// octopus RECT ����
		_octopus[i]._rc = RectMakeCenter(_octopus[i].x, _octopus[i].y, 60, 64);

		//_octopus[i]._hp -= 1;					// �׾����� ��� Ȯ�� (�׽�Ʈ��)
		if (_octopus[i].x - 32 < 0)
		{
			_octopus[i].x = 32;
		}
		if (_octopus[i].x + 32 > WINSIZEX)
		{
			_octopus[i].x = WINSIZEX - 32;
		}
		if (_octopus[i].y - 40 < 0)
		{
			_octopus[i].y = 40;
		}
		if (_octopus[i].y + 40 > WINSIZEY)
		{
			_octopus[i].y = WINSIZEY - 40;
		}

		// ������ ü���� 0 �̻��� �� (������� ��)
		if (_octopus[i]._hp > 0)
		{
			// ������ ������ ������ ��
			if (_octopus[i].frameY == OCTO_LEFT)
			{
				_octopus[i].x -= 0.5;
				_octopus[i]._count++;
				if (_octopus[i]._count % 50 == 0)
				{
					_octopus[i].frameX++;
				}
				if (_octopus[i].frameX > 3)				// ���� ���� ���, �̵� ����
				{
					_octopus[i].x += 0.5;
				}
				if (_octopus[i]._count % 250 == 0)		// ���� ����
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
			// ������ ������ �������� ��
			if (_octopus[i].frameY == OCTO_RIGHT)
			{
				_octopus[i].x += 0.5;
				_octopus[i]._count++;
				if (_octopus[i]._count % 50 == 0)
				{
					_octopus[i].frameX++;
				}
				if (_octopus[i].frameX > 3)				// ���� ���� ���, �̵� ����
				{
					_octopus[i].x -= 0.5;
				}
				if (_octopus[i]._count % 250 == 0)		// ���� ����
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
			// ������ ������ ������ ��
			if (_octopus[i].frameY == OCTO_UP)
			{
				_octopus[i].y -= 0.5;
				_octopus[i]._count++;
				if (_octopus[i]._count % 50 == 0)
				{
					_octopus[i].frameX++;
				}
				if (_octopus[i].frameX > 3)				// ���� ���� ���, �̵� ����
				{
					_octopus[i].y += 0.5;
				}
				if (_octopus[i]._count % 250 == 0)		// ���� ����
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
			// ������ ������ �Ʒ����� ��
			if (_octopus[i].frameY == OCTO_DOWN)
			{
				_octopus[i].y += 0.5;
				_octopus[i]._count++;
				if (_octopus[i]._count % 50 == 0)
				{
					_octopus[i].frameX++;
				}
				if (_octopus[i].frameX > 3)				// ���� ���� ���, �̵� ����
				{
					_octopus[i].y -= 0.5;
				}
				if (_octopus[i]._count % 250 == 0)		// ���� ����
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
		}
	}

	// ���� ���
	for (int i = 0; i < _octopus.size(); i++)
	{
		if (_octopus[i]._hp <= 0)
		{
			_octopus[i]._hp = 0;
			_octopus[i]._count++;
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

	// missile Ŭ���� ������Ʈ
	_missile->update();
}

// ���� (render)
void octopus::render()
{
	for (int i = 0; i < _octopus.size(); i++)
	{
		// ���� ���� (0 = red , 1 = blue , 2 = yellow)
		// ��� ������� ��
		if (_octopus[i]._hp > 0)
		{
			if (_octopus[i]._color == 0)
			{
				// RECT Ȱ��
				// IMAGEMANAGER->frameRender("red", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top,_octopus[i].frameX,_octopus[i].frameY);
				// �̹��� Ȱ��
				_red->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
			}
			if (_octopus[i]._color == 1)
			{
				// RECT Ȱ��
				// IMAGEMANAGER->frameRender("blue", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
				// �̹��� Ȱ��
				_blue->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
			}
			if (_octopus[i]._color == 2)
			{
				// RECT Ȱ��
				// IMAGEMANAGER->frameRender("yellow", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
				// �̹��� Ȱ��
				_yellow->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
			}
		}
		// ��� �׾��� ��
		else
		{
			// ��� ��� ���
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
		// Rectangle(getMemDC(), _octopus[i]._rc);			// ���� RECT Ȯ�� (�׽�Ʈ��)
	}

	// missile Ŭ���� ����
	_missile->render();
}