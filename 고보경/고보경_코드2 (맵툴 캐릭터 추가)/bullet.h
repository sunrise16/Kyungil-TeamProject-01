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

// bullet Ŭ����
class bullet : public gameNode
{
public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ������, �Ҹ���
	bullet() {}
	~bullet() {}
};

// ���� missile Ŭ����
class missile : public gameNode
{
private:
	// ��ü ����
	// �Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	
	// ���� ����
	float _range;		// �Ѿ� ��Ÿ�
	int _bulletMax;		// �Ѿ� �ִ밹��
	int frameX[30];		//
	int frameY[30];		//
	int _count;			//
	int _power;			//

public:
	// GET, SET �Լ�
	vector<tagBullet> getBullet() { return _vBullet; }
	int getPower() { return _power; }
	void setBullet(int num, bool fire);
	void setRC(int num);
	void setPower(int power) { _power = power; }

	// �Ѿ� �߻�
	void fire(float x, float y, float angle);

	// �Ѿ� �̵�
	void move();

	// �Ѿ� ����
	void eraseBullet(int num);
	
	// �ʱ�ȭ ó��
	HRESULT init(int bulletMax, float range);

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ������, �Ҹ���
	missile() {}
	~missile() {}
};

// ���� ���̾ Ŭ����
class missileB : public gameNode
{
private:
	// ��ü ����
	// �Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	// ���� ����
	float _range;		// �Ѿ� ��Ÿ�
	int _bulletMax;		// �Ѿ� �ִ밹��
	int frameX[30];		//
	int frameY[30];		//
	int _count;			//
	int _power;			//

public:
	// GET, SET �Լ�
	vector<tagBullet> getBullet() { return _vBullet; }
	int getPower() { return _power; }
	void setBullet(int num, bool fire);
	void setPower(int power) { _power = power; }

	// �Ѿ� �߻�
	void fire(float x, float y, float angle);

	// �Ѿ� �̵�
	void move();

	// �Ѿ� ����
	void eraseBullet(int num);

	// �ʱ�ȭ ó��
	HRESULT init(int bulletMax, float range);

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ������, �Ҹ���
	missileB() {}
	~missileB() {}
};


// ���� ����ź Ŭ����
//��ȣ���� �÷��̾� ����
class player;

class missileE : public gameNode
{
private:
	//�÷��̾� �ּҰ�
	player* _playerAdress;

private:
	// ��ü ����
	// �Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	// ���� ����
	float _range;		// �Ѿ� ��Ÿ�
	int _bulletMax;		// �Ѿ� �ִ밹��
	int frameX[30];		//
	int frameY[30];		//
	int _count;			//
	int _power;			//

public:
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }
	// GET, SET �Լ�
	vector<tagBullet> getBullet() { return _vBullet; }
	int getPower() { return _power; }
	void setBullet(int num, bool fire);
	void setPower(int power) { _power = power; }

	// �Ѿ� �߻�
	void fire(float x, float y, float angle);

	// ����ź ���� ���
	float getAngle(float startX, float startY, float endX, float endY);

	// �Ѿ� �̵�
	void move();

	// �Ѿ� ����
	void eraseBullet(int num);

	// �ʱ�ȭ ó��
	HRESULT init(int bulletMax, float range);

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ������, �Ҹ���
	missileE() {}
	~missileE() {}
};

// ���� ���� Ŭ����
class missileE2 : public gameNode
{
private:
	//�÷��̾� �ּҰ�
	player* _playerAdress;

private:
	// ��ü ����
	// �Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	// ���� ����
	float _range;		// �Ѿ� ��Ÿ�
	int _bulletMax;		// �Ѿ� �ִ밹��
	int frameX[30];		//
	int frameY[30];		//
	int _count;			//
	int _power;			//

public:
	void setPlayerAdress(player* playerAdress) { _playerAdress = playerAdress; }
	// GET, SET �Լ�
	vector<tagBullet> getBullet() { return _vBullet; }
	int getPower() { return _power; }
	void setBullet(int num, bool fire);
	void setPower(int power) { _power = power; }

	// �Ѿ� �߻�
	void fire(float x, float y, float angle);

	// �Ѿ� �̵�
	void move();

	// �Ѿ� ����
	void eraseBullet(int num);

	// �ʱ�ȭ ó��
	HRESULT init(int bulletMax, float range);

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ������, �Ҹ���
	missileE2() {}
	~missileE2() {}
};
