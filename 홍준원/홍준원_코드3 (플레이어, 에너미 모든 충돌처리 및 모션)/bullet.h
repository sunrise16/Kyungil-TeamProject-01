#pragma once
#include "gameNode.h"

//�Ѿ� ����ü
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float speed2;
	float angle;
	float gravity;
	float radius;
	bool fire;
};

//=============================================================
//	## bullet ## (�����Ѿ� - ������� ������ ��)
//=============================================================
class bullet : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	bullet() {}
	~bullet() {}
};


//=============================================================
//	## missile ## (missile[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
class missile : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//�÷��̾� ����
private:
	float _range;		//�Ѿ� ��Ÿ�
	int _bulletMax;		//�Ѿ� �ִ밹��
	int frameX[30];
	int frameY[30];
	int _count;
	int _power;

public:
	// GET, SET �Լ�
	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);
	int getPower() { return _power; }
	void setPower(int power) { _power = power; }

	//�Ѿ˹߻�
	void fire(float x, float y, float angle);
	//�Ѿ˹���
	void move();
	// �Ѿ� ����
	void eraseBullet(int num);

	//�÷��̾� ��




	missile() {}
	~missile() {}

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
};