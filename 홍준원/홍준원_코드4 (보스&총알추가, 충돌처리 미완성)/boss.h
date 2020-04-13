#pragma once
#include "gameNode.h"
#include "bullet.h"

#define BOSS_HP 15000			// ���� HP

// Ŭ���� ���� ���� (��ȣ ������)
class player;

enum bossState
{
	BOSS_IDLE,
	BOSS_FIREBALL,
	BOSS_TELESTART,
	BOSS_TELEEND,
	BOSS_DEAD
};

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
	int destroyX, destroyY;
	bool _direction;
};

class boss : public gameNode
{
private:
	// �ּҰ� ����
	player* _playerAdress;				// player Ŭ���� �ּҰ�

private:
	vector<tagBoss> _boss;				// boss ��ü
	missileB* _missile;					// fireBall ��ü
	missileE* _missileE;				// eyeShield ��ü
	missileE2* _missileE2;				// ���˺��� ��ü

	image* _bossIdle;
	image* _fireBall;
	image* _teleportS;
	image* _teleportE;
	image* _eyeShield;

	int _count;
	

public:
	// GET, SET �Լ�
	vector<tagBoss> getBoss() { return _boss; }
	missileB* getMissile() { return _missile; }
	missileE* getMissileE() { return _missileE; }
	missileE2* getMissileE2() { return _missileE2; }

	//�ּҰ� �ޱ�
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }

	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();


	boss() {}
	~boss() {}
};

