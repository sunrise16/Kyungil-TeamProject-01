#pragma once
#include "singletonBase.h"

// playerData Ŭ����
class playerData : public singletonBase <playerData>
{
private:
	// ���� ����
	int _hp;				// �÷��̾��� ü��
	float _x;				// �÷��̾��� X��ǥ
	float _y;				// �÷��̾��� Y��ǥ

public:
	// GET, SET �Լ�
	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ������, �Ҹ���
	playerData() {}
	~playerData() {}
};