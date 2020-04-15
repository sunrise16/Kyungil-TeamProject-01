#include "stdafx.h"
#include "inventory.h"

// 초기화 (init)
HRESULT inventory::init()
{
	// 인벤토리 메뉴, 이미지 추가
	_invenImage = IMAGEMANAGER->addImage("인벤이미지", "Images/Inventory/아이템창.bmp", 300, 300, true, RGB(255, 0, 255));
	_invenMenu = IMAGEMANAGER->addImage("인벤메뉴", "Images/Inventory/아이템버튼.bmp", 100, 50, true, RGB(255, 0, 255));
	_invenItemselect = IMAGEMANAGER->addImage("인벤아이템선택", "Images/Inventory/아이템선택영역.bmp", 45, 45, true, RGB(255, 0, 255));

	// 아이템 아이콘 이미지 추가
	_sword = IMAGEMANAGER->addImage("검", "Images/Inventory/검.bmp", 45, 45, true, RGB(255, 0, 255));

	// 인벤토리 초기화
	for (int i = 0; i < 12; i++)
	{
		_item[i] = RectMake(103 + (50 * (i % 4)), 90 + (55 * (i / 4)), 45, 45);
	}

	// 기타 변수 초기화
	_invenopen = false;
	selectNum = 0;
	openCount = 0;

	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void inventory::release()
{
}

// 업데이트 (update)
void inventory::update()
{
	// 인벤토리 오픈
	if (INPUT->getKeyDown(VK_F5))
	{
		openCount++;
	}
}

// 렌더 (render)
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

		// 숫자키 입력으로 인벤토리 선택칸 옮기기
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

	sprintf_s(str, "%d", selectNum);
	TextOut(getMemDC(), 500, 500, str, strlen(str));
}