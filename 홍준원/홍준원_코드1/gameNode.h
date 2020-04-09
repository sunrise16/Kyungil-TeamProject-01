#pragma once
#include "image.h"

// 백버퍼 이미지를 이미지 매니저에 담아 두기
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

// gameNode 클래스
class gameNode
{
private:
	// 시스템 관련
	HDC _hdc;			// DC 핸들

public:
	// 초기화 처리
	virtual HRESULT init();

	// 해제 처리
	virtual void release();

	// 계산식 처리
	virtual void update();

	// 화면 출력 처리
	virtual void render();

	// 백버퍼 이미지 얻기
	image* getBackBuffer() { return _backBuffer; }

	// 화면 HDC 얻기
	HDC getHDC() { return _hdc; }

	// 메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	// 메인 프로시저
	LRESULT CALLBACK MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// 생성자, 소멸자
	gameNode() {}
	virtual ~gameNode() {}
};

