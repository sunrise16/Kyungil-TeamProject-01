#include "stdafx.h"
#include "progressBar.h"

// 초기화 (init)
HRESULT progressBar::init(const char * frontImg, const char * backImg)
{
	// 체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);

	// 체력바 위치 초기화
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();

	// 체력바 가로, 세로 길이 초기화
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();

	// 체력바 RECT 초기화
	_rcProgress = RectMake(_x, _y, _width, _height);

	return S_OK;
}

// 해제 (release)
void progressBar::release()
{
}

// 업데이트 (update)
void progressBar::update()
{
	// 프로그레스바 RECT 업데이트
	_rcProgress = RectMake(_x, _y, _width, _height);
}

// 렌더 (redner)
void progressBar::render()
{
	// 렌더링 되는 순서에 의해 렌더가 되므로 뒷면 이미지부터 렌더
	_progressBarBack->render(getMemDC(), _x, _y);

	// 앞에 보여지는 체력바 이미지
	_progressBarFront->render(getMemDC(), _x, _y, 0, 0, _width, _progressBarFront->getHeight());
}

// 체력바 게이지 세팅
void progressBar::setGauge(float currentHP, float maxHP)
{
	_width = (currentHP / maxHP) * _progressBarBack->getWidth();
}
