#include "stdafx.h"
#include "input.h"

// �ʱ�ȭ (init)
HRESULT input::init()
{
	// Ű���� ���� �������� ���� ���·� �ʱ�ȭ
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}

	// �ʱ�ȭ ����
	return S_OK;
}

// ���� (release)
void input::release()
{
}

// Ű �Է� �Լ�
// Ű�� ��� ���� �ִ��� üũ
bool input::getKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

// Ű�� �ѹ��� ���ȴ��� üũ
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

// Ű�� ���ȴ� �������� üũ
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

// ��� Ű���� üũ
bool input::getToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}
