#pragma once
#include "gameNode.h"
#include "bullet.h"

#define MUSHROOM_MAX 9			//���� ��
#define MUSHROOM_HP 300			//���� HP

// Ŭ���� ���� ���� (��ȣ ������)
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
	// �ּҰ� ����
	player* _playerAdress;				// player Ŭ���� �ּҰ�
	missile* _missile;

private:
	vector<tagMushroom> _mushroom;		//���� ����ü ����
	
	
	//�̹��� ����
	image* _room;
	image* _destroy4;					// ���� �ı�
	image* _getAtk;


public:
	// GET, SET �Լ�
	vector<tagMushroom> getMushroom() { return _mushroom; }
	// �ּҰ� �ޱ�
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }

	HRESULT init();
	void release();
	void update();
	void render();

	void animation();

	mushroom() {}
	~mushroom() {}
};

