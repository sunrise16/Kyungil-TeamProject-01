#pragma once
#include "singletonBase.h"
#include "image.h"

// imageManager Ŭ����
class imageManager : public singletonBase <imageManager>
{
private:
	// �̹��� ����
	typedef map<string, image*> mapImageList;				// ������ ���� �̹��� ���
	typedef map<string, image*>::iterator mapImageIter;		// ������ ���� �̹��� ����� �ݺ���

private:
	// map<string, image*> _mImageList;
	mapImageList _mImageList;								// ���� �̹��� Ŭ������ ���� STL ��

public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// �� ��Ʈ�� �ʱ�ȭ
	image* addImage(string strKey, int width, int height);

	// �̹��� ���Ϸ� �ʱ�ȭ
	image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	// ������ �̹��� ���Ϸ� �ʱ�ȭ
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));

	// �̹��� Ű������ ã��
	image* findImage(string strKey);

	// �̹��� Ű������ ����
	BOOL deleteImage(string strKey);

	// �̹��� ��ü ����
	BOOL deleteAll();

	// ��� ����
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	
	// ���� ����
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// ������ ����
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// ���� ����
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// ������ ����
	void scaleRender(string strKey, HDC hdc, int destX, int destY, float scale = 1.0f);
	void scaleFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);

	// ������Ʈ ����
	void rotateRender(string strKey, HDC hdc, float destX, float destY, float angle);
	void rotateFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle);

	// ������, �Ҹ���
	imageManager() {}
	~imageManager() {}
};

