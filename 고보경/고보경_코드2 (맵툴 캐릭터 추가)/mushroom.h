#pragma once
#include "gameNode.h"
#include "bullet.h"

#define MUSHROOM_HP 300			// ������ HP
#define MUSHROOM_MAX 9			// ������ �ִ� ������

// Ŭ���� ���� ���� (��ȣ ������)
class player;

// ������ ���� ���� ���Ź�
enum mushState
{
	MUSH_DOWN,					// ������ ���� (�Ʒ���)
	MUSH_LEFT,					// ������ ���� (����)
	MUSH_RIGHT,					// ������ ���� (������)
	MUSH_UP,					// ������ ���� (����)
	MUSH_ATKDOWN,				// ������ ���� (�Ʒ��� ����)
	MUSH_ATKLEFT,				// ������ ���� (���� ����)
	MUSH_ATKRIGHT,				// ������ ���� (������ ����)
	MUSH_ATKUP					// ������ ���� (���� ����)
};

// ���� ����ü
struct tagMushroom
{
	RECT _rc;							// ������ RECT
	int _hp;							// ������ HP
	float x, y;							// ������ X, Y��ǥ
	float _angle;						// ������ ����
	float _speed;						// ������ �ӵ�
	int _count;							// ���� �ִϸ��̼� �����̰�
	int _dead;							// ���� ��� ��� �����̰�
	int frameX, frameY;					// ���� �ִϸ��̼� ������ X, Y��
	int hitFrameX, hitFrameY;			// ���� �ǰ� �ִϸ��̼� ������ X, Y��
	int _state;							// ������ ������
	int destroyX, destroyY;				// ���� ��� ��� �����̰�
	bool _direction;					// ���� ����
};

// mushroom Ŭ����
class mushroom : public gameNode
{
private:
	// �ּҰ� ����
	player* _playerAdress;				// player Ŭ���� �ּҰ�

	//�̹��� ����
	image* _room;						// ���� �̹���
	image* _destroy4;					// ���� �ı�
	image* _getAtk;						// ���� �ǰ�

	// ��ü ����
	vector<tagMushroom> _mushroom;		// tagMushroom ����ü�� ���� mushroom ���� ��ü
	missile* _missile;					// ������ �߻��� ź(missile) ��ü

	int scrollX;
	int scrollY;

public:
	// GET, SET �Լ�
	vector<tagMushroom> getMushroom() { return _mushroom; }
	// �ּҰ� �ޱ�
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }

	// �ʱ�ȭ ó��
	HRESULT init(float x, float y);

	// ���� ó��
	void release();

	// ���� ó��
	void update(int _scrollX, int _scrollY, bool isStart, bool playerOn);

	// ȭ�� ��� ó��
	void render();

	// ������, �Ҹ���
	mushroom() {}
	~mushroom() {}
};