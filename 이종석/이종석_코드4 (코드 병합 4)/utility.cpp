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