#pragma once
#include "singletonBase.h"

// random Ŭ����
class random : public singletonBase <random>
{
public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ������ ���� �Լ�
	int Range(int num);
	int Range(int min, int max);
	float Range(float num);
	float Range(float min, float max);

	// ������, �Ҹ���
	random() {}
	~random() {}
};

