#pragma once
#include "gameNode.h"

//총알 구조체
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float speed2;
	float angle;
	float gravity;
	float radius;
	bool fire;
};

//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들어야 함)
//=============================================================
class bullet : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	bullet() {}
	~bullet() {}
};


//=============================================================
//	## missile ## (missile[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
class missile : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//플레이어 시작
private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수
	int frameX[30];
	int frameY[30];
	int _count;
	int _power;

public:
	// GET, SET 함수
	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);
	int getPower() { return _power; }
	void setPower(int power) { _power = power; }

	//총알발사
	void fire(float x, float y, float angle);
	//총알무브
	void move();
	// 총알 제거
	void eraseBullet(int num);

	//플레이어 끝




	missile() {}
	~missile() {}

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
};