#include "stdafx.h"
#include "loading.h"

// 초기화 (init) - loadItem 클래스
HRESULT loadItem::init(string strKey, int width, int height)
{
	// 로딩 종류 초기화
	_kind = LOAD_KIND_IMAGE_0;

	// 이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	// 초기화 종료
	return S_OK;
}
HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// 로딩 종류 초기화
	_kind = LOAD_KIND_IMAGE_1;
	
	// 이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	// 로딩 종류 초기화
	_kind = LOAD_KIND_IMAGE_2;

	// 이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// 로딩 종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	// 이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// 로딩 종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	// 이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

// 초기화 (init) - loading 클래스
HRESULT loading::init()
{
	// 로딩 화면 백그라운드 이미지 초기화
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "LoadingImage/bgLoadingScene.bmp", WINSIZEX, WINSIZEY);

	// 로딩바 이미지 초기화
	IMAGEMANAGER->addImage("loadingBarFront", "LoadingImage/loadingBarFront.bmp", 600, 20);
	IMAGEMANAGER->addImage("loadingBarBack", "LoadingImage/loadingBarBack.bmp", 600, 20);

	// 로딩바 클래스 초기화
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack");
	
	// 로딩바 위치 초기화
	_loadingBar->setPos(100, 500);

	// 현재 게이지 초기화
	_currentGauge = 0;

	return S_OK;
}

// 해제 (release)
void loading::release()
{
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

// 업데이트 (update)
void loading::update()
{
	_loadingBar->update();
}

// 렌더 (render)
void loading::render()
{
	// 백그라운드 렌더
	_background->render(getMemDC());

	// 로딩바 렌더
	_loadingBar->render();
}

// 이미지 로딩
void loading::loadImage(string strKey, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}
void loading::loadImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}
void loading::loadImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}
void loading::loadFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}
void loading::loadFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

// 이미지 로딩 완료 체크
bool loading::loadingDone()
{
	// 로딩이 완료되었을 경우
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];
	switch (item->getLoadKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		}
		break;
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.isTrans, img.transColor);
		}
		break;
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.isTrans, img.transColor);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
		}
		break;
		
		// 곧 사운드 배우고 난후 직접 해보자!!
		case LOAD_KIND_SOUND:
		{
		}
		break;
	}

	// 현재 게이지 증가
	_currentGauge++;

	// 로딩바 이미지 변경
	_loadingBar->setGauge(_vLoadItem.size(), _currentGauge);

	return FALSE;
}
