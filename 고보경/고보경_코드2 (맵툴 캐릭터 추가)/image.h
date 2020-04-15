#pragma once

// image Ŭ����
class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		// ���ҽ��� �ε� (��� ����)
		LOAD_FILE,				// ���Ϸ� �ε�
		LOAD_EMPTY,				// �� ��Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		HDC hMemDC;				// �޸� DC
		HBITMAP hBit;			// ��Ʈ��
		HBITMAP hOBit;			// �õ� ��Ʈ��
		float x;					// �̹��� x��ǥ
		float y;					// �̹��� y��ǥ
		int width;				// �̹��� ���� ����
		int height;				// �̹��� ���� ����
		int currentFrameX;		// ���� ������X
		int currentFrameY;		// ���� ������Y
		int maxFrameX;			// �ִ� X������ ����
		int maxFrameY;			// �ִ� Y������ ����
		int frameWidth;			// 1������ ���� ����
		int frameHeight;		// 1������ ���� ����
		BYTE loadType;			// �̹��� �ε� Ÿ��
		tagImage()				// ������ = �ʱ�ȭ
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_EMPTY;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;			// �̹��� ����
	char*			_fileName;			// �̹��� �̸�
	bool			_isTrans;			// ���� ���� ������ üũ
	COLORREF		_transColor;		// ���� ���� RGB���� (����Ÿ = RGB(255, 0, 255))	

	LPIMAGE_INFO	_blendImage;		// ���� ���� �̹���
	BLENDFUNCTION	_blendFunc;			// ���� ���� ���

	LPIMAGE_INFO	_scaleImage;		// ������ �̹���
	LPIMAGE_INFO	_rotateImage;		// ������Ʈ �̹���
	
public:
	// �� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);

	// �̹��� ���ҽ� �ʱ�ȭ => ������� �ʾƼ� ������ �ʾ���

	// �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));

	// ������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));

	// ���� ���� �ʱ�ȭ
	HRESULT initForAlphaBlend();

	// ������ ���� �ʱ�ȭ
	HRESULT initForScaleBlt();

	// ������Ʈ ���� �ʱ�ȭ
	HRESULT initForRotateImage(bool isFrameImage);

	// ����
	void release();

	// ���� (���� ���ϴ� ��ǥ�� ���, �Ϲ������� RECT�� LT��ǥ�� �̹����� ����)
	void render(HDC hdc, int destX = 0, int destY = 0);

	// ���� (���� ���ϴ� ��ǥ�� ���ϴ� ũ�⸸ŭ �߶� ���)
	void render(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth = 0, int sourceHeight = 0);

	// ���� ���� (�̹����� ���İ���ŭ ����ȭ)
	// 0(min) ~ 255(max)
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight, BYTE alpha);

	// ������ ����
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int frameX, int frameY);
	void frameRender(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int frameX, int frameY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(HDC hdc, int destX, int destY, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int frameX, int frameY, BYTE alpha);

	// ���� ����
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// ������ ����
	void scaleRender(HDC hdc, int destX, int destY, float scale = 1.0f);
	void scaleFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);

	// ������Ʈ ����
	void rotateRender(HDC hdc, float destX, float destY, float angle);
	void rotateFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle);

	// DC ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// �̹��� X��ǥ
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	// �̹��� Y��ǥ
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// �̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x + (_imageInfo->width / 2);
		_imageInfo->y = y + (_imageInfo->height / 2);
	}

	// �̹��� ����, ���� ũ��
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	// �ٿ�� �ڽ� (�浹�� RECT)
	inline RECT boundingBox()
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height };
		return rc;
	}
	inline RECT boundingBoxWithFrame()
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };
		return rc;
	}

	// ������ X
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	// ������ Y
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// �̹��� 1������ ����, ���� ����
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	// �ƽ� ������
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	// ������, �Ҹ���
	image();
	~image();
};