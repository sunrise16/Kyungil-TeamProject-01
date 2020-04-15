#pragma once
#include "gameNode.h"
#include "bullet.h"

#define MUSHROOM_HP 300			// 버섯의 HP
#define MUSHROOM_MAX 9			// 버섯의 최대 마리수

// 클래스 전방 선언 (상호 참조용)
class player;

// 버섯의 현재 상태 열거문
enum mushState
{
	MUSH_DOWN,					// 버섯의 방향 (아래쪽)
	MUSH_LEFT,					// 버섯의 방향 (왼쪽)
	MUSH_RIGHT,					// 버섯의 방향 (오른쪽)
	MUSH_UP,					// 버섯의 방향 (위쪽)
	MUSH_ATKDOWN,				// 버섯의 방향 (아래쪽 공격)
	MUSH_ATKLEFT,				// 버섯의 방향 (왼쪽 공격)
	MUSH_ATKRIGHT,				// 버섯의 방향 (오른쪽 공격)
	MUSH_ATKUP					// 버섯의 방향 (위쪽 공격)
};

// 버섯 구조체
struct tagMushroom
{
	RECT _rc;							// 버섯의 RECT
	int _hp;							// 버섯의 HP
	float x, y;							// 버섯의 X, Y좌표
	float _angle;						// 버섯의 각도
	float _speed;						// 버섯의 속도
	int _count;							// 버섯 애니메이션 딜레이값
	int _dead;							// 버섯 사망 모션 딜레이값
	int frameX, frameY;					// 버섯 애니메이션 프레임 X, Y값
	int hitFrameX, hitFrameY;			// 버섯 피격 애니메이션 프레임 X, Y값
	int _state;							// 버섯의 종류값
	int destroyX, destroyY;				// 버섯 사망 모션 딜레이값
	bool _direction;					// 버섯 방향
};

// mushroom 클래스
class mushroom : public gameNode
{
private:
	// 주소값 관련
	player* _playerAdress;				// player 클래스 주소값

	//이미지 관련
	image* _room;						// 버섯 이미지
	image* _destroy4;					// 버섯 파괴
	image* _getAtk;						// 버섯 피격

	// 객체 관련
	vector<tagMushroom> _mushroom;		// tagMushroom 구조체를 담은 mushroom 벡터 객체
	missile* _missile;					// 버섯이 발사할 탄(missile) 객체

public:
	// GET, SET 함수
	vector<tagMushroom> getMushroom() { return _mushroom; }
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
	mushroom() {}
	~mushroom() {}
};