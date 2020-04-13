#pragma once
#include "stdafx.h"

// POINT �����
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

// �� �׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

// RECT �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

// RECT �߽���ǥ ����
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

// Rectangle �⺻ ����
inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

// Rectangle �Լ� �̿��Ͽ� �簢�� �׸���
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// Ellipse �⺻ ����
inline void Ellipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

// Ellipse �Լ� �̿��Ͽ� Ÿ�� �׸���
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// Ellipse �Լ� �̿��Ͽ� Ÿ�� �߽���ǥ�� �׸���
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

// Rectangle, Point �浹 ���� (�簢���� ���� �浹)
static bool collisionRectanglePointCheck(RECT rc, float pointX, float pointY)
{
	if ((rc.left <= pointX && pointX <= rc.right) && (rc.top <= pointY && pointY <= rc.bottom))
	{
		return TRUE;
	}

	return FALSE;
}

// Ellipse, Point �浹 ���� (���� ���� �浹)
static bool collisionEllipsePointCheck(RECT rc, float pointX, float pointY)
{
	float radius = (rc.right - rc.left) / 2;
	float rCenterX = rc.left + radius;
	float rCenterY = rc.top + radius;

	float deltaX = rCenterX - pointX;
	float deltaY = rCenterY - pointY;

	float length = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	if (length <= radius)
	{
		return TRUE;
	}

	return FALSE;
}

// Rectangle ������ �浹 ���� (�簢���� �簢���� �浹)
// �� ��� IntersectRect() �� ����� ��

// Ellipse ������ �浹 ���� (���� ���� �浹)
static bool collisionEllipseCheck(RECT rc, RECT rc2)
{
	float rc_Radius = (rc.right - rc.left) / 2;
	float rc2_Radius = (rc2.right - rc2.left) / 2;

	float rCenterX = (rc.left + (rc.right - rc.left) / 2) - (rc2.left + (rc2.right - rc2.left) / 2);
	float rCenterY = (rc.top + (rc.bottom - rc.top) / 2) - (rc2.top + (rc2.bottom - rc2.top) / 2);

	float length = pow((rc_Radius + rc2_Radius), 2);

	if (length >= (pow(rCenterX, 2) + pow(rCenterY, 2)))
	{
		return TRUE;
	}

	return FALSE;
}

// Ellipse, Rectangle �浹 ���� (���� �簢���� �浹)
static bool collisionEllipseRectangleCheck(RECT rc, RECT rc2)
{
	float radius = (rc.right - rc.left) / 2;
	float rCenterX = rc.left + radius;
	float rCenterY = rc.top + radius;

	if ((rc2.left <= rCenterX && rCenterX <= rc2.right) || (rc2.top <= rCenterY && rCenterY <= rc2.bottom))
	{
		RECT rc3 = { rc2.left - radius, rc2.top - radius, rc2.right + radius, rc2.bottom + radius };

		if ((rc3.left <= rCenterX && rCenterX <= rc3.right) && (rc3.top <= rCenterY && rCenterY <= rc3.bottom))
		{
			return TRUE;
		}
	}
	else
	{
		if (collisionEllipsePointCheck(rc, (float)rc2.left, (float)rc2.top) == TRUE)
		{
			return TRUE;
		}
		if (collisionEllipsePointCheck(rc, (float)rc2.left, (float)rc2.bottom) == TRUE)
		{
			return TRUE;
		}
		if (collisionEllipsePointCheck(rc, (float)rc2.right, (float)rc2.top) == TRUE)
		{
			return TRUE;
		}
		if (collisionEllipsePointCheck(rc, (float)rc2.right, (float)rc2.bottom) == TRUE)
		{
			return TRUE;
		}
	}

	return FALSE;
}

// FrameRect �Լ� �����ε� (����ִ� �簢�� �����)
inline void FrameRect(HDC hdc, RECT rc, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FrameRect(hdc, &rc, brush);
	DeleteObject(brush);
}

// TextOut �Լ�
inline void textOut(HDC hdc, int x, int y, const char* text, COLORREF color = RGB(255, 255, 0))
{
	SetTextColor(hdc, color);
	TextOut(hdc, x, y, text, strlen(text));
}