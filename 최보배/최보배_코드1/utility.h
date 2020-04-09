#pragma once

// PI 정의
#define PI 3.1415926535f
#define PI2 (PI * 2)

// 이미지 회전 시 사용할 값
#define PI_2 (PI / 2)		// 90도
#define PI_4 (PI / 4)		// 45도
#define PI_8 (PI / 8)		// 22.5도

// MY_UTIL 네임스페이스
namespace MY_UTIL
{
	// 두 점 사이의 거리를 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	// 두 점 사이의 각도를 구하는 함수 (조준탄)
	float getAngle(float startX, float startY, float endX, float endY);

	// 맵 스크롤
	void mapOutput(HDC hDest, int mapSize, HDC memDC);
};

