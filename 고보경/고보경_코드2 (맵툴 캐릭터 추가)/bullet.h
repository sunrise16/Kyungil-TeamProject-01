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

// bullet 클래스
class bullet : public gameNode
{
public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	bullet() {}
	~bullet() {}
};

// 문어 missile 클래스
class missile : public gameNode
{
private:
	// 객체 관련
	// 총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	
	// 변수 관련
	float _range;		// 총알 사거리
	int _bulletMax;		// 총알 최대갯수
	int frameX[30];		//
	int frameY[30];		//
	int _count;			//
	int _power;			//

public:
	// GET, SET 함수
	vector<tagBullet> getBullet() { return _vBullet; }
	int getPower() { return _power; }
	void setBullet(int num, bool fire);
	void setRC(int num);
	void setPower(int power) { _power = power; }

	// 총알 발사
	void fire(float x, float y, float angle);

	// 총알 이동
	void move();

	// 총알 제거
	void eraseBullet(int num);
	
	// 초기화 처리
	HRESULT init(int bulletMax, float range);

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	missile() {}
	~missile() {}
};

// 보스 파이어볼 클래스
class missileB : public gameNode
{
private:
	// 객체 관련
	// 총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	// 변수 관련
	float _range;		// 총알 사거리
	int _bulletMax;		// 총알 최대갯수
	int frameX[30];		//
	int frameY[30];		//
	int _count;			//
	int _power;			//

public:
	// GET, SET 함수
	vector<tagBullet> getBullet() { return _vBullet; }
	int getPower() { return _power; }
	void setBullet(int num, bool fire);
	void setPower(int power) { _power = power; }

	// 총알 발사
	void fire(float x, float y, float angle);

	// 총알 이동
	void move();

	// 총알 제거
	void eraseBullet(int num);

	// 초기화 처리
	HRESULT init(int bulletMax, float range);

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	missileB() {}
	~missileB() {}
};


// 보스 유도탄 클래스
//상호참조 플레이어 선언
class player;

class missileE : public gameNode
{
private:
	//플레이어 주소값
	player* _playerAdress;

private:
	// 객체 관련
	// 총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	// 변수 관련
	float _range;		// 총알 사거리
	int _bulletMax;		// 총알 최대갯수
	int frameX[30];		//
	int frameY[30];		//
	int _count;			//
	int _power;			//

public:
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }
	// GET, SET 함수
	vector<tagBullet> getBullet() { return _vBullet; }
	int getPower() { return _power; }
	void setBullet(int num, bool fire);
	void setPower(int power) { _power = power; }

	// 총알 발사
	void fire(float x, float y, float angle);

	// 유도탄 각도 계산
	float getAngle(float startX, float startY, float endX, float endY);

	// 총알 이동
	void move();

	// 총알 제거
	void eraseBullet(int num);

	// 초기화 처리
	HRESULT init(int bulletMax, float range);

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	missileE() {}
	~missileE() {}
};

// 보스 눈알 클래스
class missileE2 : public gameNode
{
private:
	//플레이어 주소값
	player* _playerAdress;

private:
	// 객체 관련
	// 총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	// 변수 관련
	float _range;		// 총알 사거리
	int _bulletMax;		// 총알 최대갯수
	int frameX[30];		//
	int frameY[30];		//
	int _count;			//
	int _power;			//

public:
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }
	// GET, SET 함수
	vector<tagBullet> getBullet() { return _vBullet; }
	int getPower() { return _power; }
	void setBullet(int num, bool fire);
	void setPower(int power) { _power = power; }

	// 총알 발사
	void fire(float x, float y, float angle);

	// 총알 이동
	void move();

	// 총알 제거
	void eraseBullet(int num);

	// 초기화 처리
	HRESULT init(int bulletMax, float range);

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	missileE2() {}
	~missileE2() {}
};
