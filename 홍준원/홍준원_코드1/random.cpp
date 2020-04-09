#include "stdafx.h"
#include "random.h"

// �ʱ�ȭ (init)
HRESULT random::init()
{
	// ���� �õ� �ʱ�ȭ
	srand(GetTickCount());

	return S_OK;
}

// ���� (release)
void random::release()
{
}

// ������ ���� �Լ�
// 0 ~ num ���������� ������ ���� (int)
int random::Range(int num)
{
	return rand() % num;
}
// min ~ max ���������� ������ ���� (int)
int random::Range(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
// 0.0f ~ num ���������� ������ ���� (float)
float random::Range(float num)
{
	return ((float)rand() / (float)RAND_MAX) * num;
}
// min ~ max ���������� ������ ���� (float)
float random::Range(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX);
	return (rnd * (max - min)) + min;
}