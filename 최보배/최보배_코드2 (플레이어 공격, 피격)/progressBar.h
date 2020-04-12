#pragma once
#include "gameNode.h"

// progressBar Ŭ����
class progressBar : public gameNode
{
private:
	// �̹��� ����
	image* _progressBarFront;		// ü�¹� �ո� �̹���
	image* _progressBarBack;		// ü�¹� �޸� �̹���
	
	// ��ü ����
	RECT _rcProgress;				// ü�¹� RECT
	
	// ���� ����
	float _x, _y;					// ü�¹� ��ġ ��ǥ
	float _width;					// ü�¹� ���� ����
	float _height;					// ü�¹� ���� ����

public:
	// �ʱ�ȭ ó��
	HRESULT init(const char* frontImg, const char* backImg);

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// ü�¹� ��ġ ����
	void setPos(float x, float y) { _x = x; _y = y; }

	// ü�¹� ������ ����
	float getGauge() { return _width; }
	void setGauge(float maxHp, float currentHp);

	// ������, �Ҹ���
	progressBar() {}
	~progressBar() {}
};

