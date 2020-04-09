#pragma once
#include "singletonBase.h"
#define KEYMAX 256

// input 클래스
class input : public singletonBase <input>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 키 입력 함수
	// 키가 계속 눌려 있는지 체크
	bool getKey(int key);
	// 키가 한번만 눌렸는지 체크
	bool getKeyDown(int key);
	// 키가 눌렸다 떼졌는지 체크
	bool getKeyUp(int key);
	// 토글키인지 체크
	bool getToggleKey(int key);

	// 생성자, 소멸자
	input() {}
	~input() {}
};

