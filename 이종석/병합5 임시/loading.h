#pragma once
#include "gameNode.h"
#include "progressBar.h"

// 로드 아이템 종류
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			// 빈 비트맵 이미지
	LOAD_KIND_IMAGE_1,			// 일반 이미지
	LOAD_KIND_IMAGE_2,			// 일반 이미지 (좌표)
	LOAD_KIND_FRAMEIMAGE_0,		// 프레임 이미지
	LOAD_KIND_FRAMEIMAGE_1,		// 프레임 이미지 (좌표)
	LOAD_KIND_SOUND,			// 사운드
	LOAD_KIND_END
};

// 이미지 리소스 구조체
struct tagImageResource
{
	string keyName;				// 이미지 키값
	const char* fileName;		// 이미지 파일 이름
	int x, y;					// 위치 좌표
	int width, height;			// 가로, 세로 길이
	int frameX, frameY;			// 프레임 X, Y 갯수
	bool isTrans;				// 배경 지울 것인지 체크
	COLORREF transColor;		// 지울 배경 색깔
};

// loadItem 클래스
class loadItem
{
private:
	// 객체 관련
	tagImageResource _imageResource;		// 이미지 리소스 구조체를 담은 객체

	// 변수 관련
	LOAD_KIND _kind;						// 로드 아이템 종류

public:
	// 초기화 처리
	HRESULT init(string strKey, int width, int height);
	HRESULT init(string strKey, const char* fileName, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));

	// 로딩 아이템 종류 가져오기
	LOAD_KIND getLoadKind() { return _kind; }
	
	// 이미지 리소스 가져오기
	tagImageResource getImageResource() { return _imageResource; }

	// 생성자, 소멸자
	loadItem() {}
	~loadItem() {}
};

// loading 클래스
class loading : public gameNode
{
private:
	// loadItem 클래스를 담을 벡터 및 반복자
	typedef vector<loadItem*> vLoadItem;				// loadItem 클래스를 담은 벡터
	typedef vector<loadItem*>::iterator viLoadItem;		// loadItem 클래스를 담은 벡터 반복자

private:
	// 이미지 관련
	image* _background;									// 백그라운드
	progressBar* _loadingBar;							// 로딩바
	int _currentGauge;									// 현재 게이지

	// 객체 관련
	vLoadItem _vLoadItem;								// loadItem 클래스를 담은 최종 벡터

public:
	// GET, SET 함수
	vLoadItem getLoadItem() { return _vLoadItem; }
	int getCurrentGauge() { return _currentGauge; }

	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 이미지 로딩
	void loadImage(string strKey, int width, int height);
	void loadImage(string strKey, const char* fileName, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	void loadImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	void loadFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	void loadFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));

	// 이미지 로딩 완료 체크
	bool loadingDone();

	// 생성자, 소멸자
	loading() {}
	~loading() {}
};

