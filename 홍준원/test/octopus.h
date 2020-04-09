#pragma once
#include "gameNode.h"
#include "bullet.h"

#define MINION_HP 30		//���� HP
#define MINION_MAX 9		//���� ��

enum octoState
{
	octo_DOWN,
	octo_LEFT,
	octo_RIGHT,
	octo_UP
};

//���� ����ü ����
struct tagOctopus
{
	//POINT _rc;
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
	vector<tagOctopus> _octopus;		//���� ����ü ����

	missile* _missile;

	image* _red;
	image* _blue;
	image* _yellow;
	image* _destroy;
	image* _destroy1;
	image* _destroy2;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	octopus() {}
	~octopus() {}
};


