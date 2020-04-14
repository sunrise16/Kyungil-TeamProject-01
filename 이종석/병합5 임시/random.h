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
	// 0 ~ num 까지의 랜덤값 (정수)
	int Range(int num);

	// min ~ max 까지의 랜덤값 (정수)
	int Range(int min, int max);

	// 0 ~ num 까지의 랜덤값 (실수)
	float Range(float num);

	// min ~ max 까지의 랜덤값 (실수)
	float Range(float min, float max);

	// 생성자, 소멸자
	random() {}
	~random() {}
};

