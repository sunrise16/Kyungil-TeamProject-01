#pragma once
#include "gameNode.h"
#include "bullet.h"

#define MUSHROOM_MAX 9			//버섯 수
#define MUSHROOM_HP 300			//버섯 HP

// 클래스 전방 선언 (상호 참조용)
class player;

enum mushState
{
	MUSH_DOWN,
	MUSH_LEFT,
	MUSH_RIGHT,
	MUSH_UP,
	MUSH_ATKDOWN,
	MUSH_ATKLEFT,
	MUSH_ATKRIGHT,
	MUSH_ATKUP
};

struct tagMushroom
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
	int hitFrameX, hitFrameY;
	int _state;
	int destroyX, destroyY;
	bool _direction;
};

class mushroom : public gameNode
{
private:
	// 주소값 관련
	player* _playerAdress;				// player 클래스 주소값
	missile* _missile;

private:
	vector<tagMushroom> _mushroom;		//문어 구조체 선언
	
	
	//이미지 관련
	image* _room;
	image* _destroy4;					// 버섯 파괴
	image* _getAtk;


public:
	// GET, SET 함수
	vector<tagMushroom> getMushroom() { return _mushroom; }
	// 주소값 받기
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }

	HRESULT init();
	void release();
	void update();
	void render();

	void animation();

	mushroom() {}
	~mushroom() {}
};

