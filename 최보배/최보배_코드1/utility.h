#pragma once

// PI ����
#define PI 3.1415926535f
#define PI2 (PI * 2)

// �̹��� ȸ�� �� ����� ��
#define PI_2 (PI / 2)		// 90��
#define PI_4 (PI / 4)		// 45��
#define PI_8 (PI / 8)		// 22.5��

// MY_UTIL ���ӽ����̽�
namespace MY_UTIL
{
	// �� �� ������ �Ÿ��� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);

	// �� �� ������ ������ ���ϴ� �Լ� (����ź)
	float getAngle(float startX, float startY, float endX, float endY);

	// �� ��ũ��
	void mapOutput(HDC hDest, int mapSize, HDC memDC);
};

