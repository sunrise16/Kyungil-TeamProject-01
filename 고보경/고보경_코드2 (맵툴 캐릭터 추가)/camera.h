#pragma once
#include "gameNode.h"

#define CAMSIZEX 1600
#define CAMSIZEY 900

// camera Ŭ����
class camera : public gameNode
{
private:
	// �̹��� ����
	image* _img;		// ��׶��� �̹���

	// ��ü ����
	RECT _rcCam;		// ī�޶� RECT

public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ������, �Ҹ���
	camera() {}
	~camera() {}
};

