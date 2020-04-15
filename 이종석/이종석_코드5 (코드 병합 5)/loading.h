#pragma once
#include "gameNode.h"
#include "progressBar.h"

// �ε� ������ ����
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			// �� ��Ʈ�� �̹���
	LOAD_KIND_IMAGE_1,			// �Ϲ� �̹���
	LOAD_KIND_IMAGE_2,			// �Ϲ� �̹��� (��ǥ)
	LOAD_KIND_FRAMEIMAGE_0,		// ������ �̹���
	LOAD_KIND_FRAMEIMAGE_1,		// ������ �̹��� (��ǥ)
	LOAD_KIND_SOUND,			// ����
	LOAD_KIND_END
};

// �̹��� ���ҽ� ����ü
struct tagImageResource
{
	string keyName;				// �̹��� Ű��
	const char* fileName;		// �̹��� ���� �̸�
	int x, y;					// ��ġ ��ǥ
	int width, height;			// ����, ���� ����
	int frameX, frameY;			// ������ X, Y ����
	bool isTrans;				// ��� ���� ������ üũ
	COLORREF transColor;		// ���� ��� ����
};

// loadItem Ŭ����
class loadItem
{
private:
	// ��ü ����
	tagImageResource _imageResource;		// �̹��� ���ҽ� ����ü�� ���� ��ü

	// ���� ����
	LOAD_KIND _kind;						// �ε� ������ ����

public:
	// �ʱ�ȭ ó��
	HRESULT init(string strKey, int width, int height);
	HRESULT init(string strKey, const char* fileName, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));

	// �ε� ������ ���� ��������
	LOAD_KIND getLoadKind() { return _kind; }
	
	// �̹��� ���ҽ� ��������
	tagImageResource getImageResource() { return _imageResource; }

	// ������, �Ҹ���
	loadItem() {}
	~loadItem() {}
};

// loading Ŭ����
class loading : public gameNode
{
private:
	// loadItem Ŭ������ ���� ���� �� �ݺ���
	typedef vector<loadItem*> vLoadItem;				// loadItem Ŭ������ ���� ����
	typedef vector<loadItem*>::iterator viLoadItem;		// loadItem Ŭ������ ���� ���� �ݺ���

private:
	// �̹��� ����
	image* _background;									// ��׶���
	progressBar* _loadingBar;							// �ε���
	int _currentGauge;									// ���� ������

	// ��ü ����
	vLoadItem _vLoadItem;								// loadItem Ŭ������ ���� ���� ����

public:
	// GET, SET �Լ�
	vLoadItem getLoadItem() { return _vLoadItem; }
	int getCurrentGauge() { return _currentGauge; }

	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// �̹��� �ε�
	void loadImage(string strKey, int width, int height);
	void loadImage(string strKey, const char* fileName, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	void loadImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	void loadFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	void loadFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));

	// �̹��� �ε� �Ϸ� üũ
	bool loadingDone();

	// ������, �Ҹ���
	loading() {}
	~loading() {}
};

