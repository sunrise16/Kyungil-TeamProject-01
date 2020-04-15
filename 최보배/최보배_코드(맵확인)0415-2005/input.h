#pragma once
#include "singletonBase.h"
#define KEYMAX 256

// input Ŭ����
class input : public singletonBase <input>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// Ű �Է� �Լ�
	// Ű�� ��� ���� �ִ��� üũ
	bool getKey(int key);

	// Ű�� �ѹ��� ���ȴ��� üũ
	bool getKeyDown(int key);

	// Ű�� ���ȴ� �������� üũ
	bool getKeyUp(int key);

	// ��� Ű���� üũ
	bool getToggleKey(int key);

	// ������, �Ҹ���
	input() {}
	~input() {}
};