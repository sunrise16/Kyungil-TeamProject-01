#pragma once
#include "gameNode.h"

// inventory Ŭ����
class inventory : public gameNode
{
private:
	// �̹��� ����
	image* _invenImage;				// �κ��丮 �⺻ �̹���
	image* _invenMenu;				// �κ��丮 �޴� �̹���
	image* _invenItemselect;		// �κ��丮 ���� �̹���
	image* _sword;					// ������ ������ �̹��� (��)

	// ��ü ����
	RECT _item[12];					// ������ �迭

	// ���� ����
	bool _invenopen;				// �κ��丮 ����
	int selectNum;					// �Է¹��� ����
	char str[20];					// �ؽ�Ʈ
	int openCount;					// ���� ī��Ʈ

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
	inventory() {}
	~inventory() {}
};