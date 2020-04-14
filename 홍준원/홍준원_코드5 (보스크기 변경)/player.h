#pragma once
#include "gameNode.h"
#include "inventory.h"

// Ŭ���� ���� ���� (��ȣ ������)
class octopus;
class mushroom;
class boss;

// �÷��̾� ���� ���� ���Ź�
enum PLAYER_STATE
{
	PLAYER_STATE_LEFTSTANDING = 0,		// ���� ���ĵ�
	PLAYER_STATE_RIGHTSTANDING = 1,		// ������ ���ĵ�
	PLAYER_STATE_UPSTANDING = 2,		// ���� ���ĵ�
	PLAYER_STATE_DOWNSTANDING = 3,		// �Ʒ��� ���ĵ�
	PLAYER_STATE_LEFT = 4,				// ���� �̵�
	PLAYER_STATE_RIGHT = 5,				// ������ �̵�
	PLAYER_STATE_UP = 6,				// ���� �̵�
	PLAYER_STATE_DOWN = 7,				// �Ʒ��� �̵�
	PLAYER_STATE_LEFTATK = 8,			// ���� ����
	PLAYER_STATE_RIGHTATK = 9,			// ������ ����
	PLAYER_STATE_UPATK = 10,			// ���� ����
	PLAYER_STATE_DOWNATK = 11,			// �Ʒ��� ����
	PLAYER_STATE_GETATK = 12,			// ���Ϳ��� �ǰ�
	PLAYER_STATE_DEAD = 13,				// �÷��̾� ���
};

// player Ŭ����
class player : public gameNode
{
private:
	// �ּҰ� ����
	octopus* _octopusAdress;			// octopus Ŭ���� �ּҰ�
	mushroom* _mushroomAdress;			// mushroom Ŭ���� �ּҰ�
	boss* _bossAdress;					// boss Ŭ���� �ּҰ�

	// �̹��� ����
	image* _playerLeftStanding;			// �÷��̾� �⺻ ���ĵ� ���� (����)
	image* _playerRightStanding;		// �÷��̾� �⺻ ���ĵ� ���� (������)
	image* _playerUpStanding;			// �÷��̾� �⺻ ���ĵ� ���� (����)
	image* _playerDownStanding;			// �÷��̾� �⺻ ���ĵ� ���� (�Ʒ���)
	image* _playerLeft;					// �÷��̾� �������� �̵�
	image* _playerRight;				// �÷��̾� ���������� �̵�
	image* _playerUp;					// �÷��̾� �������� �̵�
	image* _playerDown;					// �÷��̾� �Ʒ������� �̵�
	image* _playerLeftAtk;				// �÷��̾� �������� ����
	image* _playerRightAtk;				// �÷��̾� ���������� ����
	image* _playerUpAtk;				// �÷��̾� �������� ����
	image* _playerDownAtk;				// �÷��̾� �Ʒ������� ����
	image* _playerGetAtk;				// �÷��̾� ���� ����
	image* _playerHP;					// �÷��̾� ü��

	// ��ü ����
	inventory* _inventory;				// inventory Ŭ���� ����
	POINT playerCenter;					// �÷��̾� ���� ��ǥ
	RECT playerRc;						// �÷��̾� RECT
	RECT playerGetAtkLeftRc;			// �÷��̾� �ǰ� ���� RECT (����)
	RECT playerGetAtkRightRc;			// �÷��̾� �ǰ� ���� RECT (������)
	RECT playerGetAtkTopRc;				// �÷��̾� �ǰ� ���� RECT (����)
	RECT playerGetAtkBottomRc;			// �÷��̾� �ǰ� ���� RECT (�Ʒ���)
	RECT empty;							// IntersectRect�� RECT
	RECT playerAttack;

	// ���� ����
	PLAYER_STATE playerState;			// �÷��̾� ���� ����
	int hpCount;						// �÷��̾� HP (4���� �����Ͽ� 0�� �Ǹ� ���)
	int count;							// ������ ���� ī��Ʈ
	int index;							// ������ ���� �ε���
	// ���� ��ȯ
	bool playerLeftStanding;			// ���� ���ĵ�
	bool playerRightStanding;			// ������ ���ĵ�
	bool playerUpStanding;				// ���� ���ĵ�
	bool playerDownStanding;			// �Ʒ��� ���ĵ�
	// �̵� ���� ��ȯ
	bool playerLeft;					// ���� �̵�
	bool playerRight;					// ������ �̵�
	bool playerUp;						// ���� �̵�
	bool playerDown;					// �Ʒ��� �̵�
	// ���� ���� ��ȯ
	bool playerLeftAtk;					// ���� ����
	bool playerRightAtk;				// ������ ����
	bool playerUpAtk;					// ���� ����
	bool playerDownAtk;					// �Ʒ��� ����
	// �ǰ� ����
	bool playerGetAtkLeft;				// ���� �ǰ�
	bool playerGetAtkRight;				// ������ �ǰ�
	bool playerGetAtkTop;				// ���� �ǰ�
	bool playerGetAtkBottom;			// �Ʒ��� �ǰ�
	bool playerGetAtk;					// �÷��̾� �ǰ� ����
	int playerGetAtkDelay;				// �÷��̾� �ǰ� ������
	bool playerGetAtkDelayBool;			// �÷��̾� �ǰ� ������ ����
	
public:
	// GET, SET �Լ�
	RECT getAttack() { return playerAttack; }
	RECT getplayerleftatkRc() { return playerGetAtkLeftRc; }
	void setplayerleftatkRc(RECT _playerGetAtkLeftRc) { playerGetAtkLeftRc = _playerGetAtkLeftRc; }
	RECT getplayerrightatkRc() { return playerGetAtkRightRc; }
	void setplayerrightatkRc(RECT _playerGetAtkRightRc) { playerGetAtkRightRc = _playerGetAtkRightRc; }
	RECT getplayertopatkRc() { return playerGetAtkTopRc; }
	void setplayertopatkRc(RECT _playerGetAtkTopRc) { playerGetAtkTopRc = _playerGetAtkTopRc; }
	RECT getplayerbottomatkRc() { return playerGetAtkBottomRc; }
	void setplayerbottomatkRc(RECT _playerGetAtkBottomRc) { playerGetAtkBottomRc = _playerGetAtkBottomRc; }
	RECT getPlayerRc() { return playerRc; }
	void setPlayerRc(RECT _playerRc) { playerRc = _playerRc; }
	POINT getPlayercenter() { return playerCenter; }
	void setPlayercenter(POINT playercenter) { playerCenter = playercenter; }

	void setPlayerleft(bool _playerLeft) { playerLeft = _playerLeft; }
	void setPlayerright(bool _playerRight) { playerRight = _playerRight; }
	void setPlayerup(bool _playerUp) { playerUp = _playerUp; }
	void setPlayerdown(bool _playerdown) { playerDown = _playerDown; }
	// �ּҰ� �ޱ�
	void setOctopusAdress(octopus* octopusAdress) { _octopusAdress = octopusAdress; }
	void setMushroomAdress(mushroom* mushroomAdress) { _mushroomAdress = mushroomAdress; }
	void setBossAdress(boss* bossAdress) { _bossAdress = bossAdress; }

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