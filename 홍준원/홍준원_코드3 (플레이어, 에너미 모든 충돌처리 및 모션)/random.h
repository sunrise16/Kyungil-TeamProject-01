#pragma once
#include "singletonBase.h"

// random 클래스
class random : public singletonBase <random>
{
public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 랜덤값 설정 함수
	int Range(int num);
	int Range(int min, int max);
	float Range(float num);
	float Range(float min, float max);

	// 생성자, 소멸자
	random() {}
	~random() {}
};

