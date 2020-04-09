#include "stdafx.h"
#include "octopus.h"

HRESULT octopus::init()
{
	//���� �̹��� ����
	_red = IMAGEMANAGER->addFrameImage("red", "�׸�����/�������� 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_blue = IMAGEMANAGER->addFrameImage("blue", "�׸�����/�ϴû����� 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));
	_yellow = IMAGEMANAGER->addFrameImage("yellow", "�׸�����/������� 480 + 256 _ X6 Y4.bmp", 480, 256, 6, 4, true, RGB(255, 0, 255));

	//���� ����ü �ʱ�ȭ
	for (int i = 0; i < MINION_MAX; i++)
	{
		//���Ʈ ��ġ ���� ����
		_octopus[i].x = RANDOM->Range(0, WINSIZEX - 80);
		_octopus[i].y = RANDOM->Range(0, WINSIZEY - 64);
		_octopus[i]._hp = MINION_HP;
		_octopus[i]._angle = PI_2;
		_octopus[i]._speed = 3.0f;
		_octopus[i].frameX = 0;
		_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
		_octopus[i]._state = RANDOM->Range(0, 3);
	}

	_missile = new missile;
	_missile->init(30, 500);

	return S_OK;
}

void octopus::release()
{
	_missile->release();
	SAFE_DELETE(_missile);
}

void octopus::update()
{
	_missile->update();

	for (int i = 0; i < MINION_MAX; i++)
	{
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

		if (_octopus[i].frameY == octo_DOWN)
		{
			_octopus[i].y += 0.5;
			_octopus[i]._count++;
			if (_octopus[i]._count % 50 == 0)
			{
				_octopus[i].frameX++;
			}
			if (_octopus[i].frameX > 3)				//���� �������, �̵� ����
			{
				_octopus[i].y -= 0.5;
			}
			if (_octopus[i]._count % 250 == 0)			//���� �߻�
			{
				_missile->fire(_octopus[i].x, _octopus[i].y + 32, -(PI_2));
			}
			if (_octopus[i].frameX > 5)
			{
				_octopus[i].frameX = 0;
				_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
				_octopus[i]._count = RANDOM->Range(0, 30);
			}
		}
		if (_octopus[i].frameY == octo_LEFT)
		{
			_octopus[i].x -= 0.5;
			_octopus[i]._count++;
			if (_octopus[i]._count % 50 == 0)
			{
				_octopus[i].frameX++;
			}
			if (_octopus[i].frameX > 3)				//���� �������, �̵� ����
			{
				_octopus[i].x += 0.5;
			}
			if (_octopus[i]._count % 250 == 0)			//���� �߻�
			{
				_missile->fire(_octopus[i].x - 40, _octopus[i].y - 5, PI);
			}
			if (_octopus[i].frameX > 5)
			{
				_octopus[i].frameX = 0;
				_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
				_octopus[i]._count = RANDOM->Range(0, 30);
			}
		}
		if (_octopus[i].frameY == octo_RIGHT)
		{
			_octopus[i].x += 0.5;
			_octopus[i]._count++;
			if (_octopus[i]._count % 50 == 0)
			{
				_octopus[i].frameX++;
			}
			if (_octopus[i].frameX > 3)				//���� �������, �̵� ����
			{
				_octopus[i].x -= 0.5;
			}
			if (_octopus[i]._count % 250 == 0)			//���� �߻�
			{
				_missile->fire(_octopus[i].x + 40, _octopus[i].y - 5, PI2);
			}
			if (_octopus[i].frameX > 5)
			{
				_octopus[i].frameX = 0;
				_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
				_octopus[i]._count = RANDOM->Range(0, 30);
			}
		}
		if (_octopus[i].frameY == octo_UP)
		{
			_octopus[i].y -= 0.5;
			_octopus[i]._count++;
			if (_octopus[i]._count % 50 == 0)
			{
				_octopus[i].frameX++;
			}
			if (_octopus[i].frameX > 3)			//���� �������, �̵� ����
			{
				_octopus[i].y += 0.5;
			}
			if (_octopus[i]._count % 250 == 0)			//���� �߻�
			{
				_missile->fire(_octopus[i].x, _octopus[i].y - 32, PI_2);
			}
			if (_octopus[i].frameX > 5)
			{
				_octopus[i].frameX = 0;
				_octopus[i].frameY = RANDOM->Range(octo_DOWN, octo_UP);
				_octopus[i]._count = RANDOM->Range(0, 30);
			}
		}
	}
}

void octopus::render()
{
	_missile->render();
	for (int i = 0; i < MINION_MAX; i++)
	{
		if (i < 3)
		{
			//��Ʈ Ȱ��
			//IMAGEMANAGER->frameRender("red", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top,_octopus[i].frameX,_octopus[i].frameY);
			//�̹��� Ȱ��
			_red->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);
		}
		if (i >= 3 && i < 6)
		{
			//��Ʈ Ȱ��
			//IMAGEMANAGER->frameRender("blue", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
			//�̹��� Ȱ��
			_blue->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);

		}
		if (i >= 6 && i < MINION_MAX)
		{
			//��Ʈ Ȱ��
			//IMAGEMANAGER->frameRender("yellow", getMemDC(), _octopus[i]._rc.left, _octopus[i]._rc.top, _octopus[i].frameX, _octopus[i].frameY);
			//�̹��� Ȱ��
			_yellow->frameRender(getMemDC(), _octopus[i].x - 40, _octopus[i].y - 32, _octopus[i].frameX, _octopus[i].frameY);

		}
		//���� ��Ʈ Ȯ��
		//Rectangle(getMemDC(), _octopus[i]._rc);
	}
}