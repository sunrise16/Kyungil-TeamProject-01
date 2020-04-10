#pragma once
#include "gameNode.h"
#include "inventory.h"

// Ŭ���� ���� ���� (��ȣ ������)
class octopus;
class mushroom;

// �÷��̾� ���� ���� ���Ź�
enum PLAYER_STATE
{
	PLAYER_STATE_IDLE = 0,			// �⺻ ���ĵ�
	PLAYER_STATE_LEFT = 1,			// ���� �̵�
	PLAYER_STATE_RIGHT = 2,			// ������ �̵�
	PLAYER_STATE_UP = 3,			// ���� �̵�
	PLAYER_STATE_DOWN = 4,			// �Ʒ��� �̵�
	PLAYER_STATE_LEFTATK = 5,		// ���� ����
	PLAYER_STATE_RIGHTATK = 6,		// ������ ����
	PLAYER_STATE_UPATK = 7,			// ���� ����
	PLAYER_STATE_DOWNATK = 8,		// �Ʒ��� ����
	PLAYER_STATE_GETATK = 9,		// ���Ϳ��� �ǰ�
	PLAYER_STATE_DEAD = 10			// ���
};

// player Ŭ����
class player : public gameNode
{
private:
	// �ּҰ� ����
	octopus* _octopusAdress;		// octopus Ŭ���� �ּҰ�
	mushroom* _mushroomAdress;		// mushroom Ŭ���� �ּҰ�

private:
	// �̹��� ����
	image* _playerImage;			// �÷��̾� �⺻ ���ĵ� ����
	image* _playerLeft;				// �÷��̾� �������� �̵�
	image* _playerRight;			// �÷��̾� ���������� �̵�
	image* _playerUp;				// �÷��̾� �������� �̵�
	image* _playerDown;				// �÷��̾� �Ʒ������� �̵�
	image* _playerLeftAtk;			// �÷��̾� �������� ����
	image* _playerRightAtk;			// �÷��̾� ���������� ����
	image* _playerUpAtk;			// �÷��̾� �������� ����
	image* _playerDownAtk;			// �÷��̾� �Ʒ������� ����
	image* _playerGetAtk;			// �÷��̾� ���� ����
	image* _playerHP;				// �÷��̾� ü��

	// ��ü ����
	inventory* _inventory;			// inventory Ŭ���� ����
	POINT playerCenter;				// �÷��̾� ���� ��ǥ
	RECT playerRc;					// �÷��̾� RECT
	RECT playerGetAtkLeftRc;		// �÷��̾� �ǰ� ���� RECT (����)
	RECT playerGetAtkRightRc;		// �÷��̾� �ǰ� ���� RECT (������)
	RECT playerGetAtkTopRc;			// �÷��̾� �ǰ� ���� RECT (����)
	RECT playerGetAtkBottomRc;		// �÷��̾� �ǰ� ���� RECT (�Ʒ���)
	RECT empty;						// IntersectRect�� RECT

	// ���� ����
	PLAYER_STATE playerState;		// �÷��̾� ���� ����
	int hpCount;					// �÷��̾� HP (4���� �����Ͽ� 0�� �Ǹ� ���)
	int count;						// ������ ���� ī��Ʈ
	int index;						// ������ ���� �ε���
	// �̵� ���� ��ȯ
	bool playerLeft;				// ���� �̵�
	bool playerRight;				// ������ �̵�
	bool playerUp;					// ���� �̵�
	bool playerDown;				// �Ʒ��� �̵�
	// ���� ���� ��ȯ
	bool playerLeftAtk;				// ���� ����
	bool playerRightAtk;			// ������ ����
	bool playerUpAtk;				// ���� ����
	bool playerDownAtk;				// �Ʒ��� ����
	// �ǰ� ����
	bool playerGetAtkLeft;			// ���� �ǰ�
	bool playerGetAtkRight;			// ������ �ǰ�
	bool playerGetAtkTop;			// ���� �ǰ�
	bool playerGetAtkBottom;		// �Ʒ��� �ǰ�
	bool playerGetAtk;				// �÷��̾� �ǰ� ����
	
public:
	// GET, SET �Լ�
	// �ּҰ� �ޱ�
	void setOctopusAdress(octopus* octopusAdress) { _octopusAdress = octopusAdress; }
	void setMushroomAdress(mushroom* mushroomAdress) { _mushroomAdress = mushroomAdress; }

	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// �ִϸ��̼� ó��
	void animation();

	// ������, �Ҹ���
	player() {}
	~player() {}
};