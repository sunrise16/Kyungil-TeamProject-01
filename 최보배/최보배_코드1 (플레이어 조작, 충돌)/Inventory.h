#pragma once
#include "gameNode.h"


class Inventory : public gameNode
{
private:

	image* _invenImage;
	image* _invenMenu;
	image* _invenItemselect;

	RECT _item[12];

	image* _sword;

	bool _invenopen;

	int selectNum;

	char str[20];

	int openCount;
	

public:

	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	Inventory() {}
	~Inventory() {}
};

