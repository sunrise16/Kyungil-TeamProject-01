#include "stdafx.h"
#include "progressBar.h"

// �ʱ�ȭ (init)
HRESULT progressBar::init(const char * frontImg, const char * backImg)
{
	// ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);

	// ü�¹� ��ġ �ʱ�ȭ
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();

	// ü�¹� ����, ���� ���� �ʱ�ȭ
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();

	// ü�¹� RECT �ʱ�ȭ
	_rcProgress = RectMake(_x, _y, _width, _height);

	return S_OK;
}

// ���� (release)
void progressBar::release()
{
}

// ������Ʈ (update)
void progressBar::update()
{
	// ���α׷����� RECT ������Ʈ
	_rcProgress = RectMake(_x, _y, _width, _height);
}

// ���� (redner)
void progressBar::render()
{
	// ������ �Ǵ� ������ ���� ������ �ǹǷ� �޸� �̹������� ����
	_progressBarBack->render(getMemDC(), _x, _y);

	// �տ� �������� ü�¹� �̹���
	_progressBarFront->render(getMemDC(), _x, _y, 0, 0, _width, _progressBarFront->getHeight());
}

// ü�¹� ������ ����
void progressBar::setGauge(float currentHP, float maxHP)
{
	_width = (currentHP / maxHP) * _progressBarBack->getWidth();
}
