#include "stdafx.h"
#include "utility.h"

// �� �� ������ �Ÿ��� ���ϴ� �Լ�
float MY_UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

// �� �� ������ ������ ���ϴ� �Լ� (����ź)
float MY_UTIL::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	float distance = sqrtf(x * x + y * y);
	float angle = acosf(x / distance);

	if (endY > startY)
	{
		angle = PI2 - angle;
	}

	return angle;
}

// �� ��ũ��
void mapOutput(HDC hDest, int mapSize, HDC memDC)
{
	static int nY = mapSize - WINSIZEY;

	if (nY < 0)
	{
		BitBlt(hDest, 0, -nY, WINSIZEX, WINSIZEY + nY, memDC, 0, 0, SRCCOPY);
		BitBlt(hDest, 0, 0, WINSIZEX, -nY, memDC, 0, mapSize + nY, SRCCOPY);
	}
	else
	{
		BitBlt(hDest, 0, 0, WINSIZEX, WINSIZEY, memDC, 0, nY, SRCCOPY);
	}

	nY -= 5;

	if (nY + WINSIZEY <= 0)
	{
		nY += mapSize;
	}
}