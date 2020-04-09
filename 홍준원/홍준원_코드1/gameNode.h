#pragma once
#include "image.h"

// ����� �̹����� �̹��� �Ŵ����� ��� �α�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

// gameNode Ŭ����
class gameNode
{
private:
	// �ý��� ����
	HDC _hdc;			// DC �ڵ�

public:
	// �ʱ�ȭ ó��
	virtual HRESULT init();

	// ���� ó��
	virtual void release();

	// ���� ó��
	virtual void update();

	// ȭ�� ��� ó��
	virtual void render();

	// ����� �̹��� ���
	image* getBackBuffer() { return _backBuffer; }

	// ȭ�� HDC ���
	HDC getHDC() { return _hdc; }

	// �޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	// ���� ���ν���
	LRESULT CALLBACK MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// ������, �Ҹ���
	gameNode() {}
	virtual ~gameNode() {}
};

