#include "stdafx.h"
#include "bullet.h"
#include "player.h"

//=============================================================
//	## bullet ## (�����Ѿ� - ������� ������ ��)
//=============================================================
HRESULT bullet::init()
{
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
}

void bullet::render()
{
}

//=============================================================
//	## missile ## (missile[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
HRESULT missile::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/Enemy/Octopus/�����Ѿ� 96 + 32 _ X3 Y1.bmp", 96, 32, 3, 1, true, RGB(255, 0, 255));
		bullet.speed = 10.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missile::update()
{


	this->move();
}

void missile::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top, frameX[i], frameY[i]);
		Rectangle(getMemDC(), _vBullet[i].rc);
		_count++;
		if (_count % 5 == 0)
		{
			frameX[i]++;
			if (frameX[i] > 2)
			{
				frameX[i] = 0;
			}

			frameY[i] = 0;
		}

	}
}

void missile::fire(float x, float y, float angle)
{

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->angle = angle;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);
		break;
	}
}

void missile::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		for (int i = 0; i < 30; i++)
		{
			if (_range < distance)
			{
				_viBullet->fire = false;
			}
		}
	}
}

void missile::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

void missile::setRC(int num)
{
	_vBullet[num].rc = RectMakeCenter(-2000, 2000, 0, 0);
}

void missile::eraseBullet(int num)
{
	_vBullet.erase(_vBullet.begin() + num);
}


//���� ���̾
HRESULT missileB::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/Enemy/Boss/���̾ 448 + 128 _ X4 Y1.bmp", 448, 128, 4, 1, true, RGB(255, 0, 255));
		bullet.speed = 8.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missileB::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missileB::update()
{


	this->move();
}

void missileB::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left - 20, _vBullet[i].rc.top - 50, frameX[i], frameY[i]);
		Rectangle(getMemDC(), _vBullet[i].rc);
		_count++;
		if (_count % 5 == 0)
		{
			frameX[i]++;
			if (frameX[i] > 3)
			{
				frameX[i] = 0;
			}

			frameY[i] = 0;
		}

	}
}

void missileB::fire(float x, float y, float angle)
{

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->angle = angle;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 5,
			_viBullet->bulletImage->getHeight() / 2);
		break;
	}
}

void missileB::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y - 50,
			_viBullet->bulletImage->getWidth() / 5,
			_viBullet->bulletImage->getHeight() / 2);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		for (int i = 0; i < 30; i++)
		{
			if (_range < distance)
			{
				_viBullet->fire = false;
			}
		}
	}
}

void missileB::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

void missileB::eraseBullet(int num)
{
	_vBullet.erase(_vBullet.begin() + num);
}


//���� ����ź ����
HRESULT missileE::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/Enemy/Boss/���̽��� 1280 + 128 _ X10 Y1.bmp", 1280, 128, 10, 1, true, RGB(255, 0, 255));
		bullet.speed = 2.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missileE::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missileE::update()
{


	this->move();
}

void missileE::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left - 30, _vBullet[i].rc.top - 50, frameX[i], frameY[i]);
		Rectangle(getMemDC(), _vBullet[i].rc);
		_count++;
		if (_count % 5 == 0)
		{
			frameX[i]++;
			if (frameX[i] > 9)
			{
				frameX[i] = 0;
			}

			frameY[i] = 0;
		}

	}
}

void missileE::fire(float x, float y, float angle)
{

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->angle = angle;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y + 20,
			_viBullet->bulletImage->getWidth() / 16,
			_viBullet->bulletImage->getHeight() / 2);
		break;
	}
}

void missileE::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)

	{
		if (!_viBullet->fire) continue;
		_count++;
		_viBullet->angle = getAngle(_viBullet->x, _viBullet->y, _playerAdress->getPlayerRc().left + 32, _playerAdress->getPlayerRc().top + 32);
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y + 20,
			_viBullet->bulletImage->getWidth() / 16,
			_viBullet->bulletImage->getHeight() / 2);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		for (int i = 0; i < 30; i++)
		{
			if (_range < distance || _count > 1500)
			{
				_viBullet->fire = false;
				_count = 0;
			}
		}
	}
}

void missileE::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

void missileE::eraseBullet(int num)
{
	_vBullet.erase(_vBullet.begin() + num);
}

float missileE::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	//���� ������ �Ÿ�(����)
	float distance = sqrtf(x * x + y * y);
	//���� ������ ���� ���ϴ� ����(���Լ� ���)
	//������ X�� ���̸� �˰� ������ ������ �˼��ִ�
	float angle = acosf(x / distance);
	//����ó��
	//������ API���� acosf�� 0 ~ 180�� ������
	//���Ȱ�(0.0f ~ 3.14f) ���Ͻ�Ų��
	//180�� �̻��� �������� ����ó���� ����� �Ѵ�
	if (endY > startY)
	{
		angle = (PI * 2) - angle;
	}
	return angle;
}

//���� ���� ������
HRESULT missileE2::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/Enemy/Boss/���� 80 + 80.bmp", 64, 64, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missileE2::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missileE2::update()
{


	this->move();
}

void missileE2::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left - 15, _vBullet[i].rc.top - 20);
		Rectangle(getMemDC(), _vBullet[i].rc);
		_count++;
		if (_count % 5 == 0)
		{
			frameX[i]++;
			if (frameX[i] > 2)
			{
				frameX[i] = 0;
			}

			frameY[i] = 0;
		}

	}
}

void missileE2::fire(float x, float y, float angle)
{

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->angle = angle;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 2,
			_viBullet->bulletImage->getHeight() / 2);
		break;
	}
}

void missileE2::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_count++;
		if (!_viBullet->fire) continue;
		_viBullet->angle -= 0.02f;
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 2,
			_viBullet->bulletImage->getHeight() / 2);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		RECT temp;
		for (int i = 0; i < 30; i++)
		{
			if (_range < distance || _count % 2000 == 0 || IntersectRect(&temp, &_playerAdress->getPlayerRc(), &_viBullet->rc) ||
				IntersectRect(&temp, &_playerAdress->getAttack(), &_viBullet->rc))
			{
				_viBullet->fire = false;
				_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 0, 0);
			}
		}
	}
}

void missileE2::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

void missileE2::eraseBullet(int num)
{
	_vBullet.erase(_vBullet.begin() + num);
}