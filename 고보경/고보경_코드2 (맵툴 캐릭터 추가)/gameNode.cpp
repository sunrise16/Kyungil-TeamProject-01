#include "stdafx.h"
#include "gameNode.h"

// 초기화 (init)
HRESULT gameNode::init()
{
	// HDC 초기화
	_hdc = GetDC(_hWnd);

	// 타이머 초기화
	SetTimer(_hWnd, 1, 10, NULL);

	// 입력 매니저 초기화
	INPUT->init();

	// 랜덤 매니저 초기화
	RANDOM->init();

	// 이미지 매니저 초기화
	IMAGEMANAGER->init();

	// 플레이어 데이터 초기화
	PLAYERDATA->init();

	// 씬 매니저 초기화
	SCENEMANAGER->init();

	// INI 데이터 초기화
	INIDATA->init();

	// 사운드 매니저 초기화
	SOUNDMANAGER->init();
	
	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void gameNode::release()
{
	// 타이머 해제
	KillTimer(_hWnd, 1);

	// 입력 매니저 해제
	INPUT->release();
	INPUT->releaseSingleton();

	// 랜덤 매니저 해제
	RANDOM->release();
	RANDOM->releaseSingleton();

	// 이미지 매니저 해제
	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();

	// 플레이어 데이터 해제
	PLAYERDATA->release();
	PLAYERDATA->releaseSingleton();

	// 씬 매니저 해제
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();

	// INI 데이터 해제
	INIDATA->release();
	INIDATA->releaseSingleton();

	// 사운드 매니저 해제
	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	// HDC 해제
	ReleaseDC(_hWnd, _hdc);
}

// 업데이트 (update)
void gameNode::update()
{
	// 새로고침 (이후 고성능 타이머를 만든 후에는 사용하지 않음)
	InvalidateRect(_hWnd, NULL, FALSE);
}

// 렌더 (render)
void gameNode::render()
{
}

// 메인 프로시저 (MainProc)
LRESULT gameNode::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:			// 출력에 관한 모든 것을 담당 (문자, 그림, 도형 등등 화면에 보이는 모든 것)
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:	// 마우스 커서 눌렀을 때 좌표 체크
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_MOUSEMOVE:		// 마우스 커서 좌표 체크
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		// 키보드 키가 눌렸을때 메세지 발생
		switch (wParam)
		{
		case VK_ESCAPE:		// Esc 키를 누르면 화면 종료
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		// 소멸자
		PostQuitMessage(0);
		return 0;
	}

	// 윈도우 프로시저에서 처리되지 않은 나머지 메세지를 처리
	return (DefWindowProc(hWnd, message, wParam, lParam));
}
