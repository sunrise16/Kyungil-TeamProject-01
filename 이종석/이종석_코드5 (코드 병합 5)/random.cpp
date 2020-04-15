#include "stdafx.h"
#include "random.h"

// 초기화 (init)
HRESULT random::init()
{
	// 랜덤 시드 초기화
	srand(GetTickCount());

	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void random::release()
{
}

// 랜덤값 설정 함수
// 0 ~ num 범위에서의 랜덤값 설정 (int)
int random::Range(int num)
{
	return rand() % num;
}

// min ~ max 범위에서의 랜덤값 설정 (int)
int random::Range(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

// 0.0f ~ num 범위에서의 랜덤값 설정 (float)
float random::Range(float num)
{
	return ((float)rand() / (float)RAND_MAX) * num;
}

// min ~ max 범위에서의 랜덤값 설정 (float)
float random::Range(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX);
	return (rnd * (max - min)) + min;
}