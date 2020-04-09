#include "stdafx.h"
#include "utility.h"

// 두 점 사이의 거리를 구하는 함수
float MY_UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

// 두 점 사이의 각도를 구하는 함수 (조준탄)
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

// 맵 스크롤
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