#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{

	_invenImage = IMAGEMANAGER->addImage("�κ��̹���", "�÷��̾�/�κ��丮/������â.bmp", 300, 300, true, RGB(255, 0, 255));
	_invenMenu = IMAGEMANAGER->addImage("�κ��޴�", "�÷��̾�/�κ��丮/�����۹�ư.bmp", 100, 50, true, RGB(255, 0, 255));

	for (int i = 0; i < 12; i++)
	{
		if (i <= 3)
		{
			_item[i] = RectMake(103 + (50 * i), 93, 45, 45);
		}
		if (i > 3 && i <= 7)
		{
			_item[i] = RectMake((50 * i) - 97, 145, 45, 45);
		}
		if (i > 7 && i <= 11)
		{
			_item[i] = RectMake((50 * i) - 297, 200, 45, 45);
		}
	}
	_invenItemselect = IMAGEMANAGER->addImage("�κ������ۼ���", "�÷��̾�/�κ��丮/�����ۼ��ÿ���.bmp", 45, 45, true, RGB(255, 0, 255));

	_sword = IMAGEMANAGER->addImage("��", "�÷��̾�/�κ��丮/��.bmp", 45, 45, true, RGB(255, 0, 255));

	_invenopen = false;

	selectNum = 0;

	openCount = 0;

	return S_OK;

}

void Inventory::release()
{
}

void Inventory::update()
{
	if (INPUT->getKeyDown(VK_F5))
	{
		openCount++;
	}
	
	
}

void Inventory::render()
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

		
		//�� �κп���
		//f5�� ���� �κ��丮�� ����
		//������ �����ϴ� ������ ��ǵ���
		//�װ� �Ʒ�ó�� Ű�� ������ �ٲٰ������
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
		

		//0 1 2 3
		//4 5 6 7
		//8 9 10 11

	}

		

	sprintf(str, "%d", selectNum);
	TextOut(getMemDC(), 500, 500, str, strlen(str));
}
