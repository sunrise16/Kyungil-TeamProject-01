#include "stdafx.h"
#include "imageManager.h"

// 초기화 (init)
HRESULT imageManager::init()
{
	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void imageManager::release()
{
	// 전부 삭제
	this->deleteAll();
}

// 이미지 추가
image* imageManager::addImage(string strKey, int width, int height)
{	
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당 이미지를 리턴
	if (img) return img;

	// 키값으로 찾은 해당 이미지가 없을 경우 새로 생성 후 초기화
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	/* STL 맵 */
	// 키, 값을 잊지 말 것
	// 첫번째 = 키 -> first
	// 두번째 = 밸류 ->second
	// 데이터를 추가할 때 반드시 키, 밸류 쌍으로 넣어야 함
	// pair, make_pair를 사용해서 추가
	// _mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당 이미지를 리턴
	if (img) return img;

	// 키값으로 찾은 해당 이미지가 없을 경우 새로 생성 후 초기화
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	// 맵 리스트에 이미지 클래스 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당 이미지를 리턴
	if (img) return img;

	// 키값으로 찾은 해당 이미지가 없을 경우 새로 생성 후 초기화
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	// 맵 리스트에 이미지 클래스 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당 이미지를 리턴
	if (img) return img;

	// 키값으로 찾은 해당 이미지가 없을 경우 새로 생성 후 초기화
	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	// 맵 리스트에 이미지 클래스 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당 이미지를 리턴
	if (img) return img;

	// 키값으로 찾은 해당 이미지가 없을 경우 새로 생성 후 초기화
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	// 맵 리스트에 이미지 클래스 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// 이미지 찾기
image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	// 검색한 키를 찾았을 경우 이미지 클래스 리턴
	if (key != _mImageList.end())
	{
		// key->first => 해당 키
		return key->second; // 해당 데이터 = 값 (이미지 클래스)
	}

	// key가 end()까지 도달했다는 얘기는 키값으로 이미지를 찾지 못했다는 말이므로 NULL(nullptr)을 리턴
	return nullptr;
}

// 이미지 해제
BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	// 검색한 키를 찾았을 경우 
	if (key != _mImageList.end())
	{
		// 이미지 해제
		key->second->release();
		// 메모리 해제
		SAFE_DELETE(key->second);
		// 맵의 반복자 해제
		_mImageList.erase(key);

		return TRUE;
	}

	// key가 end()까지 도달했다는 얘기는 키값으로 이미지를 찾지 못했다는 말이므로 FALSE를 리턴
	return FALSE;
}

// 전체 해제
BOOL imageManager::deleteAll()
{
	// 맵 전체를 돌면서 하나씩 전부 삭제
	mapImageIter iter = _mImageList.begin();

	// 검색한 키를 찾았다면 
	// for (;;) => while(true)
	for(;iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	// 맵 전체를 삭제
	_mImageList.clear();

	return FALSE;
}

// 노멀 렌더
void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}
void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

// 알파 렌더
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);

}
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

// 프레임 렌더
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

// 루프 렌더
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}
void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

// 스케일 렌더
void imageManager::scaleRender(string strKey, HDC hdc, int destX, int destY, float scale)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->scaleRender(hdc, destX, destY, scale);
}
void imageManager::scaleFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->scaleFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, scale);
}

// 로테이트 렌더
void imageManager::rotateRender(string strKey, HDC hdc, float destX, float destY, float angle)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->rotateRender(hdc, destX, destY, angle);
}
void imageManager::rotateFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle)
{
	// 이미지를 찾아 이미지 클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->rotateFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, angle);
}