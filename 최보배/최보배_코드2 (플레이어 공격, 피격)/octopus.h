#pragma once
#include "gameNode.h"
#include "bullet.h"

#define MINION_HP 30			// 문어 HP
#define MINION_MAX 9			// 문어 수

// 클래스 전방 선언 (상호 참조용)
class player;

// 문어 현재 상태 열거문
enum octoState
{
	OCTO_DOWN = 0,			// 문어 방향 (왼쪽)
	OCTO_LEFT = 1,			// 문어 방향 (오른쪽)
	OCTO_RIGHT = 2,			// 문어 방향 (위쪽)
	OCTO_UP = 3				// 문어 방향 (아래쪽)
};

//문어 구조체 생성
struct tagOctopus
{
	RECT _rc;
	int _hp;
	float x, y;
	float _angle;
	float _speed;
	float _radius;
	int _count;
	int _move;
	int frameX, frameY;
	int _state;
	int destroyX, destroyY;
	int _color;
};

class octopus : public gameNode
{
private:
	// 주소값 관련
	player* _playerAdress;				// player 클래스 주소값

	// 이미지 관련
	image* _red;						// 문어 이미지 (빨강)
	image* _blue;						// 문어 이미지 (파랑)
	image* _yellow;						// 문어 이미지 (노랑)
	image* _destroy1;					// 문어 파괴 1
	image* _destroy2;					// 문어 파괴 2
	image* _destroy3;					// 문어 파괴 3

	// 객체 관련
	vector<tagOctopus> _octopus;		// octopus 객체
	missile* _missile;					// missile 객체

public:
	// GET, SET 함수
	vector<tagOctopus> getOctopus() { return _octopus; }
	missile* getMissile() { return _missile; }
	// 주소값 받기
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }
	
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	octopus() {}
	~octopus() {}
};


