#include "stdafx.h"
#include "bullet.h"

// 초기화 (init) - bullet 클래스
HRESULT bullet::init()
{
	// 초기화 종료
	return S_OK;
}

// 해제 (release) - bullet 클래스
void bullet::release()
{
}

// 업데이트 (update) - bullet 클래스
void bullet::update()
{
}

// 렌더 (render) - bullet 클래스
void bullet::render()
{
}

// 초기화 (init) - missile 클래스
HRESULT missile::init(int bulletMax, float range)
{
	// 총알 사거리 및 총알 갯수 초기화
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	// 총알의 갯수만큼 구조체 초기화 후 벡터에 담기
	for (int i = 0; i < bulletMax; i++)
	{
		// 총알 구조체 선언
		tagBullet bullet;

		// 총알 구조체 초기화
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/Enemy/Octopus/문어총알 96 + 32 _ X3 Y1.bmp", 96, 32, 3, 1, true, RGB(255, 0, 255));
		bullet.speed = 10.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;

		// 벡터에 담기
		_vBullet.push_back(bullet);
	}

	// 초기화 종료
	return S_OK;
}

// 해제 (release) - missile 클래스
void missile::release()
{
	// 총알 벡터 삭제
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

// 업데이트 (update)
void missile::update()
{
	// 총알 이동
	this->move();
}

// 렌더 (render)
void missile::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		// _vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top, frameX[i], frameY[i]);
		// Rectangle(getMemDC(), _vBullet[i].rc);
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

// 총알 발사
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

// 총알 이동
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

		// 총알이 사거리보다 커졌을 때
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

// 총알 상태 세팅
void missile::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

// 총알 RECT 세팅
void missile::setRC(int num)
{
	_vBullet[num].rc = RectMakeCenter(-2000, 2000, 0, 0);
}

// 총알 제거
void missile::eraseBullet(int num)
{
	_vBullet.erase(_vBullet.begin() + num);
}