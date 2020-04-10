#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{

	_invenImage = IMAGEMANAGER->addImage("인벤이미지", "플레이어/인벤토리/아이템창.bmp", 300, 300, true, RGB(255, 0, 255));
	_invenMenu = IMAGEMANAGER->addImage("인벤메뉴", "플레이어/인벤토리/아이템버튼.bmp", 100, 50, true, RGB(255, 0, 255));

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
	_invenItemselect = IMAGEMANAGER->addImage("인벤아이템선택", "플레이어/인벤토리/아이템선택영역.bmp", 45, 45, true, RGB(255, 0, 255));

	_sword = IMAGEMANAGER->addImage("검", "플레이어/인벤토리/검.bmp", 45, 45, true, RGB(255, 0, 255));

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

		
		//이 부분에서
		//f5를 눌러 인벤토리를 열고
		//아이템 선택하는 영역이 뜰건데요
		//그걸 아래처럼 키를 눌러서 바꾸고싶은데
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
