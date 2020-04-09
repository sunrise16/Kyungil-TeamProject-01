#pragma once
#include "gameNode.h"

// progressBar 클래스
class progressBar : public gameNode
{
private:
	// 이미지 관련
	image* _progressBarFront;		// 체력바 앞면 이미지
	image* _progressBarBack;		// 체력바 뒷면 이미지
	
	// 객체 관련
	RECT _rcProgress;				// 체력바 RECT
	
	// 변수 관련
	float _x, _y;					// 체력바 위치 좌표
	float _width;					// 체력바 가로 길이
	float _height;					// 체력바 세로 길이

public:
	// 초기화 처리
	HRESULT init(const char* frontImg, const char* backImg);

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 체력바 위치 세팅
	void setPos(float x, float y) { _x = x; _y = y; }

	// 체력바 게이지 세팅
	float getGauge() { return _width; }
	void setGauge(float maxHp, float currentHp);

	// 생성자, 소멸자
	progressBar() {}
	~progressBar() {}
};

