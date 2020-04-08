#pragma once
#include "gameNode.h"
//#include "bullet.h"

#define MINION_HP 30		//문어 HP
#define MINION_MAX 9		//문어 수

enum octoState
{
	octo_DOWN,
	octo_LEFT,
	octo_RIGHT,
	octo_UP
};

//문어 구조체 생성
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
};

class octopus : public gameNode
{
private:
	tagOctopus _octopus[MINION_MAX];		//문어 구조체 선언

	image* _red;
	image* _blue;
	image* _yellow;



public:
	HRESULT init();
	void release();
	void update();
	void render();

	minion() {}
	~minion() {}
};