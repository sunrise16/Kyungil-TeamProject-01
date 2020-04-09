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

	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	Inventory() {}
	~Inventory() {}
};

