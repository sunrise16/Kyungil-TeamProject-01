#include "stdafx.h"
#include "imageManager.h"

// �ʱ�ȭ (init)
HRESULT imageManager::init()
{
	// �ʱ�ȭ ����
	return S_OK;
}

// ���� (release)
void imageManager::release()
{
	// ���� ����
	this->deleteAll();
}

// �̹��� �߰�
image* imageManager::addImage(string strKey, int width, int height)
{	
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش� �̹����� ����
	if (img) return img;

	// Ű������ ã�� �ش� �̹����� ���� ��� ���� ���� �� �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	/* STL �� */
	// Ű, ���� ���� �� ��
	// ù��° = Ű -> first
	// �ι�° = ��� ->second
	// �����͸� �߰��� �� �ݵ�� Ű, ��� ������ �־�� ��
	// pair, make_pair�� ����ؼ� �߰�
	// _mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش� �̹����� ����
	if (img) return img;

	// Ű������ ã�� �ش� �̹����� ���� ��� ���� ���� �� �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	// �� ����Ʈ�� �̹��� Ŭ���� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش� �̹����� ����
	if (img) return img;

	// Ű������ ã�� �ش� �̹����� ���� ��� ���� ���� �� �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	// �� ����Ʈ�� �̹��� Ŭ���� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش� �̹����� ����
	if (img) return img;

	// Ű������ ã�� �ش� �̹����� ���� ��� ���� ���� �� �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	// �� ����Ʈ�� �̹��� Ŭ���� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ش� �̹����� ����
	if (img) return img;

	// Ű������ ã�� �ش� �̹����� ���� ��� ���� ���� �� �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	// �� ����Ʈ�� �̹��� Ŭ���� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// �̹��� ã��
image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	// �˻��� Ű�� ã���� ��� �̹��� Ŭ���� ����
	if (key != _mImageList.end())
	{
		// key->first => �ش� Ű
		return key->second; // �ش� ������ = �� (�̹��� Ŭ����)
	}

	// key�� end()���� �����ߴٴ� ���� Ű������ �̹����� ã�� ���ߴٴ� ���̹Ƿ� NULL(nullptr)�� ����
	return nullptr;
}

// �̹��� ����
BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	// �˻��� Ű�� ã���� ��� 
	if (key != _mImageList.end())
	{
		// �̹��� ����
		key->second->release();
		// �޸� ����
		SAFE_DELETE(key->second);
		// ���� �ݺ��� ����
		_mImageList.erase(key);

		return TRUE;
	}

	// key�� end()���� �����ߴٴ� ���� Ű������ �̹����� ã�� ���ߴٴ� ���̹Ƿ� FALSE�� ����
	return FALSE;
}

// ��ü ����
BOOL imageManager::deleteAll()
{
	// �� ��ü�� ���鼭 �ϳ��� ���� ����
	mapImageIter iter = _mImageList.begin();

	// �˻��� Ű�� ã�Ҵٸ� 
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
	// �� ��ü�� ����
	_mImageList.clear();

	return FALSE;
}

// ��� ����
void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}
void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

// ���� ����
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);

}
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

// ������ ����
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

// ���� ����
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}
void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

// ������ ����
void imageManager::scaleRender(string strKey, HDC hdc, int destX, int destY, float scale)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->scaleRender(hdc, destX, destY, scale);
}
void imageManager::scaleFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->scaleFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, scale);
}

// ������Ʈ ����
void imageManager::rotateRender(string strKey, HDC hdc, float destX, float destY, float angle)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->rotateRender(hdc, destX, destY, angle);
}
void imageManager::rotateFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle)
{
	// �̹����� ã�� �̹��� Ŭ������ �Լ��� ����
	image* img = findImage(strKey);
	if (img) img->rotateFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, angle);
}