#pragma once
#include "gameNode.h"

#define CAMSIZEX 1600
#define CAMSIZEY 900

// camera 클래스
class camera : public gameNode
{
private:
	// 이미지 관련
	image* _img;		// 백그라운드 이미지

	// 객체 관련
	RECT _rcCam;		// 카메라 RECT

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 생성자, 소멸자
	camera() {}
	~camera() {}
};

