#pragma once
#include "gameNode.h"
#include "bullet.h"

#define MINION_HP 300		// 문어의 HP
#define MINION_MAX 9			// 문어의 최대 마리수

// 클래스 전방 선언 (상호 참조용)
class player;

// 문어의 현재 상태 열거문
enum octoState
{
	OCTO_DOWN = 0,			// 문어의 방향 (왼쪽)
	OCTO_LEFT = 1,			// 문어의 방향 (오른쪽)
	OCTO_RIGHT = 2,			// 문어의 방향 (위쪽)
	OCTO_UP = 3				// 문어의 방향 (아래쪽)
};

// 문어 구조체
struct tagOctopus
{
	RECT _rc;							// 문어의 RECT
	int _hp;							// 문어의 HP
	float x, y;							// 문어의 X, Y좌표
	float _angle;						// 문어의 각도
	float _speed;						// 문어의 속도
	int _count;							// 문어 애니메이션 딜레이값
	int frameX, frameY;					// 문어 애니메이션 프레임 X, Y값
	int _state;							// 문어의 상태값
	int destroyX, destroyY;				// 문어 사망 모션 딜레이값
	int _color;							// 문어의 종류값 (색깔)
};

// octopus 클래스
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
	vector<tagOctopus> _octopus;		// tagOctopus 구조체를 담은 octopus 벡터 객체
	missile* _missile;					// 문어가 발사할 탄(missile) 객체

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