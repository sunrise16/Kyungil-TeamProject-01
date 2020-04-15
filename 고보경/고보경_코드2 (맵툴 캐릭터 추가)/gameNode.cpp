#include "stdafx.h"
#include "gameNode.h"

// �ʱ�ȭ (init)
HRESULT gameNode::init()
{
	// HDC �ʱ�ȭ
	_hdc = GetDC(_hWnd);

	// Ÿ�̸� �ʱ�ȭ
	SetTimer(_hWnd, 1, 10, NULL);

	// �Է� �Ŵ��� �ʱ�ȭ
	INPUT->init();

	// ���� �Ŵ��� �ʱ�ȭ
	RANDOM->init();

	// �̹��� �Ŵ��� �ʱ�ȭ
	IMAGEMANAGER->init();

	// �÷��̾� ������ �ʱ�ȭ
	PLAYERDATA->init();

	// �� �Ŵ��� �ʱ�ȭ
	SCENEMANAGER->init();

	// INI ������ �ʱ�ȭ
	INIDATA->init();

	// ���� �Ŵ��� �ʱ�ȭ
	SOUNDMANAGER->init();
	
	// �ʱ�ȭ ����
	return S_OK;
}

// ���� (release)
void gameNode::release()
{
	// Ÿ�̸� ����
	KillTimer(_hWnd, 1);

	// �Է� �Ŵ��� ����
	INPUT->release();
	INPUT->releaseSingleton();

	// ���� �Ŵ��� ����
	RANDOM->release();
	RANDOM->releaseSingleton();

	// �̹��� �Ŵ��� ����
	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();

	// �÷��̾� ������ ����
	PLAYERDATA->release();
	PLAYERDATA->releaseSingleton();

	// �� �Ŵ��� ����
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();

	// INI ������ ����
	INIDATA->release();
	INIDATA->releaseSingleton();

	// ���� �Ŵ��� ����
	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	// HDC ����
	ReleaseDC(_hWnd, _hdc);
}

// ������Ʈ (update)
void gameNode::update()
{
	// ���ΰ�ħ (���� ���� Ÿ�̸Ӹ� ���� �Ŀ��� ������� ����)
	InvalidateRect(_hWnd, NULL, FALSE);
}

// ���� (render)
void gameNode::render()
{
}

// ���� ���ν��� (MainProc)
LRESULT gameNode::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:			// ��¿� ���� ��� ���� ��� (����, �׸�, ���� ��� ȭ�鿡 ���̴� ��� ��)
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:	// ���콺 Ŀ�� ������ �� ��ǥ üũ
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_MOUSEMOVE:		// ���콺 Ŀ�� ��ǥ üũ
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		// Ű���� Ű�� �������� �޼��� �߻�
		switch (wParam)
		{
		case VK_ESCAPE:		// Esc Ű�� ������ ȭ�� ����
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		// �Ҹ���
		PostQuitMessage(0);
		return 0;
	}

	// ������ ���ν������� ó������ ���� ������ �޼����� ó��
	return (DefWindowProc(hWnd, message, wParam, lParam));
}
