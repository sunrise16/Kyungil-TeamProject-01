// 헤더 파일
#include "stdafx.h"
#include "mainGame.h"

// 전역 변수
HWND		_hWnd;
HINSTANCE	_hInstance;
POINT		_ptMouse = { 0, 0 };

// mainGame 클래스 선언
mainGame* _mg;

// 함수 전방선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

// 윈도우 메인 함수
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//mainGame 클래스 동적할당
	_mg = new mainGame;

	// 인스턴스를 전역 변수에 담기
	_hInstance = hInstance;

	// 윈도우 구조체 선언 및 초기화
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;										// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;										// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// 마우스 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// 아이콘
	wndClass.hInstance = hInstance;									// 인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						// 윈도우 프로시져
	wndClass.lpszClassName = WINNAME;								// 클래스 이름
	wndClass.lpszMenuName = NULL;									// 메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						// 윈도우 스타일

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);

	// 윈도우 창 생성
	_hWnd = CreateWindow(
		WINNAME,				// 윈도우 클래스의 이름
		WINNAME,				// 윈도우 타이틀바 이름
		WINSTYLE,				// 윈도우 스타일
		WINSTARTX,				// 윈도우 화면좌표 X
		WINSTARTY,				// 윈도우 화면좌표 Y
		WINSIZEX,				// 윈도우 화면 가로크기
		WINSIZEY,				// 윈도우 화면 세로크기
		NULL,					// 부모 윈도우
		(HMENU)NULL,			// 메뉴 핸들
		hInstance,				// 인스턴스 지정
		NULL					// 윈도우 및 자식 윈도우를 생성하면 지정해주고 그렇지 않으면 NULL
	);

	// 클라이언트 영역의 사이즈를 정확히 잡기
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	
	// 화면에 윈도우창 출력
	ShowWindow(_hWnd, nCmdShow);

	// mainGame 클래스 초기화에 실패했을 경우 바로 종료
	if (FAILED(_mg->init()))
	{
		return 0;
	}

	// 메세지 루프
	MSG message;

	/*
	// 게임용 (나중에 사용)
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	*/

	// 일반 프로그래밍용
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//메인게임 클래스 해제
	_mg->release();

	return message.wParam;
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// mainGame 클래스가 메인 프로시저를 대신 실행
	return _mg->MainProc(hWnd, message, wParam, lParam);
}

// 윈도우 크기 조정 (클라이언트 영역의 사이즈를 정확히 잡기)
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	// 실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);

	// 위의 Rect 정보로 윈도우 클라이언트 사이즈를 세팅
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}