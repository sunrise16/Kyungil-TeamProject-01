#pragma once
#include "gameNode.h"
#include "Inventory.h"

enum STATE
{
	IDLE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFTATK,
	RIGHTATK,
	UPATK,
	FRONTATK,
	GETATK,
	DEAD
};

class player : public gameNode
{
private:

	Inventory* _inventory;//�κ��丮 Ŭ���� �ҷ�����
	
	POINT _playercenter;//Ȥ�� ���� ��ǥ ����ϴ�
	RECT _playerRc;//�÷��̾� ��Ʈ

	

	image* _playerImage;//�÷��̾� ���̵� ����
	image* _playerLeft;//�÷��̾� �������� �̵�
	image* _playerRight;//�÷��̾� ���������� �̵�
	image* _playerUp;//�÷��̾� �������� �̵�
	image* _playerDown;//�÷��̾� �Ʒ������� �̵�
	image* _playerLeftatk;//�÷��̾� �������� ����
	image* _playerRightatk;//�÷��̾� ���������� ����
	image* _playerUpatk;//�÷��̾� �������� ����
	image* _playerFrontatk;//�÷��̾� �Ʒ������� ����
	image* _playerGetatk;//���� ����, ����


	image* _playerHp;

	int _hpCount;//4���� �����Ͽ� 0�̵Ǹ� ���


	RECT _getAtkleftRc;//�ǰ����� ��Ʈ
	RECT _getAtkrightRc;
	RECT _getAtktopRc;
	RECT _getAtkbottomRc;
	
	RECT empty;//���ͼ�Ʈ��Ʈ��

	STATE _state;//����


	bool _left;//�̵� ���� ��ȯ
	bool _right;
	bool _up;
	bool _down;


	bool _leftatk;//���� ���� ��ȯ
	bool _rightatk;
	bool _upatk;
	bool _frontatk;


	bool _getatkleft;//�ǰ����� �Һ���
	bool _getatkright;
	bool _getatktop;
	bool _getatkbottom;

	bool _getatk;

	int _count;//�����ӷ����� �� ��Ʈ��
	int _index;
	
public:

	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	void animation();



	player() {}
	~player() {}
};

