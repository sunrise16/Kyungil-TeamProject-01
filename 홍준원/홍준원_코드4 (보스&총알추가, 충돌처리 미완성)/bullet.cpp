#include "stdafx.h"
#include "bullet.h"
#include "player.h"

//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들어야 함)
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
//	## missile ## (missile[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
HRESULT missile::init(int bulletMax, float range)
{
	//총알 사거리 및 총알 갯수 초기화
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//총알구조체 초기화
		//제로메모리, 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/Enemy/Octopus/문어총알 96 + 32 _ X3 Y1.bmp", 96, 32, 3, 1, true, RGB(255, 0, 255));
		bullet.speed = 10.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//벡터에 담기
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

		//총알이 사거리보다 커졌을때
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


//보스 파이어볼
HRESULT missileB::init(int bulletMax, float range)
{
	//총알 사거리 및 총알 갯수 초기화
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//총알구조체 초기화
		//제로메모리, 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/Enemy/Boss/파이어볼 448 + 128 _ X4 Y1.bmp", 448, 128, 4, 1, true, RGB(255, 0, 255));
		bullet.speed = 8.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//벡터에 담기
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

		//총알이 사거리보다 커졌을때
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


//보스 유도탄 눈알
HRESULT missileE::init(int bulletMax, float range)
{
	//총알 사거리 및 총알 갯수 초기화
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//총알구조체 초기화
		//제로메모리, 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/Enemy/Boss/아이쉴드 1280 + 128 _ X10 Y1.bmp", 1280, 128, 10, 1, true, RGB(255, 0, 255));
		bullet.speed = 2.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//벡터에 담기
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

		//총알이 사거리보다 커졌을때
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
	//두점 사이의 거리(빗변)
	float distance = sqrtf(x * x + y * y);
	//두점 사이의 각도 구하는 공식(역함수 사용)
	//빗변과 X의 길이를 알고 있으면 각도를 알수있다
	float angle = acosf(x / distance);
	//예외처리
	//윈도우 API에서 acosf는 0 ~ 180도 까지의
	//라디안값(0.0f ~ 3.14f) 리턴시킨다
	//180도 이상의 값에대한 예외처리를 해줘야 한다
	if (endY > startY)
	{
		angle = (PI * 2) - angle;
	}
	return angle;
}

//보스 눈알 굴리기
HRESULT missileE2::init(int bulletMax, float range)
{
	//총알 사거리 및 총알 갯수 초기화
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//총알구조체 초기화
		//제로메모리, 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/Enemy/Boss/눈알 80 + 80.bmp", 64, 64, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//벡터에 담기
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

		//총알이 사거리보다 커졌을때
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