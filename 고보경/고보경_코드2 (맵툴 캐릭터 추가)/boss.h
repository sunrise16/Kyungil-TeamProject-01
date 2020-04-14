#pragma once
#include "gameNode.h"
#include "bullet.h"

#define BOSS_HP 15000			// 보스 HP

// 클래스 전방 선언 (상호 참조용)
class player;

// 보스의 현재 상태 열거문
enum bossState
{
	BOSS_IDLE,
	BOSS_FIREBALL,
	BOSS_TELESTART,
	BOSS_TELEEND,
	BOSS_DEAD
};

// 보스 구조체
struct tagBoss
{
	RECT _rc;
	int _hp;
	float x, y;
	float _angle;
	float _speed;
	float _radius;
	int _count;
	int _dead;
	int _move;
	int frameX, frameY;
	int fireFrameX, fireFrameY;
	int _state;
	int telFrameX, telFrameY;
	bool _direction;
};

// boss 클래스
class boss : public gameNode
{
private:
	// 주소값 관련
	player* _playerAdress;				// player 클래스 주소값

	// 이미지 관련
	image* _bossIdle;
	image* _fireBall;
	image* _teleportS;
	image* _teleportE;
	image* _eyeShield;
	int _count;

	// 객체 관련
	vector<tagBoss> _boss;				// boss 객체
	missileB* _missile;					// fireBall 객체
	missileE* _missileE;				// eyeShield 객체
	missileE2* _missileE2;				// 눈알빙빙 객체

	int scrollX;
	int scrollY;

public:
	// GET, SET 함수
	vector<tagBoss> getBoss() { return _boss; }
	missileB* getMissile() { return _missile; }
	missileE* getMissileE() { return _missileE; }
	missileE2* getMissileE2() { return _missileE2; }
	//주소값 받기
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }

	// 초기화 처리
	HRESULT init(float x, float y);

	// 해제 처리
	void release();

	// 계산식 처리
	void update(int _scrollX, int _scrollY, bool isStart, bool playerSet);

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	boss() {}
	~boss() {}

};