#include "stdafx.h"
#include "input.h"

// 초기화 (init)
HRESULT input::init()
{
	// 키값을 전부 눌려있지 않은 상태로 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}

	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void input::release()
{
}

// 키 입력 함수
// 키가 계속 눌려 있는지 체크
bool input::getKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

// 키가 한번만 눌렸는지 체크
bool input::getKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}
	
	return false;
}

// 키가 눌렸다 떼졌는지 체크
bool input::getKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp[key] = true;
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp[key] = false;
			return true;
		}
	}

	return false;
}

// 토글 키인지 체크
bool input::getToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}
