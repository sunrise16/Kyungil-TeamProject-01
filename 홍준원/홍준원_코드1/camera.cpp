#include "stdafx.h"
#include "camera.h"

// �ʱ�ȭ (init)
HRESULT camera::init()
{
	// ��׶��� �̹��� �ʱ�ȭ
	_img = IMAGEMANAGER->addImage("Background", "Background.bmp", WINSIZEX, WINSIZEY);

	// ī�޶� RECT ��ġ �ʱ�ȭ
	_rcCam = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, CAMSIZEX, CAMSIZEY);

	return S_OK;
}

// ���� (release)
void camera::release()
{
}

// ������Ʈ (update)
void camera::update()
{
	// �����̽� Ű�� �������� 
	// ���Ű�� ��׶���� ī�޶� ����Ī�ϸ鼭 ����
	if (INPUT->getToggleKey(VK_SPACE))
	{
		// �̹����� ���� �̵�
		if (INPUT->getKey('A'))
		{
			_img->setX(_img->getX() + 5.0f);
		}
		if (INPUT->getKey('D'))
		{
			_img->setX(_img->getX() - 5.0f);
		}
		if (INPUT->getKey('W'))
		{
			_img->setY(_img->getY() + 5.0f);
		}
		if (INPUT->getKey('S'))
		{
			_img->setY(_img->getY() - 5.0f);
		}
	}
	else
	{
		// ī�޶� �̵�
		if (INPUT->getKey('A') && _rcCam.left > 0)
		{
			_rcCam.left -= 5;
			_rcCam.right -= 5;
		}
		if (INPUT->getKey('D') && _rcCam.right < WINSIZEX)
		{
			_rcCam.left += 5;
			_rcCam.right += 5;
		}
		if (INPUT->getKey('W') && _rcCam.top > 0)
		{
			_rcCam.top -= 5;
			_rcCam.bottom -= 5;
		}
		if (INPUT->getKey('S') && _rcCam.bottom < WINSIZEY)
		{
			_rcCam.top += 5;
			_rcCam.bottom += 5;
		}
	}
}

// ���� (render)
void camera::render()
{
	// ��׶��� ����
	_img->render(getMemDC(), _rcCam.left, _rcCam.top, _img->getX() + _rcCam.left, _img->getY() + _rcCam.top, CAMSIZEX, CAMSIZEY);;

	// ī�޶� ����
	// Rectangle(getMemDC(), _rcCam);
	FrameRect(getMemDC(), _rcCam, RGB(255, 255, 0));
}
