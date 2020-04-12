#pragma once
#include "gameNode.h"

// inventory 클래스
class inventory : public gameNode
{
private:
	// 이미지 관련
	image* _invenImage;				// 인벤토리 기본 이미지
	image* _invenMenu;				// 인벤토리 메뉴 이미지
	image* _invenItemselect;		// 인벤토리 선택 이미지
	image* _sword;					// 아이템 아이콘 이미지 (검)

	// 객체 관련
	RECT _item[12];					// 아이템 배열

	// 변수 관련
	bool _invenopen;				// 인벤토리 오픈
	int selectNum;					// 입력받을 숫자
	char str[20];					// 텍스트
	int openCount;					// 오픈 카운트

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	inventory() {}
	~inventory() {}
};

