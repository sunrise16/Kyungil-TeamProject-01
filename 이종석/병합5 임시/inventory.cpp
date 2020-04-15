#include "stdafx.h"
#include "inventory.h"

// �ʱ�ȭ (init)
HRESULT inventory::init()
{
	// �κ��丮 �޴�, �̹��� �߰�
	_invenImage = IMAGEMANAGER->addImage("�κ��̹���", "Images/Inventory/������â.bmp", 300, 300, true, RGB(255, 0, 255));
	_invenMenu = IMAGEMANAGER->addImage("�κ��޴�", "Images/Inventory/�����۹�ư.bmp", 100, 50, true, RGB(255, 0, 255));
	_invenItemselect = IMAGEMANAGER->addImage("�κ������ۼ���", "Images/Inventory/�����ۼ��ÿ���.bmp", 45, 45, true, RGB(255, 0, 255));

	// ������ ������ �̹��� �߰�
	_sword = IMAGEMANAGER->addImage("��", "Images/Inventory/��.bmp", 45, 45, true, RGB(255, 0, 255));

	// �κ��丮 �ʱ�ȭ
	for (int i = 0; i < 12; i++)
	{
		_item[i] = RectMake(103 + (50 * (i % 4)), 90 + (55 * (i / 4)), 45, 45);
	}

	// ��Ÿ ���� �ʱ�ȭ
	selectNum = 0;
	openCount = 0;

	// �ʱ�ȭ ����
	return S_OK;
}

// ���� (release)
void inventory::release()
{
}

// ������Ʈ (update)
void inventory::update()
{
	// �κ��丮 ����
	if (INPUT->getKeyDown(VK_F5))
	{
		openCount++;
	}
}

// ���� (render)
void inventory::render()
{
	if (openCount % 2 == 1)
	{
		_invenImage->render(getMemDC(), 50, 50);
		_invenMenu->render(getMemDC(), 50, 0);

		//for (int i = 0; i < 12; i++)
		//{
		//	Rectangle(getMemDC(), _item[i]);
		//}

		_sword->render(getMemDC(), _item[0].left, _item[0].top);

		// ����Ű �Է����� �κ��丮 ����ĭ �ű��
		if (INPUT->getKeyDown('6'))
		{
			selectNum++;
			if (selectNum >= 11)
			{
				selectNum = 11;
			}

		}
		if (INPUT->getKeyDown('4'))
		{
			selectNum--;
			if (selectNum <= 0)
			{
				selectNum = 0;
			}
		}
		if (INPUT->getKeyDown('2'))
		{

			if (selectNum == 0)
			{
				selectNum = 0;
			}
			else if (selectNum == 1)
			{
				selectNum = 1;
			}
			else if (selectNum == 2)
			{
				selectNum = 2;
			}
			else if (selectNum == 3)
			{
				selectNum = 3;
			}
			else
			{
				selectNum -= 4;
			}
		}
		if (INPUT->getKeyDown('8'))
		{

			if (selectNum == 8)
			{
				selectNum = 8;
			}
			else if (selectNum == 9)
			{
				selectNum = 9;
			}
			else if (selectNum == 10)
			{
				selectNum = 10;
			}
			else if (selectNum == 11)
			{
				selectNum = 11;
			}
			else
			{
				selectNum += 4;
			}
		}
		_invenItemselect->render(getMemDC(), _item[selectNum].left, _item[selectNum].top);
	}

	//sprintf_s(str, "%d", selectNum);
	//TextOut(getMemDC(), 500, 500, str, strlen(str));
}