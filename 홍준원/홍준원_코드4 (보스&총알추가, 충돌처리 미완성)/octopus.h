#pragma once
#include "gameNode.h"
#include "bullet.h"

#define MINION_HP 300			// ���� HP
#define MINION_MAX 9			// ���� ��

// Ŭ���� ���� ���� (��ȣ ������)
class player;

// ���� ���� ���� ���Ź�
enum octoState
{
	OCTO_DOWN = 0,			// ���� ���� (����)
	OCTO_LEFT = 1,			// ���� ���� (������)
	OCTO_RIGHT = 2,			// ���� ���� (����)
	OCTO_UP = 3			// ���� ���� (�Ʒ���)
};

//���� ����ü ����
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
	// �ּҰ� ����
	player* _playerAdress;				// player Ŭ���� �ּҰ�

private:
	// �̹��� ����
	image* _red;						// ���� �̹��� (����)
	image* _blue;						// ���� �̹��� (�Ķ�)
	image* _yellow;						// ���� �̹��� (���)
	image* _destroy1;					// ���� �ı� 1
	image* _destroy2;					// ���� �ı� 2
	image* _destroy3;					// ���� �ı� 3

	// ��ü ����
	vector<tagOctopus> _octopus;		// octopus ��ü
	missile* _missile;					// missile ��ü

public:
	// GET, SET �Լ�
	vector<tagOctopus> getOctopus() { return _octopus; }
	missile* getMissile() { return _missile; }
	// �ּҰ� �ޱ�
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }

	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ������, �Ҹ���
	octopus() {}
	~octopus() {}
};


