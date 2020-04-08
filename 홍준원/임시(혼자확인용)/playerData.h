#pragma once
#include "singletonBase.h"

// playerData 클래스
class playerData : public singletonBase <playerData>
{
private:
	// 변수 관련
	int _hp;				// 플레이어의 체력
	float _x;				// 플레이어의 X좌표
	float _y;				// 플레이어의 Y좌표

public:
	// GET, SET 함수
	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 생성자, 소멸자
	playerData() {}
	~playerData() {}
};