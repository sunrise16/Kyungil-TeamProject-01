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
	// 0 ~ num ������ ������ (����)
	int Range(int num);

	// min ~ max ������ ������ (����)
	int Range(int min, int max);

	// 0 ~ num ������ ������ (�Ǽ�)
	float Range(float num);

	// min ~ max ������ ������ (�Ǽ�)
	float Range(float min, float max);

	// ������, �Ҹ���
	random() {}
	~random() {}
};

